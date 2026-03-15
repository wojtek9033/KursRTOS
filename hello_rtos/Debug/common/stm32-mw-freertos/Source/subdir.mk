################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/croutine.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/event_groups.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/list.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/queue.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/stream_buffer.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/tasks.c \
D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/timers.c 

OBJS += \
./common/stm32-mw-freertos/Source/croutine.o \
./common/stm32-mw-freertos/Source/event_groups.o \
./common/stm32-mw-freertos/Source/list.o \
./common/stm32-mw-freertos/Source/queue.o \
./common/stm32-mw-freertos/Source/stream_buffer.o \
./common/stm32-mw-freertos/Source/tasks.o \
./common/stm32-mw-freertos/Source/timers.o 

C_DEPS += \
./common/stm32-mw-freertos/Source/croutine.d \
./common/stm32-mw-freertos/Source/event_groups.d \
./common/stm32-mw-freertos/Source/list.d \
./common/stm32-mw-freertos/Source/queue.d \
./common/stm32-mw-freertos/Source/stream_buffer.d \
./common/stm32-mw-freertos/Source/tasks.d \
./common/stm32-mw-freertos/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
common/stm32-mw-freertos/Source/croutine.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/croutine.c common/stm32-mw-freertos/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/event_groups.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/event_groups.c common/stm32-mw-freertos/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/list.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/list.c common/stm32-mw-freertos/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/queue.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/queue.c common/stm32-mw-freertos/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/stream_buffer.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/stream_buffer.c common/stm32-mw-freertos/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/tasks.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/tasks.c common/stm32-mw-freertos/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/stm32-mw-freertos/Source/timers.o: D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/timers.c common/stm32-mw-freertos/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F411RE -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/Core/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis/CMSIS/RTOS2/Include" -I"D:/Workspaces/RTOS/Kurs/common/cmsis-device-f4/Include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/CMSIS_RTOS_V2" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/include" -I"D:/Workspaces/RTOS/Kurs/common/stm32-mw-freertos/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source

clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source:
	-$(RM) ./common/stm32-mw-freertos/Source/croutine.cyclo ./common/stm32-mw-freertos/Source/croutine.d ./common/stm32-mw-freertos/Source/croutine.o ./common/stm32-mw-freertos/Source/croutine.su ./common/stm32-mw-freertos/Source/event_groups.cyclo ./common/stm32-mw-freertos/Source/event_groups.d ./common/stm32-mw-freertos/Source/event_groups.o ./common/stm32-mw-freertos/Source/event_groups.su ./common/stm32-mw-freertos/Source/list.cyclo ./common/stm32-mw-freertos/Source/list.d ./common/stm32-mw-freertos/Source/list.o ./common/stm32-mw-freertos/Source/list.su ./common/stm32-mw-freertos/Source/queue.cyclo ./common/stm32-mw-freertos/Source/queue.d ./common/stm32-mw-freertos/Source/queue.o ./common/stm32-mw-freertos/Source/queue.su ./common/stm32-mw-freertos/Source/stream_buffer.cyclo ./common/stm32-mw-freertos/Source/stream_buffer.d ./common/stm32-mw-freertos/Source/stream_buffer.o ./common/stm32-mw-freertos/Source/stream_buffer.su ./common/stm32-mw-freertos/Source/tasks.cyclo ./common/stm32-mw-freertos/Source/tasks.d ./common/stm32-mw-freertos/Source/tasks.o ./common/stm32-mw-freertos/Source/tasks.su ./common/stm32-mw-freertos/Source/timers.cyclo ./common/stm32-mw-freertos/Source/timers.d ./common/stm32-mw-freertos/Source/timers.o ./common/stm32-mw-freertos/Source/timers.su

.PHONY: clean-common-2f-stm32-2d-mw-2d-freertos-2f-Source

