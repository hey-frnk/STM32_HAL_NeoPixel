################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/sk6812.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f0xx.c 

OBJS += \
./Src/main.o \
./Src/sk6812.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f0xx.o 

C_DEPS += \
./Src/main.d \
./Src/sk6812.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DUSE_HAL_DRIVER -DSTM32F042x6 -I"/Users/HARDWARECOP/Documents/CCPP/STM32_Digital_RGBW_LED/Inc" -I"/Users/HARDWARECOP/Documents/CCPP/STM32_Digital_RGBW_LED/Drivers/STM32F0xx_HAL_Driver/Inc" -I"/Users/HARDWARECOP/Documents/CCPP/STM32_Digital_RGBW_LED/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"/Users/HARDWARECOP/Documents/CCPP/STM32_Digital_RGBW_LED/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"/Users/HARDWARECOP/Documents/CCPP/STM32_Digital_RGBW_LED/Drivers/CMSIS/Include"  -O3 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


