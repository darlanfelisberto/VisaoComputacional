################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../deteccaoFacial.cpp 

OBJS += \
./deteccaoFacial.o 

CPP_DEPS += \
./deteccaoFacial.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/opencv2/highgui -I/usr/include/opencv2/imgproc -I/usr/include/opencv2/legacy -I/usr/include/opencv2/ml -I/usr/include/opencv2/objdetect -I/usr/include/opencv2/video -I/usr/include/opencv2/objdetect -I/usr/include/opencv2 -I/usr/include/opencv -I/usr/include/opencv2/core -I/usr/include/opencv2/features2d -I/usr/include/opencv2/flann -I/usr/include/opencv2/gpu -I/usr/include/opencv2/calib3d -I/usr/include/opencv2/contrib -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


