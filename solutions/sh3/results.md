### Task1

added set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg") to the CMakeList to use it with gprof
then did gprof npb_bt_.. gmon.out > res.txt to save the output

my time was 0 for some reason for all programs so i recompiled them like one of my friends with
``cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_FLAGS="-pg" -DCMAKE_CXX_FLAGS="-pg"``

but that didnt change anything either so i can only look at the calls, the first 3 functions have the exact same number of calls so i guess they are related to each other, i cant really say much about time because how often a function is called doesnt say anything about its execution time

npb_bt_a

| %     | cumulative | self | self    | total   |           
|------|------------|------|---------|---------|  
| time | seconds    | seconds | calls | Ts/call | Ts/call | name           
| ---- | ---------- | ------- | ------| --------| ------- | ----           
| 0.00 | 0.00       | 0.00    | 146029716 | 0.00 | 0.00  | binvcrhs       
| 0.00 | 0.00       | 0.00    | 146029716 | 0.00 | 0.00  | matmul_sub     
| 0.00 | 0.00       | 0.00    | 146029716 | 0.00 | 0.00  | matvec_sub     
| 0.00 | 0.00       | 0.00    | 4195072   | 0.00 | 0.00  | exact_solution 
| 0.00 | 0.00       | 0.00    | 2317932   | 0.00 | 0.00  | binvrhs        
| 0.00 | 0.00       | 0.00    | 2317932   | 0.00 | 0.00  | lhsinit        
| 0.00 | 0.00       | 0.00    | 202       | 0.00 | 0.00  | compute_rhs    
| 0.00 | 0.00       | 0.00    | 201       | 0.00 | 0.00  | x_solve        
| 0.00 | 0.00       | 0.00    | 201       | 0.00 | 0.00  | y_solve        
| 0.00 | 0.00       | 0.00    | 201       | 0.00 | 0.00  | z_solve        
| 0.00 | 0.00       | 0.00    | 2         | 0.00 | 0.00  | wtime_         
| 0.00 | 0.00       | 0.00    | 1         | 0.00 | 0.00  | error_norm     
| 0.00 | 0.00       | 0.00    | 1         | 0.00 | 0.00  | rhs_norm      

npb_bt_b

| %     | cumulative | self | self    | total   |           
|------|------------|------|---------|---------|  
| time | seconds    | seconds | calls | Ts/call | Ts/call | name           
| ---- | ---------- | ------- | ------| --------| ------- | ----           
| 0.00 | 0.00       | 0.00    | 609030000 | 0.00 | 0.00  | binvcrhs       
| 0.00 | 0.00       | 0.00    | 609030000 | 0.00 | 0.00  | matmul_sub     
| 0.00 | 0.00       | 0.00    | 609030000 | 0.00 | 0.00  | matvec_sub     
| 0.00 | 0.00       | 0.00    | 16980552   | 0.00 | 0.00  | exact_solution 
| 0.00 | 0.00       | 0.00    | 6030000    | 0.00 | 0.00  | binvrhs        
| 0.00 | 0.00       | 0.00    | 6030000    | 0.00 | 0.00  | lhsinit        
| 0.00 | 0.00       | 0.00    | 202        | 0.00 | 0.00  | compute_rhs    
| 0.00 | 0.00       | 0.00    | 201        | 0.00 | 0.00  | x_solve        
| 0.00 | 0.00       | 0.00    | 201        | 0.00 | 0.00  | y_solve        
| 0.00 | 0.00       | 0.00    | 201        | 0.00 | 0.00  | z_solve        
| 0.00 | 0.00       | 0.00    | 2          | 0.00 | 0.00  | wtime_         
| 0.00 | 0.00       | 0.00    | 1          | 0.00 | 0.00  | error_norm     
| 0.00 | 0.00       | 0.00    | 1          | 0.00 | 0.00  | rhs_norm      

on the LCC3 i got some results

npb_bt_a

binvchrs consumes the most time because it is called often just like matmul_sub
compute_rhs, y_solve, x_solve and z_solve seem to be more complex since they are called far less times but still consume a significant amout of time, they could be adjusted to improve the performance of our program 

| Time (%) | Cumulative (seconds) | Self (seconds) | Calls     | ms/call | ms/call | Name              |
|----------|----------------------|----------------|-----------|---------|---------|-------------------|
| 27.07    | 22.61                | 22.61          | 146029716 | 0.00    | 0.00    | binvcrhs          |
| 16.34    | 36.26                | 13.65          | 146029716 | 0.00    | 0.00    | matmul_sub        |
| 14.51    | 48.39                | 12.12          | 202       | 60.01   | 60.01   | compute_rhs       |
| 12.39    | 58.74                | 10.35          | 201       | 51.50   | 119.83  | y_solve           |
| 12.16    | 68.90                | 10.16          | 201       | 50.55   | 118.89  | z_solve           |
| 9.88     | 77.15                | 8.25           | 201       | 41.05   | 109.38  | x_solve           |
| 5.44     | 81.69                | 4.54           | 146029716 | 0.00    | 0.00    | matvec_sub        |
| 1.42     | 82.88                | 1.19           |           |         |         | add               |
| 0.38     | 83.20                | 0.32           | 2317932   | 0.00    | 0.00    | lhsinit           |
| 0.12     | 83.30                | 0.10           |           |         |         | set_constants     |
| 0.12     | 83.40                | 0.10           | 4195072   | 0.00    | 0.00    | exact_solution    |
| 0.10     | 83.48                | 0.08           | 2317932   | 0.00    | 0.00    | binvrhs           |
| 0.05     | 83.52                | 0.04           |           |         |         | exact_rhs         |
| 0.01     | 83.53                | 0.01           | 1         | 10.00   | 16.25   | error_norm        |
| 0.01     | 83.54                | 0.01           |           |         |         | initialize        |
| 0.00     | 83.54                | 0.00           | 2         | 0.00    | 0.00    | wtime_            |
| 0.00     | 83.54                | 0.00           | 1         | 0.00    | 0.00    | rhs_norm          |

npb_bt_b

comparing to npb_bt_b we can see almost the same percentages but the number of calls of compute_rhs and the solve functions is still the same but the time is longer which is interesting, all other functions are called way more often leading to a longer execution time

| Time (%) | Cumulative (seconds) | Self (seconds) | Calls     | ms/call | ms/call | Name              |
|----------|----------------------|----------------|-----------|---------|---------|-------------------|
| 27.97    | 93.85                | 93.85          | 609030000 | 0.00    | 0.00    | binvcrhs          |
| 16.59    | 149.54               | 55.69          | 609030000 | 0.00    | 0.00    | matmul_sub        |
| 13.52    | 194.91               | 45.37          | 202       | 224.59  | 224.59  | compute_rhs       |
| 13.18    | 239.14               | 44.24          | 201       | 220.08  | 494.79  | z_solve           |
| 12.06    | 279.60               | 40.46          | 201       | 201.27  | 475.99  | y_solve           |
| 10.33    | 314.26               | 34.66          | 201       | 172.46  | 447.18  | x_solve           |
| 4.43     | 329.14               | 14.88          | 609030000 | 0.00    | 0.00    | matvec_sub        |
| 1.25     | 333.34               | 4.19           |           |         |         | add               |
| 0.24     | 334.15               | 0.81           | 6030000   | 0.00    | 0.00    | lhsinit           |
| 0.13     | 334.58               | 0.43           | 16980552  | 0.00    | 0.00    | exact_solution    |
| 0.13     | 335.00               | 0.42           | 6030000   | 0.00    | 0.00    | binvrhs           |
| 0.08     | 335.27               | 0.27           |           |         |         | set_constants     |
| 0.07     | 335.52               | 0.25           |           |         |         | exact_rhs         |
| 0.03     | 335.62               | 0.10           |           |         |         | initialize        |
| 0.00     | 335.63               | 0.01           | 1         | 10.00   | 10.00   | rhs_norm          |
| 0.00     | 335.63               | 0.00           | 2         | 0.00    | 0.00    | wtime_            |
| 0.00     | 335.63               | 0.00           | 1         | 0.00    | 26.88   | error_norm        |
