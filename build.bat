@echo off
setlocal

set CONFIG=%1
if "%CONFIG%"=="" set CONFIG=Release

if /I not "%CONFIG%"=="Debug" if /I not "%CONFIG%"=="Release" (
    echo Usage: build.bat [Debug^|Release]
    exit /b 1
)

echo Configuring CMake project (%CONFIG%)...
cmake -S . -B build -DCMAKE_BUILD_TYPE=%CONFIG%
if errorlevel 1 (
    echo CMake configuration failed.
    exit /b 1
)

echo Building project (%CONFIG%)...
cmake --build build --config %CONFIG%
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded. Output is in build\%CONFIG%
endlocal
