################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../nicatio/dmqi.cpp \
../nicatio/face.cpp \
../nicatio/filter.cpp \
../nicatio/hausdorff.cpp \
../nicatio/io.cpp \
../nicatio/math.cpp 

OBJS += \
./nicatio/dmqi.o \
./nicatio/face.o \
./nicatio/filter.o \
./nicatio/hausdorff.o \
./nicatio/io.o \
./nicatio/math.o 

CPP_DEPS += \
./nicatio/dmqi.d \
./nicatio/face.d \
./nicatio/filter.d \
./nicatio/hausdorff.d \
./nicatio/io.d \
./nicatio/math.d 


# Each subdirectory must supply rules for building sources it contributes
nicatio/%.o: ../nicatio/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"C:\opencv2.4.3\include\opencv" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


