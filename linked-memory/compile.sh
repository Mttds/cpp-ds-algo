#!/usr/bin/env bash

mkdir -p obj
mkdir -p bin

# we don't need to link explicitly with List.cpp compiled with
# -c into List.o because it's a template class and it's implementation
# is included into main.cpp when we include List.h because List.h includes List.cpp at the end
g++ main.cpp -o ./bin/main || exit 1
