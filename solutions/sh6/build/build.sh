#!/bin/bash

for opt_flag in O0 O1 O2 O3 Os Ofast; do
    gcc -${opt_flag} -o mmul_${opt_flag} mmul.c
    gcc -${opt_flag} -o mmul_tiled_${opt_flag} mmul_tiled.c
done
