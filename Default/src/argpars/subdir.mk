################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/argpars/argparser.cpp 

OBJS += \
./src/argpars/argparser.o 

CPP_DEPS += \
./src/argpars/argparser.d 


# Each subdirectory must supply rules for building sources it contributes
src/argpars/%.o: ../src/argpars/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


