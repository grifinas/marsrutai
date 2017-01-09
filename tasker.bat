@echo off

SET oos=-IA:\Qt\5.8\msvc2015_64\include ^
    -IA:\Qt\5.8\msvc2015_64\include\QtQuick ^
    -IA:\Qt\5.8\msvc2015_64\include\QtGui ^
    -IA:\Qt\5.8\msvc2015_64\include\QtANGLE ^
    -IA:\Qt\5.8\msvc2015_64\include\QtQml ^
    -IA:\Qt\5.8\msvc2015_64\include\QtNetwork ^
    -IA:\Qt\5.8\msvc2015_64\include\QtCore ^
    -Idebug ^
    -IA:\Qt\5.8\msvc2015_64\mkspecs\win32-msvc2015 ^
    -IC:\Users\juris\Desktop\ogl-OpenGL-tutorial_0015_33\external\glfw-3.1.2\include ^
    -IA:\git_repos\marsrutai\headers
    

if "%1" == "compile" (
    cd obj
    g++ -ggdb -std=c++14 -c %oos% ../src/*.cpp
    cd ..
    g++ -ggdb -std=c++14 %oos% ./obj/*.o -o marsrutai.exe
    REM del "./*.o"
    
    if %ERRORLEVEL% NEQ 0 EXIT \B
    shift
) 
if "%1" == "" echo compiled successfully
if "%1" == "run" marsrutai.exe | tee log.txt
