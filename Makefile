CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
INCLUDE_DIR = $(CURDIR)/dev/String/api
SRC_DIR = $(CURDIR)/dev/String/src
BUILD_DIR = $(CURDIR)/dev/build
LIBRARY_NAME = libmyframework.a

CLIENT_SRC = $(CURDIR)/dev/IPC/ClientInet.cpp
SERVER_SRC = $(CURDIR)/dev/IPC/ServerInet.cpp
SHAREMEM_SRC = $(CURDIR)/dev/IPC/ShareMem.cpp
STRING_SRC = $(SRC_DIR)/DevString.cpp
SERVERUNIX_SRC = $(CURDIR)/dev/IPC/ServerUnix.cpp
CLIENTUNIX_SRC = $(CURDIR)/dev/IPC/ClientUnix.cpp

CLIENT_OBJ = $(BUILD_DIR)/ClientInet.o
SERVER_OBJ = $(BUILD_DIR)/ServerInet.o
SHAREMEM_OBJ = $(BUILD_DIR)/ShareMem.o
STRING_OBJ = $(BUILD_DIR)/DevString.o
SERVERUNIX_OBJ = $(BUILD_DIR)/ServerUnix.o
CLIENTUNIX_OBJ = $(BUILD_DIR)/ClientUnix.o

.PHONY: all clean

all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(CLIENT_OBJ) $(SERVER_OBJ) $(SHAREMEM_OBJ) $(STRING_OBJ) $(SERVERUNIX_OBJ) $(CLIENTUNIX_OBJ)
	ar rcs $@ $^

$(CLIENT_OBJ): $(CLIENT_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(SHAREMEM_OBJ): $(SHAREMEM_SRC)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(STRING_OBJ): $(STRING_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVERUNIX_OBJ): $(SERVERUNIX_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENTUNIX_OBJ): $(CLIENTUNIX_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(LIBRARY_NAME)
	rm -rf *.o *.a
	rm -rf ./demoBuild/*
