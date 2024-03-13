### Task 1

##### delannoy

It computes the number of paths from the southwest corner (0, 0) of a rectangular grid to the northeast corner (m, n)

the parameter determines the size of our grid and it supprots a size up to 23 because larger would take too much time, it uses the recursive definition

$$ D(m,n) = \begin{cases}
1 \quad \text{if $m=0$ or $n=0$}\\ 
D(m-1,n) + D(m-1,n-1) + D(m, n-1) \quad \text{otherwise}
\end{cases}
$$

I measured it with ``time ./delannoy N`` and  ``/usr/bin/time -v ./delannoy N`` and chose parameters that show execution times form 1s to 1min and got the following results

| N    | 13     | 14     | 15      |
|------|--------|--------|---------|
| real | 1.747s | 9.791s | 55.440s |
| user | 1.734s | 9.781s | 55.344s |
| sys  | 0s     | 0.016s | 0s      |
| size | 544kB  | 544kB  | 548kB   |

##### filegene

It creates a number of directories containing a number of files with random content in it, i tried some parameters and i thought increasing the min file size to the same as the max of the default (1048576) would make a huge difference but in the example of 10 50 it increased the time by 78% which is not even double considering the min file size is more than 1000x larger, so the number of files/directories matter more than the size of the files, the impact of directories compared to files seems to be the same because equally many files get generated since 10 dirs x 100 files = 1000 files which is the same as for 100 dirs and 10 files

| default size | 10 50  | 50 10  | 30 100  | min=max | 10 50  | 100 100   |
|--------------|--------|--------|---------|---------|--------|-----------|
| real         | 1.900s | 1.922s | 11.354s | 1048576 | 3.374s | 1m10.714s |
| user         | 1.625s | 1.641s | 9.672s  |         | 3.063s | 1m0.250s  |
| sys          | 0.234s | 0.281s | 1.563s  |         | 0.313s | 6.031s    |
| size         | 1856kB | 1860kB | 1860kB  |         | 1632kB | 1632kB    |


##### filesearch

it recursively searches through a directory and all its sub dirs and files to find the largest file, there is no parameter that can be entered so it seems like it takes the current directory even tho it could be modified to take a path as an input

|      | time   |
|------|--------|
| real | 0.011s |
| user | 0s     |
| sys  | 0.016s |
| size | 728kB  |

##### mmul

It does some matrix multiplicatiosn with matrices size 1000x1000, compared to the examples above it uses way more memory than computing a number or creating files because there are way more intermediate values to be stored

|      | time    |
|------|---------|
| real | 0.742s  |
| user | 0.688s  |
| sys  | 0.031s  |
| size | 24028kB |

##### nbody

It simulates multiple forces applied to bodys in a 3D space

|      | time   |
|------|--------|
| real | 0.444s |
| user | 0.438s |
| sys  | 0.016s |
| size | 748kB  |

##### qap

It is an implementation of the Quadratic Assignment Problem which is to assign a set of facilities to a set of locations in such a way as to minimize the total assignment cost and is NP Hard, all problems until 18a have pretty similiar execution times and after that it increases a lot

|      | 15a    | 18a       |
|------|--------|-----------|
| real | 1.439s | 1m14.935s |
| user | 1.422s | 1m14.719s |
| sys  | 0.016s | 0s        |
| size | 636kB  | 644kB     |


### Task 2

I wrote a bash script that has a run function that can be used for every program, for eahc program it executes its 5 times with the same parameters and saves the wall clock times and max memory usages for every execution in an array each, next we calculate mean and variance for both metrics and finally we write it to a csv

i ran it on my system which has the following specs:

- Ryzen 5600x
- TridentZ 16GB DDR4-3200 CL16 Memory
- RTX 3080
- Samsung 970 Evo Plus M.2

from the tests in Task 1 i am not surprised about the mean and variance except in filegen the variance seems wrong the source is possibly due my handling of float operations after talking to colleagues 


| program                       | time_mean | time_var | memory_mean | memory_var |
|-------------------------------|-----------|----------|-------------|------------|
| ./delannoy 14                 | 10048     | 155      | 544         | 3          |
| ./filegen 30 100 1024 1048576 | 10446     | 212572   | 1858        | 4          |
| ./filesearch                  | 4         | 7        | 726         | 4          |
| ./mmul                        | 70        | 14       | 24027       | 2          |
| ./nbody                       | 43        | 0        | 745         | 4          |
| ./qap chr15c.dat              | 1026      | 1        | 637         | 4          |

on the LCC3 i got similiar results to my local machine

| program                       | time_mean | time_var | memory_mean | memory_var |
|-------------------------------|-----------|----------|-------------|------------|
| ./delannoy 14                 | 10044     | 492      | 544         | 0          |
| ./filegen 30 100 1024 1048576 | 10087     | 38       | 1856        | 0          |
| ./filesearch                  | 3         | 6        | 728         | 0          |
| ./mmul                        | 70        | 0        | 24024       | 0          |
| ./nbody                       | 44        | 0        | 746         | 4          |
| ./qap chr15c.dat              | 1029      | 1        | 634         | 4          |

i noticed i changed some directory structure so the path to chr15c.dat was false and it didnt read the file on the LCC3 and on my pc so i reran it and tried to fix the calculations by using the bc library but i still got an unusual value for the variance and on the LCC3 i got some dividing by 0 errors



