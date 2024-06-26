################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/App_Tasks.c \
../Core/Src/Build_msg.c \
../Core/Src/Buzzer.c \
../Core/Src/CalculateSpeed.c \
../Core/Src/Call_Back_Functions.c \
../Core/Src/Car_Control.c \
../Core/Src/GPS.c \
../Core/Src/LCD_I2C.c \
../Core/Src/NMEA.c \
../Core/Src/UartRingbuffer.c \
../Core/Src/Warning_Functions.c \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/App_Tasks.o \
./Core/Src/Build_msg.o \
./Core/Src/Buzzer.o \
./Core/Src/CalculateSpeed.o \
./Core/Src/Call_Back_Functions.o \
./Core/Src/Car_Control.o \
./Core/Src/GPS.o \
./Core/Src/LCD_I2C.o \
./Core/Src/NMEA.o \
./Core/Src/UartRingbuffer.o \
./Core/Src/Warning_Functions.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/App_Tasks.d \
./Core/Src/Build_msg.d \
./Core/Src/Buzzer.d \
./Core/Src/CalculateSpeed.d \
./Core/Src/Call_Back_Functions.d \
./Core/Src/Car_Control.d \
./Core/Src/GPS.d \
./Core/Src/LCD_I2C.d \
./Core/Src/NMEA.d \
./Core/Src/UartRingbuffer.d \
./Core/Src/Warning_Functions.d \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/App_Tasks.cyclo ./Core/Src/App_Tasks.d ./Core/Src/App_Tasks.o ./Core/Src/App_Tasks.su ./Core/Src/Build_msg.cyclo ./Core/Src/Build_msg.d ./Core/Src/Build_msg.o ./Core/Src/Build_msg.su ./Core/Src/Buzzer.cyclo ./Core/Src/Buzzer.d ./Core/Src/Buzzer.o ./Core/Src/Buzzer.su ./Core/Src/CalculateSpeed.cyclo ./Core/Src/CalculateSpeed.d ./Core/Src/CalculateSpeed.o ./Core/Src/CalculateSpeed.su ./Core/Src/Call_Back_Functions.cyclo ./Core/Src/Call_Back_Functions.d ./Core/Src/Call_Back_Functions.o ./Core/Src/Call_Back_Functions.su ./Core/Src/Car_Control.cyclo ./Core/Src/Car_Control.d ./Core/Src/Car_Control.o ./Core/Src/Car_Control.su ./Core/Src/GPS.cyclo ./Core/Src/GPS.d ./Core/Src/GPS.o ./Core/Src/GPS.su ./Core/Src/LCD_I2C.cyclo ./Core/Src/LCD_I2C.d ./Core/Src/LCD_I2C.o ./Core/Src/LCD_I2C.su ./Core/Src/NMEA.cyclo ./Core/Src/NMEA.d ./Core/Src/NMEA.o ./Core/Src/NMEA.su ./Core/Src/UartRingbuffer.cyclo ./Core/Src/UartRingbuffer.d ./Core/Src/UartRingbuffer.o ./Core/Src/UartRingbuffer.su ./Core/Src/Warning_Functions.cyclo ./Core/Src/Warning_Functions.d ./Core/Src/Warning_Functions.o ./Core/Src/Warning_Functions.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

