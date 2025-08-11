import os

salida = ""
testdir = "maze-PD-testfiles/"
files = os.listdir(testdir)

for f in files:
    if not f.__contains__(".sol"):
        print(f,end="\t")
        salida = os.popen(f"timeout 2 ./maze -f {testdir}{f}").read().split("\n")[0]
        if salida == "":
            salida = os.popen(f" ./maze --ignore-naive -f {testdir}{f}").read().split("\n")[0]
        solucion = os.popen(f"cat {testdir}{f}.sol").read().split("\n")[0]
        if salida.strip() == solucion.strip():
            print("OK!")
        else:
            print("ERROR! ❌")