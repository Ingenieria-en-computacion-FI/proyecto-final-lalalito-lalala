import csv
import matplotlib.pyplot as plt

data = {
    "fifo": ([], []),
    "sjf": ([], []),
    "rr": ([], [])
}

with open("data/benchmarks/benchmark.csv") as f:

    reader = csv.DictReader(f)

    for row in reader:

        alg = row["algorithm"]

        data[alg][0].append(int(row["size"]))
        data[alg][1].append(float(row["time"]))

for alg in data:

    plt.plot(
        data[alg][0],
        data[alg][1],
        marker="o",
        label=alg.upper()
    )

plt.xlabel("Número de procesos")
plt.ylabel("Tiempo (s)")
plt.title("Comparación FIFO vs SJF vs RR")
plt.legend()

plt.savefig("data/benchmarks/graph.png")
plt.show()