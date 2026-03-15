################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.c 

OBJS += \
./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.o \
./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.o 

C_DEPS += \
./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.d \
./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.d 


# Each subdirectory must supply rules for building sources it contributes
common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.c common/stm32-mw-freertos/Source/portable/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.c common/stm32-mw-freertos/Source/portable/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source-2f-portable-2f-Common

clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source-2f-portable-2f-Common:
	-$(RM) ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.cyclo ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.d ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.o ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers.su ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.cyclo ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.d ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.o ./common/stm32-mw-freertos/Source/portable/Common/mpu_wrappers_v2.su

.PHONY: clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source-2f-portable-2f-Common

