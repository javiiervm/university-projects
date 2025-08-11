#include <iostream>      // Para entrada/salida estándar (cin, cout, cerr)
#include <fstream>       // Para manejo de archivos
#include <vector>        // Para vectores dinámicos
#include <string>        // Para cadenas de caracteres
#include <cstring>       // Para funciones de comparación tipo C (strcmp)
#include <chrono>        // Para medir el tiempo de ejecución
#include <climits>       // Para valores como INT_MAX
#include <iomanip>       // Para formatear la salida (tiempo con 3 decimales)
#include <queue>         // Para la cola de prioridad
#include <utility>       // Para pares (pair)
#include <algorithm>

using namespace std;

// Constante con el formato correcto que debe tener la línea de comandos
const string FORMATO_ENTRADA = " [-p] [--p2D] -f file";

// Vectores con los desplazamientos posibles (8 direcciones)
constexpr int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; // Norte, NE, Este, SE, Sur, SW, Oeste, NO
constexpr int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// Estructura para representar un nodo en la lista de nodos vivos
struct Nodo {
    int x, y;                   // Posición actual en el laberinto
    int g;                      // Coste real acumulado desde el inicio (profundidad)
    int h;                      // Heurística (cota optimista estimada)
    vector<pair<int, int>> camino; // Camino recorrido hasta aquí

    // Operador < invertido para que la priority_queue funcione como min-heap
    bool operator<(const Nodo& otro) const {
        return g + h > otro.g + otro.h;
    }
};

// =======================================
// compute_reachable: Marca con true todas las casillas desde las que
// se puede llegar al destino (n-1, m-1). Se usa para poda de no factibilidad.
// =======================================
void compute_reachable(const vector<vector<int>> &laberinto, vector<vector<bool>> &reachable) {
    int n = laberinto.size();
    int m = laberinto[0].size();
    queue<pair<int,int>> q;

    // Inicializamos todo a false
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            reachable[i][j] = false;

    // Si la meta está abierta, iniciamos desde ella
    if (laberinto[n-1][m-1] == 1) {
        reachable[n-1][m-1] = true;
        q.push({n-1, m-1});
    }

    // BFS inverso para marcar las casillas desde las que se puede llegar a la meta
    while(!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for(int dir = 0; dir < 8; ++dir) {
            int px = x - dx[dir], py = y - dy[dir];
            if (px >= 0 && px < n && py >= 0 && py < m && laberinto[px][py] == 1 && !reachable[px][py]) {
                reachable[px][py] = true;
                q.push({px, py});
            }
        }
    }
}

// ============================= VALIDACIÓN DE PARÁMETROS =============================

// Procesa los argumentos de la línea de comandos
bool validar_parametros(int argc, char *argv[], bool &flagP2D, bool &flagP, string &filename) {
    bool flagName = false;
    if(argc == 1) return false;

    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-f") == 0) {
            if(i == argc - 1) {
                cerr << "ERROR: Missing filename." << endl;
                return false;
            }
            filename = argv[++i];
            flagName = true;
        } else if(strcmp(argv[i], "--p2D") == 0) {
            flagP2D = true;
        } else if(strcmp(argv[i], "-p") == 0) {
            flagP = true;
        } else {
            cerr << "ERROR: Unknown option " << argv[i] << "." << endl;
            return false;
        }
    }

    return flagName;
}

// Imprime el formato correcto y termina el programa
void exit_failure(char *argv[]) {
    cerr << "Usage:\n" << argv[0] << FORMATO_ENTRADA << endl;
    exit(EXIT_FAILURE);
}

// ============================= FUNCIONES AUXILIARES =============================

// Devuelve la longitud del camino
int longitudCamino(const vector<pair<int, int>> &camino) {
    return camino.size();
}

// Imprime el laberinto marcando el camino con '*'
void mostrar_p2D(const vector<vector<int>> &laberinto, const vector<pair<int, int>> &camino) {
    vector<vector<char>> output(laberinto.size(), vector<char>(laberinto[0].size()));

    // Copia del laberinto original
    for (int i = 0; i < laberinto.size(); ++i)
        for (int j = 0; j < laberinto[0].size(); ++j)
            output[i][j] = laberinto[i][j] + '0';

    // Marcar el camino
    for (auto &p : camino)
        output[p.first][p.second] = '*';

    // Imprimir
    for (int i = 0; i < output.size(); ++i) {
        for (int j = 0; j < output[0].size(); ++j)
            cout << output[i][j];
        cout << endl;
    }
}

// Imprime el camino como secuencia de direcciones entre <>
void mostrar_p(const vector<pair<int, int>> &camino) {
    if(camino.size() <= 1) {
        cout << "<>" << endl;
        return;
    }

    cout << "<";
    for(int i = 1; i < camino.size(); ++i) {
        int dx_move = camino[i].first - camino[i-1].first;
        int dy_move = camino[i].second - camino[i-1].second;
        for(int dir = 0; dir < 8; ++dir) {
            if(dx[dir] == dx_move && dy[dir] == dy_move) {
                cout << dir+1;
                break;
            }
        }
    }
    cout << ">" << endl;
}

// ============================= ALGORITMO DE RAMIFICACIÓN Y PODA =============================

// maze_bb: Implementa ramificación y poda usando A* con cola de prioridad
bool maze_bb(const vector<vector<int>> &laberinto, const vector<vector<bool>> &reachable,
            vector<pair<int, int>> &camino_final, int &nvisit, int &nexplored, int &nleaf,
            int &nunfeasible, int &nnotpromising, int &npromising_but_discarded,
            int &nbest_from_leaf, int &nbest_from_bound) {

    int n = laberinto.size(), m = laberinto[0].size();

    // Si la entrada o la salida están cerradas, no hay solución
    if (laberinto[0][0] == 0 || laberinto[n-1][m-1] == 0) {
        nvisit = 1;
        return false;
    }

    // Matriz para no volver a expandir el mismo nodo
    vector<vector<bool>> visitado(n, vector<bool>(m, false));

    // Cola de prioridad con criterio g + h (A*)
    priority_queue<Nodo> cola;

    // Nodo inicial
    Nodo inicio = {0, 0, 1, abs(n-1) + abs(m-1), {{0, 0}}};
    cola.push(inicio);

    // Cota pesimista: inicialmente no hay solución conocida
    int mejor_longitud = INT_MAX;

    // Bucle principal: mientras haya nodos vivos
    while (!cola.empty()) {
        Nodo actual = cola.top(); cola.pop();
        nvisit++;

        int x = actual.x, y = actual.y;

        // Poda: ya se visitó antes
        if (visitado[x][y]) {
            npromising_but_discarded++;
            continue;
        } else {
            visitado[x][y] = true;
        }

        // Caso base: nodo hoja (es destino)
        if (x == n-1 && y == m-1) {
            nexplored++;
            nleaf++;
            if (actual.g < mejor_longitud) {
                mejor_longitud = actual.g;
                camino_final = actual.camino;
                nbest_from_leaf++;
            }
            continue;
        }

        // Poda por no prometedor
        if (actual.g + actual.h >= mejor_longitud) {
            nnotpromising++;
            continue;
        }

        // El nodo se va a expandir
        nexplored++;

        // Estructura auxiliar para ordenar sucesores
        struct Sucesor {
            int nx, ny, dir, h;
        };

        // Recolectar sucesores válidos
        vector<Sucesor> sucesores;

        for (int dir = 0; dir < 8; ++dir) {
            int nx = x + dx[dir], ny = y + dy[dir];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m || laberinto[nx][ny] == 0 || !reachable[nx][ny]) {
                nunfeasible++;
                continue;
            }

            int heuristica = abs(n - 1 - nx) + abs(m - 1 - ny);
            sucesores.push_back({nx, ny, dir, heuristica});
        }

        // Ordenar los sucesores por heurística creciente (más prometedores primero)
        sort(sucesores.begin(), sucesores.end(), [](const Sucesor &a, const Sucesor &b) {
            if (a.h != b.h) return a.h < b.h;
            return a.dir < b.dir; // en caso de empate, ordena por dirección (para que sea determinista)
        });

        // Insertar en la cola
        for (const auto& s : sucesores) {
            vector<pair<int, int>> nuevo_camino = actual.camino;
            nuevo_camino.emplace_back(s.nx, s.ny);
            int nuevo_coste = actual.g + 1;
            cola.push({s.nx, s.ny, nuevo_coste, s.h, nuevo_camino});
        }

    }

    return !camino_final.empty();
}

// ============================= FUNCIÓN MAIN =============================

int main(int argc, char *argv[]) {
    bool flagP2D = false, flagP = false;
    string filename;

    // Validación de parámetros
    if (!validar_parametros(argc, argv, flagP2D, flagP, filename))
        exit_failure(argv);

    // Abrir archivo
    ifstream is(filename);
    if (!is) {
        cerr << "ERROR: Can't open file: " << filename << "." << endl;
        exit_failure(argv);
    }

    // Leer laberinto
    int rows, cols;
    is >> rows >> cols;
    vector<vector<int>> laberinto(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            is >> laberinto[i][j];
    is.close();

    // Calcular casillas desde las que se puede llegar a la meta
    vector<vector<bool>> reachable(rows, vector<bool>(cols, false));
    compute_reachable(laberinto, reachable);

    // Variables de salida
    vector<pair<int, int>> camino_final;
    int nvisit = 0, nexplored = 0, nleaf = 0, nunfeasible = 0;
    int nnotpromising = 0, npromising_but_discarded = 0;
    int nbest_from_leaf = 0, nbest_from_bound = 0;

    // Medir tiempo de ejecución
    auto inicio = chrono::high_resolution_clock::now();
    bool solucion = maze_bb(laberinto, reachable, camino_final, nvisit, nexplored, nleaf,
                            nunfeasible, nnotpromising, npromising_but_discarded,
                            nbest_from_leaf, nbest_from_bound);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempo = fin - inicio;

    // Imprimir longitud del camino (o 0 si no hay solución)
    if (!solucion)
        cout << 0 << endl;
    else
        cout << longitudCamino(camino_final) << endl;

    // Imprimir estadísticas (8 contadores)
    cout << nvisit << " " << nexplored << " " << nleaf << " " << nunfeasible << " "
        << nnotpromising << " " << npromising_but_discarded << " "
        << nbest_from_leaf << " " << nbest_from_bound << endl;

    // Imprimir tiempo de CPU
    cout << fixed << setprecision(3) << tiempo.count() << endl;

    // Imprimir camino en formato visual o direccional si se ha solicitado
    if (!solucion) {
        if (flagP2D) cout << "0" << endl;
        if (flagP) cout << "<0>" << endl;
    } else {
        if (flagP2D) mostrar_p2D(laberinto, camino_final);
        if (flagP) mostrar_p(camino_final);
    }

    return 0;
}
