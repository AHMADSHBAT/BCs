#!/bin/bash

# Create demoBuild directory if it doesn't exist
mkdir -p ./demoBuild

# Compile IPCServerDemo.cpp
g++ -std=c++11 -c IPCServerDemo.cpp -o ./demoBuild/IPCServerDemo.o

# Compile IPCClientDemo.cpp
g++ -std=c++11 -c IPCClientDemo.cpp -o ./demoBuild/IPCClientDemo.o

# Compile ShareMemDemo.cpp
g++ -std=c++11 -c ShareMemDemo.cpp -o ./demoBuild/ShareMemDemo.o

# Compile Stringdemo.cpp
g++ -std=c++11 -c Stringdemo.cpp -o ./demoBuild/Stringdemo.o

# Link with libmyframework.a
# Link with DEV.framework
g++ -o ./demoBuild/Stringdemo ./demoBuild/Stringdemo.o -L. -lmyframework
g++ -o ./demoBuild/ShareMemDemo ./demoBuild/ShareMemDemo.o -L. -lmyframework
g++ -o ./demoBuild/IPCClientDemo ./demoBuild/IPCClientDemo.o -L. -lmyframework -pthread
g++ -o ./demoBuild/IPCServerDemo ./demoBuild/IPCServerDemo.o -L. -lmyframework -pthread
