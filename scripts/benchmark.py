import subprocess
import time
import csv

sizes = [100, 500, 1000, 2500, 4000, 5000]
algorithms = ["fifo", "sjf", "rr"]

results = []

for size in sizes:

    subprocess.run(
        ["python", "scripts/generate_process.py", str(size)],
        check=True
    )

    file = f"data/inputs/processes_{size}.csv"

    for alg in algorithms:

        start = time.perf_counter()

        subprocess.run(
            ["./bin/main.exe", alg, file],
            stdout=subprocess.DEVNULL
        )

        end = time.perf_counter()

        results.append({
            "algorithm": alg,
            "size": size,
            "time": end - start
        })

with open("data/benchmarks/benchmark.csv", "w", newline="") as f:
    writer = csv.DictWriter(
        f,
        fieldnames=["algorithm", "size", "time"]
    )

    writer.writeheader()

    for row in results:
        writer.writerow(row)