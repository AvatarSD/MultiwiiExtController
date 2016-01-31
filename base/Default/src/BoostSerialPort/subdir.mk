################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BoostSerialPort/BSerialPort.cpp 

OBJS += \
./src/BoostSerialPort/BSerialPort.o 

CPP_DEPS += \
./src/BoostSerialPort/BSerialPort.d 


# Each subdirectory must supply rules for building sources it contributes
src/BoostSerialPort/%.o: ../src/BoostSerialPort/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


