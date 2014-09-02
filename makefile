OBJS = 
OBJS_UNITTESTS =
CC = g++-4.8
DEBUG = -g
CFLAGS = -Wall -c -std=c++0x -I$(CURDIR)/src -I$(CURDIR)/unittests $(DEBUG)
LFLAGS = -Wall $(DEBUG)
BIN_DIR = Debug

ifeq ($(OS),Windows_NT)
	BIN_OUT = $(BIN_DIR)/HttpServer.exe
	BIN_OUT_UNITTESTS = $(BIN_DIR)/HttpServer_unittests.exe
else
	BIN_OUT = $(BIN_DIR)/HttpServer
	BIN_OUT_UNITTESTS = $(BIN_DIR)/HttpServer_unittests
endif

dir_guard=@mkdir -p $(@D)

All : HttpServer HttpServer_unittests

include src/subdir.mk
include unittests/subdir.mk

HttpServer : $(OBJS) $(OBJ_MAIN)
	$(CC) $(LFLAGS) $(OBJS) $(OBJ_MAIN) -o $(BIN_OUT)

HttpServer_unittests : $(OBJS) $(OBJS_UNITTESTS)
	$(CC) $(LFLAGS) $(OBJS) $(OBJS_UNITTESTS) -o $(BIN_OUT_UNITTESTS)

clean:
	rm -rf $(BIN_DIR)