################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f746nghx.s 

OBJS += \
./Core/Startup/startup_stm32f746nghx.o 

S_DEPS += \
./Core/Startup/startup_stm32f746nghx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"D:/ME program/2017-PhD/01_research/02Study/34_ballon_like_cover/DeepLearing/TACTS/MicroController/STM32F746/TACT_stm32f7/Drivers/VL53L0X" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f746nghx.d ./Core/Startup/startup_stm32f746nghx.o

.PHONY: clean-Core-2f-Startup

