import subprocess
import time

command = (
    'cd "c:\\Users\\ZISU00\\Desktop\\Projects\\Projects\\JavaScript\\Backend\\CLI\\personal\\Coco\\tests\\standalone\\" && '
    '"c:\\Users\\ZISU00\\Desktop\\Projects\\Projects\\JavaScript\\Backend\\CLI\\personal\\Coco\\tests\\standalone\\test"'
)

num_runs = 10
execution_times = []

for _ in range(num_runs):
    start_time = time.time()
    subprocess.run(command, shell=True)
    end_time = time.time()
    execution_time = end_time - start_time
    execution_times.append(execution_time)

for i, time_taken in enumerate(execution_times, start=1):
    print(f"Run {i}: {time_taken:.2f} seconds")

average_time = sum(execution_times) / num_runs
print(f"Average time: {average_time:.2f} seconds")
