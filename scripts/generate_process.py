import random
from pathlib import Path

print("SCRIPT CORRIENDO")

BASE = Path.cwd()
OUT = BASE / "data" / "inputs" / "processes.csv"

print(" Guardando en:", OUT)

OUT.parent.mkdir(parents=True, exist_ok=True)

data = "\n".join(
    f"{i},{random.randint(1,20)},{random.randint(1,5)},{random.randint(10,500)}"
    for i in range(100)
)

OUT.write_text(data)

print("✔ CSV generado")