import pandas as pd

# Carga el archivo con los resultados
df = pd.read_csv("../data/benchmarks/benchmark.csv")

print("=== VALIDACIÓN ===")

# Muestra el tiempo promedio por algoritmo
print(df.groupby("algorithm")["time"].mean())

print("\n✔ OK si no hay valores negativos o NaN")
