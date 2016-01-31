################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PPM/ppm.cpp 

OBJS += \
./src/PPM/ppm.o 

CPP_DEPS += \
./src/PPM/ppm.d 


# Each subdirectory must supply rules for building sources it contributes
src/PPM/%.o: ../src/PPM/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


