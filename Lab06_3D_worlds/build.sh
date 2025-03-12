#!/bin/sh

clang++ ./Lab06_3D_worlds.cpp ./common/camera.cpp -lGLEW -lGL -lX11 -lGLU -lOpenGL -lglfw
if [ $? -eq 0 ]; then
    mv ./a.out ./main
    ./main
fi
