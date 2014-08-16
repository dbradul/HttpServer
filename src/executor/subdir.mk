################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_EXECUTOR = ./src/executor
OBJ_DIR_EXECUTOR = ./$(BIN_DIR)/$(SRC_DIR_EXECUTOR)

# Add inputs and outputs
CPP_SRCS += \
$(SRC_DIR_EXECUTOR)/IJob.cpp \
$(SRC_DIR_EXECUTOR)/JobExecutor.cpp \
$(SRC_DIR_EXECUTOR)/JobFactory.cpp \

OBJS += \
$(OBJ_DIR_EXECUTOR)/IJob.o \
$(OBJ_DIR_EXECUTOR)/JobExecutor.o \
$(OBJ_DIR_EXECUTOR)/JobFactory.o

# Apply rules
$(OBJ_DIR_EXECUTOR)/%.o: $(SRC_DIR_EXECUTOR)/%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
