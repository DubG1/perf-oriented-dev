import subprocess
import re
import statistics

def run(command, output_file, raw_output):

    #store immediate results
    wall_clock_times = []
    max_memory_usages = []

    loadgen = "./tools/load_generator/exec_with_workstation_heavy.sh"

    for i in range(3):
        full_command = f"/usr/bin/time -v {command}"
        time_output = subprocess.run(full_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
        print(time_output.stderr)

        #extract metrics and transform
        wall_clock_time_match = re.search(r"Elapsed \(wall clock\) time \(h:mm:ss or m:ss\): (\d+):(\d+\.\d+)", time_output.stderr)

        if wall_clock_time_match:
            minutes = int(wall_clock_time_match.group(1))
            seconds = float(wall_clock_time_match.group(2))
            total_milliseconds = minutes * 60 * 1000 + seconds * 1000
        else:
            print("Error: Failed to extract wall clock time")

        max_memory_usage_match = re.search(r"Maximum resident set size \(kbytes\): (\d+)", time_output.stderr)
        max_memory_usage = max_memory_usage_match.group(1) if max_memory_usage_match else "0"

        wall_clock_times.append(total_milliseconds)
        max_memory_usages.append(int(max_memory_usage))

        #save raw data
        with open(raw_output, "a") as raw_f:
            raw_f.write(f"{command}, {total_milliseconds}, {max_memory_usage}\n")

    #time
    mean_time = statistics.mean(wall_clock_times)
    var_time = statistics.variance(wall_clock_times)

    #memory
    mean_memory = statistics.mean(max_memory_usages)
    var_memory = statistics.variance(max_memory_usages)

    #save results
    with open(output_file, "a") as f:
        f.write(f"{command}, {mean_time:.2f}, {var_time:.2f}, {mean_memory:.2f}, {var_memory:.2f}\n")

#reset csv and add headers
output_csv = "performance_metrics.csv"
raw_output_csv = "raw_data.csv"
open(output_csv, 'w').close()
open(raw_output_csv, 'w').close()

with open(output_csv, "a") as f:
    f.write("program, time_mean, time_variance, memory_mean, memory_variance\n")

#run each program with parameters
run("./small_samples/build/mmul", output_csv, raw_output_csv)
