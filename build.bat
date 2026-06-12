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

robocopy "build\_deps\flecs-build\%CONFIG%" "build\%CONFIG%" /E /Z /R:3 /W:5
robocopy "build\_deps\sdl_image-build\%CONFIG%" "build\%CONFIG%" /E /Z /R:3 /W:5
robocopy "build\_deps\sdl-build\%CONFIG%" "build\%CONFIG%" /E /Z /R:3 /W:5

set EXE=build\%CONFIG%\RPGGame.exe
if exist "%EXE%" (
    echo Running %EXE% ...
    "%EXE%"
) else (
    echo Could not find executable to run.
    exit /b 1
)

endlocal