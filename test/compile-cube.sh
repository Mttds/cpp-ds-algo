#!/usr/bin/env bash

mkdir -p obj
mkdir -p bin

g++ -c main.cpp -o ./obj/main.o -I./include || exit 1
g++ -c cube.cpp -o ./obj/cube.o -I./include || exit 1

g++ ./obj/main.o ./obj/cube.o -o ./bin/cube-main
