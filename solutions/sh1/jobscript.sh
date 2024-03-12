#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name test
# Redirect output stream to this file
#SBATCH --output=output.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive


run() {
    command="$1"
    output_file="$2"

    # store intermediate results
    wall_clock_times=()
    max_memory_usages=()

    # loop to run the command 5 times
    for ((i=1; i<=3; i++)); do

        /usr/bin/time -v $command 2> temp_time_output.txt

        # Extract metrics
        wall_clock_time=$(grep "Elapsed (wall clock) time" temp_time_output.txt | awk '{print $NF}')
        # Extract minutes, seconds, and milliseconds
        minutes=$(echo "$wall_clock_time" | cut -d ':' -f 1)
        seconds=$(echo "$wall_clock_time" | cut -d ':' -f 2 | cut -d '.' -f 1)
        milliseconds=$(echo "$wall_clock_time" | cut -d ':' -f 2 | cut -d '.' -f 2)

        # Calculate ms, 10# prefix to fix leading 0s
        total_seconds=$((10#$minutes * 60 + 10#$seconds))
        total_milliseconds=$((10#$total_seconds * 1000 + 10#$milliseconds))

        max_memory_usage=$(grep "Maximum resident set size" temp_time_output.txt | awk '{print $NF}')

        wall_clock_times+=($total_milliseconds)
        max_memory_usages+=($max_memory_usage)

    done

    # mean
    t_sum=0
    for time in "${wall_clock_times[@]}"; do
        ((t_sum += time))
    done

    mean_time=$((t_sum / ${#wall_clock_times[@]}))

    # variance time
    t_var_sum=0
    for time in "${wall_clock_times[@]}"; do
        diff=$((time - mean_time))
        sq_difference=$((diff * diff))
        ((t_var_sum += sq_difference))
    done

    var_time=$((t_var_sum / ${#wall_clock_times[@]}))

    # mean memory
    m_sum=0
    for memory in "${max_memory_usages[@]}"; do
        ((m_sum += memory))
    done

    mean_memory=$((m_sum / ${#max_memory_usages[@]}))

    # variance memory
    m_var_sum=0
    for memory in "${max_memory_usages[@]}"; do
        diff=$((memory - mean_memory))
        sq_difference=$((diff * diff))
        ((m_var_sum += sq_difference))
    done

    var_memory=$((m_var_sum / ${#max_memory_usages[@]}))

    echo "$command, $mean_time, $var_time, $mean_memory, $var_memory" >> $output_file

    rm temp_time_output.txt
}

output_csv="performance_metrics.csv"

# add headers
echo "program, time_mean, time_variance, memory_mean, memory_variance" >> $output_csv

# run each program with parameters
run "./delannoy 14" $output_csv

run "./filegen 30 100 1024 1048576" $output_csv

run "./filesearch" $output_csv

run "./mmul" $output_csv

run "./nbody" $output_csv

run "./qap /home/georg/poc/perf-oriented-dev/small_samples/qap/problems/chr15c.dat" $output_csv
