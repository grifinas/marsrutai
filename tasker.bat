@echo off
SET t=%1
CALL %2 %3 %4 %5 %6 %7 %8 %9
if %ERRORLEVEL% NEQ 0 EXIT \B
if "%t%" == "and_run" a.exe
if "%t%" == "compile" echo "compiled successfully"