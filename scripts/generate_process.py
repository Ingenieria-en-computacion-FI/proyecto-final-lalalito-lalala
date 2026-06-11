import random
import sys
from pathlib import Path

n = int(sys.argv[1])  # Recibe cantidad de procesos desde línea de comandos

OUT = Path(f"data/inputs/processes_{n}.csv")  # Ruta del archivo de salida

with open(OUT, "w") as f:
    for i in range(n):
        # Escribe: ID, tiempo de ejecución, prioridad, memoria requerida
        f.write(
            f"{i},{random.randint(1,20)},{random.randint(1,5)},{random.randint(10,500)}\n"
        )

print(f"✔ Generados {n} procesos")
