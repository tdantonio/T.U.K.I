################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/protocolo.c \
../src/shared.c \
../src/sockets.c 

C_DEPS += \
./src/protocolo.d \
./src/shared.d \
./src/sockets.d 

OBJS += \
./src/protocolo.o \
./src/shared.o \
./src/sockets.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/protocolo.d ./src/protocolo.o ./src/shared.d ./src/shared.o ./src/sockets.d ./src/sockets.o

.PHONY: clean-src

