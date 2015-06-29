################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pwm.c \
../pwm_fun.c 

OBJS += \
./pwm.o \
./pwm_fun.o 

C_DEPS += \
./pwm.d \
./pwm_fun.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/home/bing/FriendlyARM-mini6410/linux-2.6.38/arch/arm/include -I/home/bing/FriendlyARM-mini6410/linux-2.6.38/arch/arm/plat-samsung/include -I/home/bing/FriendlyARM-mini6410/linux-2.6.38/include -I/home/bing/FriendlyARM-mini6410/linux-2.6.38/arch/arm/mach-s3c64xx/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


