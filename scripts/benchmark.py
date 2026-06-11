import subprocess
import time
import csv

# Tamaños de prueba (cantidad de procesos)
sizes = [100, 500, 1000, 2500, 4000, 5000]
# Algoritmos a evaluar
algorithms = ["fifo", "sjf", "rr"]

results = []  # Almacena los tiempos obtenidos

for size in sizes:
    # Genera archivo con procesos del tamaño actual
    subprocess.run(
        ["python", "scripts/generate_process.py", str(size)],
        check=True
    )
    file = f"data/inputs/processes_{size}.csv"

    for alg in algorithms:
        start = time.perf_counter()  # Inicia medición de tiempo
        
        # Ejecuta el planificador y descarta su salida
        subprocess.run(
            ["./bin/main.exe", alg, file],
            stdout=subprocess.DEVNULL
        )
        
        end = time.perf_counter()  # Finaliza medición
        results.append({
            "algorithm": alg,
            "size": size,
            "time": end - start
        })

# Guarda todos los resultados en un archivo CSV
with open("data/benchmarks/benchmark.csv", "w", newline="") as f:
    writer = csv.DictWriter(f, fieldnames=["algorithm", "size", "time"])
    writer.writeheader()
    for row in results:
        writer.writerow(row)
        
