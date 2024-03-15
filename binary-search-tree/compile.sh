#!/usr/bin/env bash

mkdir -p bin

g++ main.cpp -o ./bin/main || exit 1