@echo off
clang++ -o main.exe .\Lab05_Transformations.cpp ../lib/*.lib -I ..\include\ -lopengl32 -lgdi32 -lwinmm -luser32 -lshell32 -lkernel32 -lmsvcrt -nostdlib
if %ERRORLEVEL% == 0 main.exe
