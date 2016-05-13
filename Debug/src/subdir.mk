################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Auto\ Instrucional\ ED2.c 

OBJS += \
./src/Auto\ Instrucional\ ED2.o 

C_DEPS += \
./src/Auto\ Instrucional\ ED2.d 


# Each subdirectory must supply rules for building sources it contributes
src/Auto\ Instrucional\ ED2.o: ../src/Auto\ Instrucional\ ED2.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Auto Instrucional ED2.d" -MT"src/Auto\ Instrucional\ ED2.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


