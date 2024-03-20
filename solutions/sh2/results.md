### Task 1

I was struggling a lot to make it work i ran it once with the exec_with_workstation_heavy.sh loadgenerator (1) and once without it (2). i dont think i actually could get the load generator to work with my script, it works when executing a single program with it the task gives so little information, ive tried for about 4 hours but these are my results

(1)

program|time_mean|time_variance|memory_mean|memory_variance
---|---|---|---|---
./small_samples/build/delannoy 14|26360.00|100.00|1352.00|112.00
./small_samples/build/filegen 30 100 1024 1048576|7086.67|8033.33|2477.33|3301.33
./small_samples/build/filesearch|203.33|100833.33|1528.00|448.00
./small_samples/build/mmul|2120.00|7500.00|24640.00|4368.00
./small_samples/build/nbody|2593.33|533.33|1873.33|3845.33
./small_samples/build/qap chr15c.dat|290.00|300.00|1380.00|6736.00

(2)

program|time_mean|time_variance|memory_mean|memory_variance
---|---|---|---|---
./small_samples/build/delannoy 14|26216.67|33.33|1345.33|3077.33
./small_samples/build/filegen 30 100 1024 1048576|9853.33|100133.33|2508.00|7248.00
./small_samples/build/filesearch|100.00|16900.00|1482.67|8789.33
./small_samples/build/mmul|2073.33|33.33|24525.33|69.33
./small_samples/build/nbody|2580.00|0.00|1894.67|1925.33
./small_samples/build/qap chr15c.dat|276.67|33.33|1410.67|10325.33

### Task 2

I created a simple program that creates a file and writes random characters to a  file, it is possible to specify size of the write operation and operations per second, ive only briefly tried it out but couldnt measure any impact again like in task1, i did not benchmark it because i had spent so much time on task 1