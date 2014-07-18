OBJS = 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++0x -I$(CURDIR)/src -I$(CURDIR)/unittests $(DEBUG)
LFLAGS = -Wall $(DEBUG)
BIN_DIR = Debug
BIN_OUT = $(BIN_DIR)/HttpServer.exe

include src/subdir.mk
#include unittests/subdir.mk

HttpServer : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_OUT)

#HttpServer_unittests : $(OBJS)
#	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_OUT)

clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_OUT)
