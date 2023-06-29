#!/bin/bash

# Create demoBuild directory if it doesn't exist
mkdir -p ./demoBuild

# Compile ServerInetDemo.cpp
g++ -std=c++11 -c ServerInetDemo.cpp -o ./demoBuild/ServerInetDemo.o

# Compile ClientInetDemo.cpp
g++ -std=c++11 -c ClientInetDemo.cpp -o ./demoBuild/ClientInetDemo.o
g++ -std=c++11 -c ServerUnixDemo.cpp -o ./demoBuild/ServerUnixDemo.o
g++ -std=c++11 -c ClientUnixDemo.cpp -o ./demoBuild/ClientUnixDemo.o

# Compile ShareMemDemo.cpp
g++ -std=c++11 -c ShareMemDemo.cpp -o ./demoBuild/ShareMemDemo.o

# Compile Stringdemo.cpp
g++ -std=c++11 -c Stringdemo.cpp -o ./demoBuild/Stringdemo.o

# Link with libmyframework.a
# Link with DEV.framework
g++ -o ./demoBuild/Stringdemo ./demoBuild/Stringdemo.o -L. -lmyframework
g++ -o ./demoBuild/ShareMemDemo ./demoBuild/ShareMemDemo.o -L. -lmyframework
g++ -o ./demoBuild/ClientInetDemo ./demoBuild/ClientInetDemo.o -L. -lmyframework -pthread
g++ -o ./demoBuild/ServerUnixDemo ./demoBuild/ServerUnixDemo.o -L. -lmyframework -pthread
g++ -o ./demoBuild/ClientUnixDemo ./demoBuild/ClientUnixDemo.o -L. -lmyframework -pthread
g++ -o ./demoBuild/ServerInetDemo ./demoBuild/ServerInetDemo.o -L. -lmyframework -pthread
rm ./demoBuild/*.o
