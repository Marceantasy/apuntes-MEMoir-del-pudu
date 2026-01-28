#!/bin/bash

g++ -g -O2 -std=c++20 -pedantic -Wall -Wextra -o tmp $1.cpp
echo running
valgrind -q ./tmp