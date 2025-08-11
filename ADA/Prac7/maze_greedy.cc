#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <limits.h>     // Para INT_MAX (valor "infinito")
#include <algorithm>    // Para std::min

using namespace std;

const string FORMATO_ENTRADA = " [--p2D] -f file";


// ============================= COMPROBACIÓN DE PARÁMETROS Y MENSAJES DE ERROR =============================

/* 
Recorre los argumentos de la línea de comandos para identificar:
    - El nombre del fichero (tras la opción "-f").
    - Las opciones: -t, --p2D y --ignore-naive.
Devuelve true si se encuentra la opción "-f" (nombre del fichero), false en caso contrario, y activa las flags pasadas por referencia
*/
bool validar_parametros(int argc, char *argv[], bool &flagP2D, string &filename) {
    bool flagName = false;  // Indica si se ha encontrado el nombre del fichero.
    if(argc == 1) return false; // Si no hay argumentos, devuelve false.
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-f") == 0) {
            if(i == argc - 1) { // Si "-f" es el último argumento, falta el nombre del fichero.
                cerr << "ERROR: Missing filename." << endl;
                return false;
            }
            i++;              // Incrementa para tomar el siguiente argumento, que es el nombre del fichero.
            filename = argv[i];
            flagName = true;  // Se encontró el nombre del fichero.
        } else if(strcmp(argv[i], "--p2D") == 0) {
            flagP2D = true;   // La opción --p2D está activada.
        } else {
            // Si se encuentra una opción desconocida, se muestra un mensaje de error.
            cerr << "ERROR: Unknown option " << argv[i] << "." << endl;
            return false;
        }
    }
    return flagName;
}

// Imprime el mensaje de uso correcto y termina el programa con una salida de error.
void exit_failure(char *argv[]) {
    cerr << "Usage:\n" << argv[0] << FORMATO_ENTRADA << endl;
    exit(EXIT_FAILURE);
}

// ============================= FUNCIONES AUXILIARES =============================
int longitudCamino(vector<vector<int>> mat) {
    int contador = 0;
    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[i].size(); j++) {
            if(mat[i][j] == 2) {
                contador++;
            }
        }
    }
    return contador;
}


// ============================= FUNCIÓN PARA BUSCAR EL CAMINO =============================

void maze_greedy(vector<vector<int>> &mat, int row, int col, int maxrows, int maxcols) {
    if(mat[row][col] == 0) {
        return;
    }
    mat[row][col] = 2;  // Usamos el valor 2 para simbolizar que hemos elegido esa casilla
    if(row+1 < maxrows && col+1 < maxcols && mat[row+1][col+1] == 1) {
        maze_greedy(mat, row+1, col+1, maxrows, maxcols);
    } else {
        if(row+1 < maxrows && mat[row+1][col] == 1) {
            maze_greedy(mat, row+1, col, maxrows, maxcols);
        } else {
            if(col+1 < maxcols && mat[row][col+1] == 1) {
                maze_greedy(mat, row, col+1, maxrows, maxcols);
            } else {
                return;
            }
        }
    }
}


// ============================= FUNCIÓN MAIN =============================

int main(int argc, char *argv[]) {
    bool flagP2D = false;
    string filename;
    // Validación de parámetros. Si falla, se muestra el uso correcto y se termina el programa.
    if(!validar_parametros(argc, argv, flagP2D, filename))
        exit_failure(argv);
    ifstream is(filename);
    if(!is) {
        cerr << "ERROR: Can't open file: " << filename << "." << endl;
        exit_failure(argv);
    }
    // Lectura de filas y columnas.
    int rows, cols;
    is >> rows >> cols;
    // Lectura de la matriz que representa el laberinto.
    vector<vector<int>> mat(rows, vector<int>(cols));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            is >> mat[i][j];
        }
    }
    is.close();

    maze_greedy(mat, 0, 0, mat.size(), mat[0].size());

    if(mat[rows-1][cols-1] == 2) {
        cout << longitudCamino(mat) << endl;
    } else {
        cout << 0 << endl;
    }

    if(flagP2D) {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if(mat[i][j] == 2) {
                    cout << "*";
                } else {
                    cout << mat[i][j];
                }
            }
            cout << endl;
        }
    }

    return 0;
}
