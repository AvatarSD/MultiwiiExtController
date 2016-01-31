################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/consoleOut/PPMroutine.cpp \
../src/consoleOut/sonarsroutine.cpp 

OBJS += \
./src/consoleOut/PPMroutine.o \
./src/consoleOut/sonarsroutine.o 

CPP_DEPS += \
./src/consoleOut/PPMroutine.d \
./src/consoleOut/sonarsroutine.d 


# Each subdirectory must supply rules for building sources it contributes
src/consoleOut/%.o: ../src/consoleOut/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


