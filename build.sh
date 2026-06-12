#!/usr/bin/env bash
set -e

CONFIG="${1:-Release}"

if [[ "$CONFIG" != "Debug" && "$CONFIG" != "Release" ]]; then
    echo "Usage: ./build.sh [Debug|Release]"
    exit 1
fi

echo "Configuring CMake project ($CONFIG)..."
cmake -S . -B build -DCMAKE_BUILD_TYPE="$CONFIG"

echo "Building project ($CONFIG)..."
cmake --build build --config "$CONFIG" -- -j"$(nproc)"

echo "Build succeeded. Output is in build/"
cp "./build/_deps/flecs-build/$CONFIG/flecs.dll" "./build/$CONFIG/"
cp "./build/_deps/sdl_image-build/$CONFIG/SDL3_image.dll" "./build/$CONFIG/" 
cp "./build/_deps/sdl-build/$CONFIG/SDL3.dll" "./build/$CONFIG/"


EXE="build/RPGGame"
if [[ -f "build/$CONFIG/RPGGame" ]]; then
    EXE="build/$CONFIG/RPGGame"
fi

if [[ -f "$EXE" ]]; then
    echo "Running $EXE ..."
    "$EXE"
else
    echo "Could not find executable to run."
    exit 1
fi
