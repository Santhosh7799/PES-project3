################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/analysis.c \
../Sources/circbuf.c \
../Sources/data.c \
../Sources/log.c \
../Sources/main.c \
../Sources/rtc.c \
../Sources/uart.c 

OBJS += \
./Sources/analysis.o \
./Sources/circbuf.o \
./Sources/data.o \
./Sources/log.o \
./Sources/main.o \
./Sources/rtc.o \
./Sources/uart.o 

C_DEPS += \
./Sources/analysis.d \
./Sources/circbuf.d \
./Sources/data.d \
./Sources/log.d \
./Sources/main.d \
./Sources/rtc.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL25Z128VLK4" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL25Z4/include" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


