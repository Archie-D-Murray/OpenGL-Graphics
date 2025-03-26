#!/bin/sh

cflags=$(pkgconf glew glfw3 --libs)
clang++ ./*.cpp ./common/*.cpp $cflags -g -O0 -fno-limit-debug-info -std=c++20 -DGLM_CONFIG_CTOR_INIT=DGLM_CTOR_INIT_ENABLE
if [ $? -eq 0 ]; then
    mv ./a.out ./main
    ./main
fi
