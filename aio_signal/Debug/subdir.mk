################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../aio_signal.mod.o \
../aio_signal.o 

C_SRCS += \
../aio_signal.c \
../aio_signal.mod.c \
../test_aio_signal.c 

OBJS += \
./aio_signal.o \
./aio_signal.mod.o \
./test_aio_signal.o 

C_DEPS += \
./aio_signal.d \
./aio_signal.mod.d \
./test_aio_signal.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


