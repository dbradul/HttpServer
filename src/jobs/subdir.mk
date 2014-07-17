################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_JOBS = ./src/jobs
OBJ_DIR_JOBS = ./$(BIN_DIR)/$(SRC_DIR_JOBS)

# Add inputs and outputs
CPP_SRCS += \
$(SRC_DIR_JOBS)/IJobFactory.cpp \
$(SRC_DIR_JOBS)/JobFactoryGET.cpp \
$(SRC_DIR_JOBS)/JobFactoryPOST.cpp

OBJS += \
$(OBJ_DIR_JOBS)/IJobFactory.o \
$(OBJ_DIR_JOBS)/JobFactoryGET.o \
$(OBJ_DIR_JOBS)/JobFactoryPOST.o

# Apply rule
$(OBJ_DIR_JOBS)/%.o: $(SRC_DIR_JOBS)/%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
