################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_PROTOCOL = ./src/protocol
OBJ_DIR_PROTOCOL = ./$(BIN_DIR)/$(SRC_DIR_PROTOCOL)

# Add inputs and outputs
CPP_SRCS += \
$(SRC_DIR_PROTOCOL)/Constants.cpp \
$(SRC_DIR_PROTOCOL)/Message.cpp \
$(SRC_DIR_PROTOCOL)/Request.cpp \
$(SRC_DIR_PROTOCOL)/Response.cpp

OBJS += \
$(OBJ_DIR_PROTOCOL)/Constants.o \
$(OBJ_DIR_PROTOCOL)/Message.o \
$(OBJ_DIR_PROTOCOL)/Request.o \
$(OBJ_DIR_PROTOCOL)/Response.o

# Apply rules
$(OBJ_DIR_PROTOCOL)/%.o: $(SRC_DIR_PROTOCOL)/%.cpp
	$(dir_guard)
	$(CC) $(CFLAGS) -o "$@" "$<"
