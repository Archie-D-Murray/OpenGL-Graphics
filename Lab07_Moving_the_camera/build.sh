#!/bin/sh

cflags=$(pkgconf glew glfw3 --libs)
clang++ ./*.cpp ./common/*.cpp $cflags
if [ $? -eq 0 ]; then
    mv ./a.out ./main
    ./main
fi
