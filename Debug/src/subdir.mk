################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ExportHandle.cpp \
../src/SourceHandle.cpp \
../src/SqlHandle.cpp \
../src/StatOutput.cpp \
../src/task.cpp 

OBJS += \
./src/ExportHandle.o \
./src/SourceHandle.o \
./src/SqlHandle.o \
./src/StatOutput.o \
./src/task.o 

CPP_DEPS += \
./src/ExportHandle.d \
./src/SourceHandle.d \
./src/SqlHandle.d \
./src/StatOutput.d \
./src/task.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


