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