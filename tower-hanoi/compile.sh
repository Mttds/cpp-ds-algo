#!/usr/bin/env bash

mkdir -p obj
mkdir -p bin

g++ -c main.cpp -o ./obj/main.o -I./include || exit 1
g++ -c cube.cpp -o ./obj/cube.o -I./include || exit 1
g++ -c stack.cpp -o ./obj/stack.o -I./include || exit 1
g++ -c game.cpp -o ./obj/game.o -I./include || exit 1
g++ -c HSLAPixel.cpp -o ./obj/HSLAPixel.o -I./include || exit 1

g++ ./obj/main.o ./obj/cube.o ./obj/stack.o ./obj/game.o ./obj/HSLAPixel.o -o ./bin/main
