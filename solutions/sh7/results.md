### Sheet 7

#### Task 1

I built the custom allocators and then built the allscale_api project with ```/usr/bin/time -v ninja``` with the default and then the custom allocators with LD_PRELOAD and got the following results.
 

|                  | default alloc | mimalloc | rpmalloc |
|------------------|---------------|----------|----------|
| CPU time (s)     | 607           | 627      | 620      |
| Wall time (s)    | 103           | 99       | 105      |
| Peak Memory (kb) | 586636        | 586424   | 585992   |

### Task 2
