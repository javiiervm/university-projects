import subprocess
import os

# Ruta de los tests
RUTA_TESTS = "maze-BB-testfiles"
EJECUTABLE = "./maze_bb"

# Recorre todos los ficheros .maze que NO terminan en .sol_bb
def es_maze_valido(nombre):
    return nombre.endswith(".maze") and not nombre.endswith(".sol_bb")

# Comparador
def comparar(fichero_maze):
    nombre_base = fichero_maze[:-5]  # quita '.maze'
    fichero_sol = fichero_maze + ".sol_bb"

    path_maze = os.path.join(RUTA_TESTS, fichero_maze)
    path_sol = os.path.join(RUTA_TESTS, fichero_sol)

    # Ejecutar el programa
    try:
        resultado = subprocess.run(
            [EJECUTABLE, "-p", "--p2D", "-f", path_maze],
            capture_output=True,
            text=True,
            timeout=10
        )
    except Exception as e:
        print(f"{fichero_maze}: ERROR al ejecutar → {e}")
        return

    if resultado.returncode != 0:
        print(f"{fichero_maze}: ERROR en la ejecución (código {resultado.returncode})")
        return

    salida_mi_programa = resultado.stdout.strip().splitlines()

    # Leer la salida esperada
    try:
        with open(path_sol, 'r') as f:
            salida_esperada = f.read().strip().splitlines()
    except FileNotFoundError:
        print(f"{fichero_maze}: ERROR no se encontró {fichero_sol}")
        return

    # Comparar primera y última línea
    if not salida_mi_programa or not salida_esperada:
        print(f"{fichero_maze}: ERROR salida vacía o mal formateada")
        return

    longitud_ok = salida_mi_programa[0] == salida_esperada[0]
    camino_ok = salida_mi_programa[-1] == salida_esperada[-1]

    if longitud_ok and camino_ok:
        print(f"{fichero_maze}: OK")
    else:
        print(f"{fichero_maze}: ERROR")
        if not longitud_ok:
            pass
            #print(f"  Longitud esperada: {salida_esperada[0]} / obtenida: {salida_mi_programa[0]}")
        if not camino_ok:
            pass
            #print(f"  Camino esperado:   {salida_esperada[-1]} / obtenido: {salida_mi_programa[-1]}")

# Recorrer la carpeta
for nombre in sorted(os.listdir(RUTA_TESTS)):
    if es_maze_valido(nombre):
        comparar(nombre)
