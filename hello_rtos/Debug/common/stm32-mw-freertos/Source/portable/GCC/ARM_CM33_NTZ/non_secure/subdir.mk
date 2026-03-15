################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c 

OBJS += \
./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.o \
./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.o \
./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o 

C_DEPS += \
./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.d \
./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.d \
./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.d 


# Each subdirectory must supply rules for building sources it contributes
common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.c common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.c common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source-2f-portable-2f-GCC-2f-ARM_CM33_NTZ-2f-non_secure

clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source-2f-portable-2f-GCC-2f-ARM_CM33_NTZ-2f-non_secure:
	-$(RM) ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.cyclo ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.d ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.o ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.su ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.cyclo ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.d ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.o ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/port.su ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.cyclo ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.d ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.o ./common/stm32-mw-freertos/Source/portable/GCC/ARM_CM33_NTZ/non_secure/portasm.su

.PHONY: clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source-2f-portable-2f-GCC-2f-ARM_CM33_NTZ-2f-non_secure

