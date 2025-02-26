#!/bin/sh

clang++ ./Lab02_Basic_shapes.cpp ./common/shader.hpp -lGLEW -lGL -lX11 -lGLU -lOpenGL -lglfw
mv ./a.out main
