import subprocess
import re
import statistics
import sys

def run(command, output_file, raw_output):

    #store immediate results
    wall_clock_times = []

    for i in range(3):
        full_command = f"/usr/bin/time -v {command}"
        time_output = subprocess.run(full_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)

        #extract metrics and transform
        wall_clock_time_match = re.search(r"Elapsed \(wall clock\) time \(h:mm:ss or m:ss\): (\d+):(\d+\.\d+)", time_output.stderr)

        if wall_clock_time_match:
            minutes = int(wall_clock_time_match.group(1))
            seconds = float(wall_clock_time_match.group(2))
            total_milliseconds = minutes * 60 * 1000 + seconds * 1000
        else:
            print("Error: Failed to extract wall clock time")


        wall_clock_times.append(total_milliseconds)

        #save raw data
        with open(raw_output, "a") as raw_f:
            raw_f.write(f"{command}, {total_milliseconds}\n")


    #time
    mean_time = statistics.mean(wall_clock_times)
    var_time = statistics.variance(wall_clock_times)


    #save results
    with open(output_file, "a") as f:
        f.write(f"{command}, {mean_time:.2f}, {var_time:.2f}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 benchmark.py <command>")
        sys.exit(1)
        
    name = sys.argv[1]

    cmd = " ".join(sys.argv[1:])
    print(cmd)

    output_csv = cmd + "_metrics.csv"
    raw_output_csv = cmd + "_raw.csv"

    #reset csv and add headers
    open(output_csv, 'w').close()
    open(raw_output_csv, 'w').close()

    with open(output_csv, "a") as f:
        f.write("program, time_mean, time_variance\n")
    
    #run command and write results
    run("./" + cmd, output_csv, raw_output_csv)
