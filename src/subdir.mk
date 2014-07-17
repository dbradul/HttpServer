################################################################################
# HttpServer
# DB, 2014
################################################################################

include ./src/builder/subdir.mk
include ./src/common/subdir.mk
include ./src/executor/subdir.mk
include ./src/jobs/subdir.mk
include ./src/protocol/subdir.mk

SRC_DIR = ./src
OBJ_DIR = ./$(BIN_DIR)/$(SRC_DIR)

# Add inputs and outputs
CPP_SRCS += \
$(SRC_DIR)/Main.cpp \
$(SRC_DIR)/Dispatcher.cpp

OBJS += \
$(OBJ_DIR)/Main.o \
$(OBJ_DIR)/Dispatcher.o \

# Apply rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
