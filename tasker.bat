@echo off
if "%1" == "compile" (
    g++ -g -std=c++11 testing.cpp 
    if %ERRORLEVEL% NEQ 0 EXIT \B
    shift
) 
if "%1" == "" echo "compiled successfully"
if "%1" == "run" a.exe
