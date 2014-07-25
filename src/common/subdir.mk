################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_COMMON = ./src/common
OBJ_DIR_COMMON = ./$(BIN_DIR)/$(SRC_DIR_COMMON)

# Add inputs and outputs 
CPP_SRCS += \
$(SRC_DIR_COMMON)/File.cpp \
$(SRC_DIR_COMMON)/Config.cpp \
$(SRC_DIR_COMMON)/Utils.cpp

OBJS += \
$(OBJ_DIR_COMMON)/File.o \
$(OBJ_DIR_COMMON)/Config.o \
$(OBJ_DIR_COMMON)/Utils.o

# Apply rules
$(OBJ_DIR_COMMON)/%.o: $(SRC_DIR_COMMON)/%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"


