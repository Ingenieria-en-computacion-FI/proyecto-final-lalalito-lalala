import pandas as pd

df = pd.read_csv("../data/benchmarks/benchmark.csv")

print("=== VALIDACIÓN ===")

print(df.groupby("algorithm")["time"].mean())

print("\n✔ OK si no hay valores negativos o NaN")