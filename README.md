# STM32_HAL_NeoPixel

A lightweight, resource saving driver for SK6812 NeoPixels using STM32 HAL, Timer PWM and DMA. Implemented on STM32F042K6 (NUCLEO-F042K6) using TIM2, Channel 1 and DMA.

![Demo with 8 SK6812 NeoPixel LEDs](/blog/demo.jpg)

### Changelog
07-10-2020:
- Added support for WS2812B NeoPixel LEDs. Change to WS2812B by changing the parameter NUM_BPP from (4) to (3) in sk6812.c