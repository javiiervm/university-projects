import os

testdir = "maze-BT-testfiles/"
files = sorted([f for f in os.listdir(testdir) if f.endswith(".maze")], key=lambda x: int(x.split('-')[0]))

for f in files:
    print("")
    if f.startswith("10"):
        break
    sol_file = f"{f}.sol_bt"
    if sol_file in os.listdir(testdir):
        if os.system(f"timeout 5 ./maze_bt -p --p2D -f {testdir}{f} > salida.txt"):
            print(f"{f}: ERROR! Tiempo de ejecución excedido (5 segundos).")
            continue
        if open(f"{testdir}{sol_file}").read() == open("salida.txt").read():
            print(f"{f}: OK")
        else:
            print(f"{f}:")
            os.system(f"diff {testdir}{sol_file} salida.txt")
