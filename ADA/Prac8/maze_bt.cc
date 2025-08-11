#include <iostream>      // Para entrada y salida estándar (cin, cout, cerr)
#include <fstream>       // Para manejo de archivos (ifstream)
#include <vector>        // Para uso de vectores
#include <string>        // Para uso de strings
#include <cstring>       // Para comparar cadenas tipo C (strcmp)
#include <chrono>        // Para medir el tiempo de ejecución
#include <climits>       // Para obtener el valor INT_MAX
#include <iomanip>
#include <queue>
#include <utility>

using namespace std;

// Constante con el formato que debe seguir la línea de comandos
const string FORMATO_ENTRADA = " [-p] [--p2D] -f file";

// Vectores que representan los desplazamientos en las 8 direcciones posibles (N, NE, E, SE, S, SW, W, NW)
constexpr int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; // Desplazamientos en X
constexpr int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1}; // Desplazamientos en Y

// =======================================
// compute_reachable: marca con true todas las casillas
// desde las que existe un camino a (n-1, m-1)
// =======================================
void compute_reachable(
    const vector<vector<int>> &laberinto,
    vector<vector<bool>>         &reachable
) {
    int n = laberinto.size();
    int m = laberinto[0].size();
    queue<pair<int,int>> q;

    // Inicializamos todo a false
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            reachable[i][j] = false;

    // Si la meta está abierta, arrancamos desde ella
    if (laberinto[n-1][m-1] == 1) {
        reachable[n-1][m-1] = true;
        q.push({n-1, m-1});
    }

    // BFS invertido
    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for(int dir = 0; dir < 8; ++dir) {
            int px = x - dx[dir], py = y - dy[dir];
            if (px >= 0 && px < n && py >= 0 && py < m
                && laberinto[px][py] == 1
                && !reachable[px][py]) {
                reachable[px][py] = true;
                q.push({px, py});
            }
        }
    }
}

// ============================= COMPROBACIÓN DE PARÁMETROS Y MENSAJES DE ERROR =============================

// Función que valida los parámetros pasados por línea de comandos
bool validar_parametros(int argc, char *argv[], bool &flagP2D, bool &flagP, string &filename) {
    bool flagName = false; // Indica si se ha proporcionado el nombre del archivo
    if(argc == 1) return false; // Si no hay argumentos, retorna false
    for (int i = 1; i < argc; i++) {
        // Si el argumento actual es "-f", se espera que el siguiente sea el nombre del archivo
        if(strcmp(argv[i], "-f") == 0) {
            if(i == argc - 1) {
                cerr << "ERROR: Missing filename." << endl;
                return false;
            }
            filename = argv[++i]; // Guarda el nombre del archivo
            flagName = true;
        } else if(strcmp(argv[i], "--p2D") == 0) {
            flagP2D = true; // Activa la impresión visual del camino
        } else if(strcmp(argv[i], "-p") == 0) {
            flagP = true; // Activa la impresión de movimientos
        } else {
            // Si se encuentra una opción desconocida, muestra error
            cerr << "ERROR: Unknown option " << argv[i] << "." << endl;
            return false;
        }
    }
    return flagName; // Retorna true solo si se proporcionó el nombre del archivo
}

// Función que muestra el formato correcto de uso del programa y termina la ejecución con error
void exit_failure(char *argv[]) {
    cerr << "Usage:\n" << argv[0] << FORMATO_ENTRADA << endl;
    exit(EXIT_FAILURE);
}

// ============================= FUNCIONES AUXILIARES =============================

// Función que devuelve la longitud del camino (número de posiciones visitadas)
int longitudCamino(const vector<pair<int, int>> &camino) {
    return camino.size();
}

// Función que imprime el laberinto en formato 2D con el camino marcado con '*'
void mostrar_p2D(const vector<vector<int>> &laberinto, const vector<pair<int, int>> &camino) {
    // Inicializa una matriz de caracteres del mismo tamaño que el laberinto
    vector<vector<char>> output(laberinto.size(), vector<char>(laberinto[0].size()));

    // Convierte los valores del laberinto (0 y 1) a caracteres ('0' y '1')
    for (int i = 0; i < laberinto.size(); ++i)
        for (int j = 0; j < laberinto[0].size(); ++j)
            output[i][j] = laberinto[i][j] + '0';

    // Recorre el camino y marca las posiciones con '*'
    for (auto &p : camino)
        output[p.first][p.second] = '*';

    // Imprime la matriz resultante por pantalla
    for (int i = 0; i < output.size(); ++i) {
        for (int j = 0; j < output[0].size(); ++j)
            cout << output[i][j];
        cout << endl;
    }
}

// Función que imprime el camino en forma de direcciones (1-8) encerradas entre signos <>
void mostrar_p(const vector<pair<int, int>> &camino) {
    if(camino.size() <= 1) {
        cout << "<>" << endl; // Camino vacío o con un solo nodo
        return;
    }

    cout << "<";
    for(int i = 1; i < camino.size(); ++i) {
        // Calcula el movimiento entre dos posiciones consecutivas
        int dx_move = camino[i].first - camino[i-1].first;
        int dy_move = camino[i].second - camino[i-1].second;
        for(int dir = 0; dir < 8; ++dir) {
            // Encuentra la dirección correspondiente al movimiento y la imprime
            if(dx[dir] == dx_move && dy[dir] == dy_move) {
                cout << dir+1; // Direcciones del 1 al 8
                break;
            }
        }
    }
    cout << ">" << endl;
}

// ============================= FUNCIÓN PRINCIPAL: maze_bt =============================

// Función recursiva que explora todos los caminos posibles mediante backtracking
int backtrack(
    const vector<vector<int>> &laberinto, 
    const vector<vector<bool>> &reachable,
    int n, int m,                        // Dimensiones del laberinto
    int &visitados, int &explorados,     // Contadores de nodos visitados y explorados
    int &hojas,                          // Número de soluciones encontradas
    int &descartados_no_factibles,       // Caminos que no llevan a una solución por ser inválidos
    int &descartados_no_prometedores,    // Caminos válidos pero peores que el mejor actual
    int &mejor_longitud,                 // Longitud del mejor camino encontrado hasta ahora
    vector<pair<int, int>> &camino_final,// Mejor camino encontrado
    vector<pair<int, int>> &camino_actual,// Camino que se está construyendo actualmente
    vector<vector<bool>> &visitado,     // Matriz de nodos visitados
    int x, int y,                         // Posición actual
    vector<vector<int>> &pasos_minimos,
    vector<vector<int>> &memo
) {
    if (memo[x][y] != INT_MAX) {
        return memo[x][y];
    }
    
    visitados++;
    visitado[x][y] = true;
    camino_actual.push_back({x, y});

    // Poda: si ya llegamos aquí en menos pasos antes, descartamos
    if (camino_actual.size() >= pasos_minimos[x][y]) {
        descartados_no_prometedores++;
        camino_actual.pop_back();
        visitado[x][y] = false;
        return camino_actual.size();
    }

    // Actualiza el mínimo de pasos para llegar a (x,y)
    pasos_minimos[x][y] = camino_actual.size();

    // Caso base: se llega al destino
    if (x == n - 1 && y == m - 1) {
        if (camino_actual.size() < mejor_longitud) {
            mejor_longitud = camino_actual.size();
            camino_final = camino_actual;
            hojas++;
        }
    } else {
        explorados++;

        struct Opcion { int h, dir; };
        Opcion opciones[8];
        int numOpc = 0;

        // Recolectar vecinos válidos
        for (int dir = 0; dir < 8; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            if (!reachable[nx][ny] || laberinto[nx][ny] == 0 || visitado[nx][ny]) {
                descartados_no_factibles++;
                continue;
            }

            //int h = max(abs((n - 1) - nx), abs((m - 1) - ny)); // Chebyshev
            int h = abs((n-1) - nx) + abs((m-1) - ny); // Manhattan
            opciones[numOpc++] = {h, dir};
        }

        // Ordenar por heurística creciente
        for (int i = 1; i < numOpc; ++i) {
            Opcion key = opciones[i];
            int j = i - 1;
            while (j >= 0 && opciones[j].h > key.h) {
                opciones[j + 1] = opciones[j];
                --j;
            }
            opciones[j + 1] = key;
        }

        // Explorar vecinos ordenados
        for (int i = 0; i < numOpc; ++i) {
            int dir = opciones[i].dir;
            int nx = x + dx[dir], ny = y + dy[dir];

            if (camino_actual.size() + 1 >= mejor_longitud) {
                descartados_no_prometedores++;
                continue;
            }

            backtrack(laberinto, reachable, n, m,
                    visitados, explorados, hojas,
                    descartados_no_factibles, descartados_no_prometedores,
                    mejor_longitud, camino_final, camino_actual,
                    visitado, nx, ny, pasos_minimos, memo);
        }
    }

    // Deshacer cambios (backtracking)
    camino_actual.pop_back();
    visitado[x][y] = false;

    memo[x][y] = camino_actual.size();
    return memo[x][y];
}

// Función que inicializa las estructuras necesarias y llama a la función backtrack
bool maze_bt(
    const vector<vector<int>> &laberinto, 
    const vector<vector<bool>> &reachable,
    vector<pair<int, int>> &camino_final, 
    int &visitados, int &explorados, int &hojas, 
    int &descartados_no_factibles, int &descartados_no_prometedores) {

    int n = laberinto.size();
    int m = laberinto[0].size();
    vector<vector<int>> pasos_minimos(n, vector<int>(m, INT_MAX));
    vector<vector<int>> memo(n, vector<int>(m, INT_MAX));

    // Si casilla inicial o final está cerrada, no hay solución
    if (laberinto[0][0] == 0 || laberinto[n - 1][m - 1] == 0)
        return false;

    int mejor_longitud = INT_MAX; // Se inicializa con el peor caso posible
    vector<pair<int, int>> camino_actual; // Vector para construir caminos
    vector<vector<bool>> visitado(n, vector<bool>(m, false)); // Matriz de visitados

    // Llamada inicial al backtracking desde la posición (0,0)
    backtrack(laberinto, reachable, n, m, visitados, explorados, hojas, descartados_no_factibles, descartados_no_prometedores, mejor_longitud, camino_final, camino_actual, visitado, 0, 0, pasos_minimos, memo);
    return true;
}

// ============================= FUNCIÓN MAIN =============================

int main(int argc, char *argv[]) {
    bool flagP2D = false; // Mostrar laberinto visual
    bool flagP = false;   // Mostrar camino como secuencia de direcciones
    string filename;      // Nombre del archivo de entrada

    // Validar parámetros de entrada
    if(!validar_parametros(argc, argv, flagP2D, flagP, filename))
        exit_failure(argv);

    // Abrir archivo de entrada
    ifstream is(filename);
    if(!is) {
        cerr << "ERROR: Can't open file: " << filename << "." << endl;
        exit_failure(argv);
    }

    // Leer dimensiones del laberinto
    int rows, cols;
    is >> rows >> cols;
    vector<vector<int>> laberinto(rows, vector<int>(cols));
    
    // Leer contenido del laberinto (0s y 1s)
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            is >> laberinto[i][j];

    is.close(); // Cerrar archivo

    vector<vector<bool>> reachable(rows, vector<bool>(cols, false));
    compute_reachable(laberinto, reachable);

    vector<pair<int, int>> camino_final; // Camino óptimo resultante
    int visitados = 0, explorados = 0, hojas = 0, descartados_no_factibles = 0, descartados_no_prometedores = 0;

    // Medir el tiempo de ejecución del algoritmo
    auto inicio = chrono::high_resolution_clock::now();
    bool solucion_encontrada = maze_bt(laberinto, reachable, camino_final, visitados, explorados, hojas, descartados_no_factibles, descartados_no_prometedores);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo = fin - inicio;

    // Imprimir longitud del camino
    if (!solucion_encontrada || camino_final.empty())
        cout << 0 << endl;
    else
        cout << longitudCamino(camino_final) << endl;

    // Imprimir estadísticas
    cout << visitados << " " << explorados << " " << hojas << " " << descartados_no_factibles << " " << descartados_no_prometedores << endl;

    // Imprimir tiempo de ejecución en milisegundos
    cout << fixed << setprecision(3) << tiempo.count() << endl;

    // Imprimir representación visual o direccional del camino si se solicitó
    if (!solucion_encontrada || camino_final.empty()) {
        if (flagP2D) cout << "0" << endl;
        if (flagP) cout << "<0>" << endl;
    } else {
        if (flagP2D) mostrar_p2D(laberinto, camino_final);
        if (flagP) mostrar_p(camino_final);
    }

    return 0;
}
