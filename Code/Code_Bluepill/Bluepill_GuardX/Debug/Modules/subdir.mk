################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/esp01.c \
../Modules/hcsr04.c \
../Modules/motor.c \
../Modules/mpu6050.c 

OBJS += \
./Modules/esp01.o \
./Modules/hcsr04.o \
./Modules/motor.o \
./Modules/mpu6050.o 

C_DEPS += \
./Modules/esp01.d \
./Modules/hcsr04.d \
./Modules/motor.d \
./Modules/mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/%.o Modules/%.su Modules/%.cyclo: ../Modules/%.c Modules/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"H:/stm32-zone/Bluepill_STM32F103C8T6/Bluepill_GuardX/Modules" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Modules

clean-Modules:
	-$(RM) ./Modules/esp01.cyclo ./Modules/esp01.d ./Modules/esp01.o ./Modules/esp01.su ./Modules/hcsr04.cyclo ./Modules/hcsr04.d ./Modules/hcsr04.o ./Modules/hcsr04.su ./Modules/motor.cyclo ./Modules/motor.d ./Modules/motor.o ./Modules/motor.su ./Modules/mpu6050.cyclo ./Modules/mpu6050.d ./Modules/mpu6050.o ./Modules/mpu6050.su

.PHONY: clean-Modules

