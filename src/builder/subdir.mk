################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_BUILDER = ./src/builder
OBJ_DIR_BUILDER = ./$(BIN_DIR)/$(SRC_DIR_BUILDER)

# Add inputs and outputs 
CPP_SRCS += \
$(SRC_DIR_BUILDER)/PageBuilder.cpp \
$(SRC_DIR_BUILDER)/Templater.cpp \
$(SRC_DIR_BUILDER)/Decorator.cpp

OBJS += \
$(OBJ_DIR_BUILDER)/PageBuilder.o \
$(OBJ_DIR_BUILDER)/Templater.o \
$(OBJ_DIR_BUILDER)/Decorator.o

# Apply rule
$(OBJ_DIR_BUILDER)/%.o: $(SRC_DIR_BUILDER)/%.cpp
	$(CC) $(CFLAGS) -o "$@" "$<"
