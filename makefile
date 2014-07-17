OBJS = 
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++0x -I"D:\work\projects\HttpServer\src" -I"D:\work\projects\HttpServer\unittests" $(DEBUG)
LFLAGS = -Wall $(DEBUG)
BIN_DIR = Debug
BIN_OUT = $(BIN_DIR)/HttpServer.exe

include src/subdir.mk
#include unittests/subdir.mk

HttpServer : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(BIN_OUT)

clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_OUT)
