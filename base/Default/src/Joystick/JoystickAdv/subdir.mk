################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Joystick/JoystickAdv/joystickadv.cpp 

OBJS += \
./src/Joystick/JoystickAdv/joystickadv.o 

CPP_DEPS += \
./src/Joystick/JoystickAdv/joystickadv.d 


# Each subdirectory must supply rules for building sources it contributes
src/Joystick/JoystickAdv/%.o: ../src/Joystick/JoystickAdv/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


