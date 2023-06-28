#!/bin/bash

# Compile IPCServerDemo.cpp
g++ -std=c++11 -c IPCServerDemo.cpp

# Compile IPCClientDemo.cpp
g++ -std=c++11 -c IPCClientDemo.cpp

# Link with DEV.framework
g++ -o IPCClientDemo IPCClientDemo.o -L. -lmyframework -pthread
g++ -o IPCServerDemo IPCServerDemo.o -L. -lmyframework -pthread

# Run the program
./IPCServerDemo
