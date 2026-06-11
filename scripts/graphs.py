import csv
import matplotlib.pyplot as plt

# Almacena tamaños y tiempos por algoritmo
data = {
    "fifo": ([], []),
    "sjf": ([], []),
    "rr": ([], [])
}

# Lee resultados del archivo CSV
with open("data/benchmarks/benchmark.csv") as f:
    reader = csv.DictReader(f)
    for row in reader:
        alg = row["algorithm"]
        data[alg][0].append(int(row["size"]))   # Guarda cantidad de procesos
        data[alg][1].append(float(row["time"])) # Guarda tiempo de ejecución

# Dibuja la curva de cada algoritmo
for alg in data:
    plt.plot(
        data[alg][0],
        data[alg][1],
        marker="o",
        label=alg.upper()
    )

# Configuración del gráfico
plt.xlabel("Número de procesos")
plt.ylabel("Tiempo (s)")
plt.title("Comparación FIFO vs SJF vs RR")
plt.legend()

# Guarda y muestra el gráfico
plt.savefig("data/benchmarks/graph.png")
plt.show()
