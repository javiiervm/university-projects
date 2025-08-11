import os

salida = ""
testdir = "maze-Greedy-testfiles/"
files = os.listdir(testdir)

for f in files:
    if not f.__contains__(".sol"):
        print(f,end="\t")
        salida = os.popen(f"timeout 2 ./maze_greedy -f {testdir}{f}").read().split("\n")[0]
        if salida == "":
            salida = os.popen(f" ./maze_greedy -f {testdir}{f}").read().split("\n")[0]
        solucion = os.popen(f"cat {testdir}{f}.sol_greedy").read().split("\n")[0]
        if salida.strip() == solucion.strip():
            print("OK!")
        else:
            print("ERROR! ❌")