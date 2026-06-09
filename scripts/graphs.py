import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../data/benchmarks/benchmark.csv")

for alg in df["algorithm"].unique():

    subset = df[df["algorithm"] == alg]

    plt.plot(subset["size"], subset["time"], label=alg)

plt.xlabel("Procesos")
plt.ylabel("Tiempo (s)")
plt.title("Comparación de algoritmos de scheduling")
plt.legend()

plt.savefig("../data/outputs/graph.png")
plt.show()