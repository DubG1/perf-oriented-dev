### Task 1

#### npb_bt_a

there are only 2 functions that allocate memory with the biggest one being IO_file_doallocate with kbyes while fopen only allocates 488 bytes of the heap

![alt text](npb_sc.png)

the time difference was a lot with npb_bt_a taking 10x as long and ssca2 about 3x

|          | massif    | -         |
|----------|-----------|-----------|
| npb_bt_a | 11m8.557s | 1m10.825s |
| ssca2 17 | 1m4.970s  | 32.458s   |


#### ssca2 17

in this program there is a lot more going on with 24,5 mbytes of total heap consumption at one point, and the genScalData, computeGraph and betweennessCentrality functions taking up 4 mbytes each

![alt text](ssca2_sc.png)


### Task 2

the perf results are in a seperate file, the execution time with perf is pretty much the same comparing to the results from above without perf, there are minimal differences but these could be due to different loads on the LCC3 because i did both tasks on different days

- ssca2 has way higher L1 cache misses than npb_bt_a but LLC misses are the other way around with ssca2 having way lower misses than npb_bt_a
- dTLB is pretty minimal with only ssca2 having 13.20% misses
- both have almost 0 L1 icache and iTLB misses

|           | ssca2  | npb_bt_a |
|-----------|--------|----------|
| L1-dcache | 38.84% | 4.23%    |
| LL-cache  | 10.44% | 49.69%   |
