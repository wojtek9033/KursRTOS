################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Source/os_systick.c \
D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.c \
D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.c 

OBJS += \
./common/cmsis/CMSIS/RTOS2/Source/os_systick.o \
./common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.o \
./common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.o 

C_DEPS += \
./common/cmsis/CMSIS/RTOS2/Source/os_systick.d \
./common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.d \
./common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.d 


# Each subdirectory must supply rules for building sources it contributes
common/cmsis/CMSIS/RTOS2/Source/os_systick.o: D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Source/os_systick.c common/cmsis/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.o: D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.c common/cmsis/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.o: D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.c common/cmsis/CMSIS/RTOS2/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-cmsis-2f-CMSIS-2f-RTOS2-2f-Source

clean-common-2f-cmsis-2f-CMSIS-2f-RTOS2-2f-Source:
	-$(RM) ./common/cmsis/CMSIS/RTOS2/Source/os_systick.cyclo ./common/cmsis/CMSIS/RTOS2/Source/os_systick.d ./common/cmsis/CMSIS/RTOS2/Source/os_systick.o ./common/cmsis/CMSIS/RTOS2/Source/os_systick.su ./common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.cyclo ./common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.d ./common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.o ./common/cmsis/CMSIS/RTOS2/Source/os_tick_gtim.su ./common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.cyclo ./common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.d ./common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.o ./common/cmsis/CMSIS/RTOS2/Source/os_tick_ptim.su

.PHONY: clean-common-2f-cmsis-2f-CMSIS-2f-RTOS2-2f-Source

