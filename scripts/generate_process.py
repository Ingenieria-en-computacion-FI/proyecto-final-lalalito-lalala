import random
import sys
from pathlib import Path

n = int(sys.argv[1])

OUT = Path(f"data/inputs/processes_{n}.csv")

with open(OUT, "w") as f:
    for i in range(n):
        f.write(
            f"{i},{random.randint(1,20)},{random.randint(1,5)},{random.randint(10,500)}\n"
        )

print(f"✔ Generados {n} procesos")