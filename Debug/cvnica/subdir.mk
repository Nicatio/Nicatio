################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cvnica/cvdmqi.cpp 

OBJS += \
./cvnica/cvdmqi.o 

CPP_DEPS += \
./cvnica/cvdmqi.d 


# Each subdirectory must supply rules for building sources it contributes
cvnica/%.o: ../cvnica/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\opencv2.4.3\include\opencv" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

