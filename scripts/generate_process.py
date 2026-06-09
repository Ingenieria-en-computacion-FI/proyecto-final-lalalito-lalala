import random
import json
from pathlib import Path

OUT = Path("../data/inputs/processes.json")

processes = []

for i in range(100):

    processes.append({
        "pid": i,
        "burst": random.randint(1, 20),
        "memory": random.randint(10, 500)
    })

OUT.parent.mkdir(parents=True, exist_ok=True)

with open(OUT, "w") as f:
    json.dump(processes, f, indent=4)

print("✔ Procesos generados")