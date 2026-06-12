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
