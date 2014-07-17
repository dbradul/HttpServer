################################################################################
# HttpServer
# DB, 2014
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./unittests/AllTests.cpp

OBJS += \
./Debug/unittests/AllTests.o

# Each subdirectory must supply rules for building sources it contributes
Debug/unittests/%.o: ./unittests/%.cpp
	$(CC) $(CFLAGS) "$<"


