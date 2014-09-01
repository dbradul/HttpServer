################################################################################
# HttpServer
# DB, 2014
################################################################################

include ./src/builder/subdir.mk
include ./src/common/subdir.mk
include ./src/executor/subdir.mk
include ./src/protocol/subdir.mk
include ./src/core/subdir.mk

SRC_DIR = ./src
OBJ_DIR = ./$(BIN_DIR)/$(SRC_DIR)

# Add inputs and outputs
#CPP_SRCS += \
#$(SRC_DIR)/Main.cpp

OBJ_MAIN = \
$(OBJ_DIR)/Main.o

# Apply rules
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
#	$(CC) $(CFLAGS) -o "$@" "$<"

$(OBJ_DIR)/Main.o: $(SRC_DIR)/Main.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
