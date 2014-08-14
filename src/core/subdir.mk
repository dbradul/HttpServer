################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_CORE = ./src/core
OBJ_DIR_CORE = ./$(BIN_DIR)/$(SRC_DIR_CORE)

# Add inputs and outputs
CPP_SRCS += \
$(SRC_DIR_CORE)/Dispatcher.cpp \
$(SRC_DIR_CORE)/Connection.cpp

OBJS += \
$(OBJ_DIR_CORE)/Dispatcher.o \
$(OBJ_DIR_CORE)/Connection.o

# Apply rules
$(OBJ_DIR_CORE)/%.o: $(SRC_DIR_CORE)/%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
