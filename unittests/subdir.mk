################################################################################
# HttpServer
# DB, 2014
################################################################################

SRC_DIR_UNITTESTS = ./unittests
OBJ_DIR_UNITTESTS = ./$(BIN_DIR)/$(SRC_DIR_UNITTESTS)

# Add inputs and outputs 
CPP_SRCS += \
$(SRC_DIR_UNITTESTS)/TestSuit.cpp \
$(SRC_DIR_UNITTESTS)/FileTest.cpp \
$(SRC_DIR_UNITTESTS)/PageBuilderTest.cpp \
$(SRC_DIR_UNITTESTS)/TemplaterTest.cpp

OBJS_UNITTESTS += \
$(OBJ_DIR_UNITTESTS)/TestSuit.o \
$(OBJ_DIR_UNITTESTS)/FileTest.o \
$(OBJ_DIR_UNITTESTS)/PageBuilderTest.o \
$(OBJ_DIR_UNITTESTS)/TemplaterTest.o

# Apply rule
$(OBJ_DIR_UNITTESTS)/%.o: $(SRC_DIR_UNITTESTS)/%.cpp
	$(dir_guard)
	$(CC) $(CFLAGS) -o "$@" "$<"


