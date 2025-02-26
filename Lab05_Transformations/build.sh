#!/bin/sh

clang++ ./Lab05_Transformations.cpp -o main -lGLEW -lGL -lX11 -lGLU -lOpenGL -lglfw
if [ $? -eq 0 ]; then
    ./main
fi
