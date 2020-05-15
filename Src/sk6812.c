// Peripheral usage
#include "stm32f0xx_hal.h"
extern TIM_HandleTypeDef htim2;

#define SK6812_PWM_DUTY_HI (38)
#define SK6812_PWM_DUTY_LO (19)

// LED parameters
#define NUM_BPP (4)
#define NUM_PIXELS (8)
#define NUM_BYTES (NUM_BPP * NUM_PIXELS)

// LED color buffer
uint8_t rgb_arr[NUM_BYTES] = {0};

// LED write buffer
#define WRITE_BUF_LENGTH (NUM_BPP * 8)
uint8_t write_buf[WRITE_BUF_LENGTH] = {0};
uint_fast8_t write_buf_pos;

// Initializer
void led_init() {
  write_buf_pos = 0;
  // HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)write_buf, WRITE_BUF_LENGTH);
}

static inline uint8_t scale8(uint8_t x, uint8_t scale) {
  return ((uint16_t)x * scale) >> 8;
}

// Set a single color (RGB) to index
void led_set_RGB(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  rgb_arr[4 * index] = scale8(g, 0xB0); // g;
  rgb_arr[4 * index + 1] = r;
  rgb_arr[4 * index + 2] = scale8(b, 0xF0); // b;
  rgb_arr[4 * index + 3] = 0;
}

// Set a single color (RGBW) to index
void led_set_RGBW(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
    led_set_RGB(index, r, g, b);
  rgb_arr[4 * index + 3] = w;
}

// Set all colors to RGB
void led_set_all_RGB(uint8_t r, uint8_t g, uint8_t b) {
  for(uint_fast8_t i = 0; i < NUM_PIXELS; ++i) led_set_RGB(i, r, g, b);
}

// Set all colors to RGBW
void led_set_all_RGBW(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  for(uint_fast8_t i = 0; i < NUM_PIXELS; ++i) led_set_RGBW(i, r, g, b, w);
}

// Shuttle the data to the LEDs!
void led_render() {
  // Ooh boi the first data buffer!!
  write_buf_pos = 0;
  for(uint_fast8_t i = 0; i < 8; ++i) {
    write_buf[i     ] = SK6812_PWM_DUTY_LO << (((rgb_arr[0] << i) & 0x80) > 0);
    write_buf[i +  8] = SK6812_PWM_DUTY_LO << (((rgb_arr[1] << i) & 0x80) > 0);
    write_buf[i + 16] = SK6812_PWM_DUTY_LO << (((rgb_arr[2] << i) & 0x80) > 0);
    write_buf[i + 24] = SK6812_PWM_DUTY_LO << (((rgb_arr[3] << i) & 0x80) > 0);
  }
  write_buf_pos++; // Since we're ready for the next buffer
  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)write_buf, WRITE_BUF_LENGTH);
}

void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) {
  // DMA buffer set from LED(write_buf_pos) to LED(write_buf_pos + 1)
  if(write_buf_pos < NUM_PIXELS) {
    // We're in. Let's fill the mem
    for(uint_fast8_t i = 0; i < 8; ++i) {
      write_buf[i   ]=SK6812_PWM_DUTY_LO<<(((rgb_arr[write_buf_pos*4  ]<<i)&0x80)>0);
      write_buf[i+ 8]=SK6812_PWM_DUTY_LO<<(((rgb_arr[write_buf_pos*4+1]<<i)&0x80)>0);
      write_buf[i+16]=SK6812_PWM_DUTY_LO<<(((rgb_arr[write_buf_pos*4+2]<<i)&0x80)>0);
      write_buf[i+24]=SK6812_PWM_DUTY_LO<<(((rgb_arr[write_buf_pos*4+3]<<i)&0x80)>0);
    }
    write_buf_pos++;
  } else if (write_buf_pos >= NUM_PIXELS + 1) {
    // Last two transfers are resets. 64 * 1.25 us = 80 us = good enough reset
    for(uint_fast8_t i = 0; i < WRITE_BUF_LENGTH; ++i) write_buf[i] = 0;
    write_buf_pos++;
    if(write_buf_pos >= NUM_PIXELS + 2) {
      // Stop transfer, we're done for now until someone needs us again
      write_buf_pos = 0;
      HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
    }
  }
}
