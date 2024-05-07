##!/bin/bash

original_path=$(pwd)

# Build the small samples
cd ../../small_samples
rm -rf build
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS_RELEASE="-O1"
ninja

