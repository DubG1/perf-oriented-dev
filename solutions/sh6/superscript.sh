#!/bin/bash

sbatch ./scripts/tiled32.sh
sbatch ./scripts/tiled64.sh
sbatch ./scripts/tiled128.sh
sbatch ./scripts/tiled256.sh
sbatch ./scripts/tiled512.sh
sbatch ./scripts/tiled1024.sh
