#!/bin/bash

# Compile main.cpp
g++ -std=c++11 -c Stringdemo.cpp

# Link with libmyframework.a
g++ -o Stringdemo Stringdemo.o -L. -lmyframework
# Run the program
./Stringdemo
