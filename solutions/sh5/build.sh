##!/bin/bash

original_path=$(pwd)

# Build the small samples
cd ../../small_samples
rm -rf build
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS="-O0"
ninja

cd "$original_path"

# Build the npb
cd ../../larger_samples/npb_bt
rm -rf build
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS="-O0"
ninja

cd "$original_path"

# Build the ssca2
cd ../../larger_samples/ssca2
rm -rf build
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS="-O0"
ninja