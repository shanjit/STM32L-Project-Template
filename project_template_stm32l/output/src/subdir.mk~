################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/core_cm3.c \
../src/main.c \
../src/stm32l1xx_it.c \
../src/stm32l_discovery_lcd.c \
../src/system_stm32l1xx.c 

S_UPPER_SRCS += \
../src/startup_stm32l1xx_md.S 

OBJS += \
./src/core_cm3.o \
./src/main.o \
./src/startup_stm32l1xx_md.o \
./src/stm32l1xx_it.o \
./src/stm32l_discovery_lcd.o \
./src/system_stm32l1xx.o 

C_DEPS += \
./src/core_cm3.d \
./src/main.d \
./src/stm32l1xx_it.d \
./src/stm32l_discovery_lcd.d \
./src/system_stm32l1xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -DUSE_STDPERIPH_DRIVER -DUSE_STM32L_DISCOVERY -DSTM32L1XX_MD -I"/home/cuil/workspace/arm/stm32ldiscoveryboard/project_template_stm32l/src" -I"/home/cuil/workspace/arm/stm32ldiscoveryboard/project_template_stm32l/peri_library/peri_inc" -O0 -g3 -Wall -c -mthumb -mcpu=cortex-m3 -mfix-cortex-m3-ldrd -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	arm-none-eabi-as -mthumb -mcpu=cortex-m3 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


