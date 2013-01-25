################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../nicatio/face.cpp \
../nicatio/filter.cpp \
../nicatio/hausdorff.cpp \
../nicatio/math.cpp 

OBJS += \
./nicatio/face.o \
./nicatio/filter.o \
./nicatio/hausdorff.o \
./nicatio/math.o 

CPP_DEPS += \
./nicatio/face.d \
./nicatio/filter.d \
./nicatio/hausdorff.d \
./nicatio/math.d 


# Each subdirectory must supply rules for building sources it contributes
nicatio/%.o: ../nicatio/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\opencv2.4.3\include\opencv" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


