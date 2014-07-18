################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_CORE = ./src/core
OBJ_DIR_CORE = ./$(BIN_DIR)/$(SRC_DIR_CORE)

# Add inputs and outputs
CPP_SRCS += \
$(SRC_DIR_CORE)/Server.cpp \
$(SRC_DIR_CORE)/Connector.cpp

OBJS += \
$(OBJ_DIR_CORE)/Server.o \
$(OBJ_DIR_CORE)/Connector.o

# Apply rules
$(OBJ_DIR_CORE)/%.o: $(SRC_DIR_CORE)/%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
