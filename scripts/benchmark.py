import subprocess
import time
import pandas as pd
from pathlib import Path

BIN = Path("../bin/main.exe")
OUT = Path("../data/benchmarks/benchmark.csv")

algorithms = ["fifo", "sjf", "rr"]
sizes = [100, 500, 1000, 5000]

results = []

for alg in algorithms:
    for size in sizes:

        start = time.perf_counter()

        subprocess.run(
            [str(BIN), alg, str(size)],
            check=True
        )

        end = time.perf_counter()

        results.append({
            "algorithm": alg,
            "size": size,
            "time": end - start
        })

OUT.parent.mkdir(parents=True, exist_ok=True)

pd.DataFrame(results).to_csv(OUT, index=False)

print("✔ Benchmark guardado en data/benchmarks/")