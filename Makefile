CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
INCLUDE_DIR = $(CURDIR)/dev/String/api
SRC_DIR = $(CURDIR)/dev/String/src
BUILD_DIR = $(CURDIR)/dev/build
LIBRARY_NAME = libmyframework.a

CLIENT_SRC = $(CURDIR)/dev/IPC/transport_client.cpp
SERVER_SRC = $(CURDIR)/dev/IPC/transport_server.cpp
STRING_SRC = $(SRC_DIR)/DevString.cpp

CLIENT_OBJ = $(BUILD_DIR)/transport_client.o
SERVER_OBJ = $(BUILD_DIR)/transport_server.o
STRING_OBJ = $(BUILD_DIR)/DevString.o

.PHONY: all clean

all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(CLIENT_OBJ) $(SERVER_OBJ) $(STRING_OBJ)
	ar rcs $@ $^

$(CLIENT_OBJ): $(CLIENT_SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)


$(STRING_OBJ): $(STRING_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(LIBRARY_NAME)
	rm -rf *.o *.a
