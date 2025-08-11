#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <limits.h>     // Para INT_MAX (valor "infinito")
#include <algorithm>    // Para std::min

using namespace std;

const string FORMATO_ENTRADA = " [--p2D] [-t] [--ignore-naive] -f file";


// ============================= COMPROBACIÓN DE PARÁMETROS Y MENSAJES DE ERROR =============================

/* 
Recorre los argumentos de la línea de comandos para identificar:
    - El nombre del fichero (tras la opción "-f").
    - Las opciones: -t, --p2D y --ignore-naive.
Devuelve true si se encuentra la opción "-f" (nombre del fichero), false en caso contrario, y activa las flags pasadas por referencia
*/
bool validar_parametros(int argc, char *argv[], bool &flagT, bool &flagP2D, bool &flagIgnoreNaive, string &filename) {
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
        } else if(strcmp(argv[i], "-t") == 0) {
            flagT = true;     // La opción -t está activada.
        } else if(strcmp(argv[i], "--p2D") == 0) {
            flagP2D = true;   // La opción --p2D está activada.
        } else if(strcmp(argv[i], "--ignore-naive") == 0) {
            flagIgnoreNaive = true;
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


// ============================= ANOTACIONES PARA RESOLVER EL LABERINTO =============================

/* 
---------------------- RECURRENCIA PARA RESOLVER EL LABERINTO ----------------------
    maze(n, m) =
        ∞  si L[n][m] == 0   (la celda es inaccesible)
        ∞  si n < 0 o m < 0   (índice fuera de rango)
        1  si n == 0 y m == 0 (casilla de origen, camino de longitud 1)
        min(maze(n-1, m-1), maze(n-1, m), maze(n, m-1)) + 1, en otro caso
*/


// ============================= SOLUCIÓN RECURSIVA SIN ALMACÉN =============================

// Versión recursiva naive del algoritmo, sin memoización.
int maze_naive(const vector<vector<int>> &mat, int row, int col) {
    // Si el índice está fuera de rango o la celda es inaccesible (valor 0), devuelve "infinito"
    if(row < 0 || col < 0 || mat[row][col] == 0)
        return INT_MAX;

    // Caso base: si se alcanza el origen (0,0), devuelve 1 (camino de longitud 1)
    if(row == 0 && col == 0)
        return 1;

    // Llamadas recursivas: se calcula la longitud del camino desde las tres direcciones permitidas.
    int diagonal = maze_naive(mat, row - 1, col - 1);  // Diagonal (arriba-izquierda)
    int arriba   = maze_naive(mat, row - 1, col);      // Arriba
    int izquierda = maze_naive(mat, row, col - 1);      // Izquierda

    // Se obtiene el mínimo de los tres caminos
    int min_camino = min(diagonal, min(arriba, izquierda));

    // Si no se encontró camino (min_camino es INT_MAX), se devuelve INT_MAX; de lo contrario se suma 1
    return (min_camino == INT_MAX ? INT_MAX : min_camino + 1);
}


// ============================= SOLUCIÓN RECURSIVA CON ALMACÉN =============================

/*
Función auxiliar recursiva con memoización.
Recibe la matriz del laberinto, la posición actual (row, col) y la tabla memo (inicialmente con -1).
Si ya se ha calculado el subproblema para (row, col), lo devuelve directamente desde memo.
En el caso base, para el origen (0,0), se asigna y devuelve 1.
Devuelve INT_MAX si la celda es inaccesible o está fuera de rango.
*/
int maze_memo_helper(const vector<vector<int>> &mat, int row, int col, vector<vector<int>> &memo) {
    if(row < 0 || col < 0 || mat[row][col] == 0)
        return INT_MAX;
    if(row == 0 && col == 0) {
        memo[row][col] = 1;  // Se guarda el resultado del origen en la tabla de memoización.
        return 1;
    }
    // Si ya se ha calculado el subproblema para (row, col), se devuelve el valor memorizado.
    if(memo[row][col] != -1)
        return memo[row][col];
    // Se calculan recursivamente las tres posibles rutas.
    int diagonal = maze_memo_helper(mat, row - 1, col - 1, memo);
    int arriba = maze_memo_helper(mat, row - 1, col, memo);
    int izquierda = maze_memo_helper(mat, row, col - 1, memo);
    // Se obtiene el mínimo de las tres rutas.
    int min_camino = min(diagonal, min(arriba, izquierda));
    // Se almacena en memo el resultado sumando 1 (o INT_MAX si no hay camino).
    memo[row][col] = (min_camino == INT_MAX ? INT_MAX : min_camino + 1);
    return memo[row][col];
}

/*
Inicializa la tabla de memoización con -1 y llama a la función auxiliar maze_memo_helper para la celda destino.
devuelve 0 si no existe camino (cuando el resultado es INT_MAX), o la longitud del camino mínimo.
*/
int maze_memo(const vector<vector<int>> &mat) {
    int rows = mat.size(), cols = mat[0].size();
    vector<vector<int>> memo(rows, vector<int>(cols, -1)); // Inicializa memo con -1 (no calculado)
    int result = maze_memo_helper(mat, rows - 1, cols - 1, memo);
    return (result == INT_MAX ? 0 : result);
}

/*
Función: compute_maze_memo
--------------------------
Similar a maze_memo, pero además devuelve la tabla de memoización calculada en el parámetro 'memo',
para poder imprimirla posteriormente.
*/
int compute_maze_memo(const vector<vector<int>> &mat, vector<vector<int>> &memo) {
    int rows = mat.size(), cols = mat[0].size();
    memo.assign(rows, vector<int>(cols, -1)); // Reinicializa la tabla de memoización.
    int result = maze_memo_helper(mat, rows - 1, cols - 1, memo);
    return result;
}


// ============================= SOLUCIÓN ITERATIVA CON ALMACÉN Y TABLA INTERMEDIA =============================

/*
Función: maze_it_matrix
-----------------------
Implementa una solución iterativa usando una tabla (matriz dp) para la programación dinámica.
Recorre la matriz de arriba hacia abajo y de izquierda a derecha, llenando dp según:
    - Si la celda es inaccesible (0), dp[i][j] se asigna INT_MAX.
    - En el origen (0,0), dp[0][0] se asigna 1.
    - En las demás celdas, dp[i][j] se calcula como min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]) + 1.
devuelve el valor en la celda destino (rows-1, cols-1).
*/
int maze_it_matrix(const vector<vector<int>> &mat) {
    int rows = mat.size(), cols = mat[0].size();
    vector<vector<int>> dp(rows, vector<int>(cols, INT_MAX)); // Inicializa dp con INT_MAX.
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(mat[i][j] == 0)
                dp[i][j] = INT_MAX; // Celda inaccesible
            else {
                if(i == 0 && j == 0)
                    dp[i][j] = 1; // Origen
                else {
                    // Obtiene el valor de las celdas de arriba, izquierda y diagonal (si existen).
                    int up   = (i > 0 ? dp[i - 1][j] : INT_MAX);
                    int left = (j > 0 ? dp[i][j - 1] : INT_MAX);
                    int diag = (i > 0 && j > 0 ? dp[i - 1][j - 1] : INT_MAX);
                    int best = min(diag, min(up, left)); // Selecciona el mínimo de los tres.
                    dp[i][j] = (best == INT_MAX ? INT_MAX : best + 1);
                }
            }
        }
    }
    return dp[rows - 1][cols - 1];
}

/*
  Función: compute_maze_it_matrix
  -------------------------------
  Similar a maze_it_matrix, pero almacena la tabla iterativa en 'dp' para poder imprimirla.
*/
int compute_maze_it_matrix(const vector<vector<int>> &mat, vector<vector<int>> &dp) {
    int rows = mat.size(), cols = mat[0].size();
    dp.assign(rows, vector<int>(cols, INT_MAX)); // Inicializa la tabla dp.
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(mat[i][j] == 0)
                dp[i][j] = INT_MAX;
            else {
                if(i == 0 && j == 0)
                    dp[i][j] = 1;
                else {
                    int up   = (i > 0 ? dp[i - 1][j] : INT_MAX);
                    int left = (j > 0 ? dp[i][j - 1] : INT_MAX);
                    int diag = (i > 0 && j > 0 ? dp[i - 1][j - 1] : INT_MAX);
                    int best = min(diag, min(up, left));
                    dp[i][j] = (best == INT_MAX ? INT_MAX : best + 1);
                }
            }
        }
    }
    return dp[rows - 1][cols - 1];
}


// ============================= SOLUCIÓN ITERATIVA CON ALMACÉN COMP. ESPACIAL MEJORADA =============================

/*
  Función: maze_it_vector
  ------------------------
  Versión iterativa que utiliza un vector para optimizar el uso de espacio.
  Se mantiene un vector "prev" para la fila anterior y "curr" para la fila actual.
  Cada celda de "curr" se calcula a partir de "prev" y de los valores previos en "curr".
  devuelve el valor de la última celda de la última fila.
*/
int maze_it_vector(const vector<vector<int>> &mat) {
    int rows = mat.size(), cols = mat[0].size();
    vector<int> prev(cols, INT_MAX), curr(cols, INT_MAX);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(mat[i][j] == 0)
                curr[j] = INT_MAX;
            else {
                if(i == 0 && j == 0)
                    curr[j] = 1;
                else {
                    int up   = (i > 0 ? prev[j] : INT_MAX);
                    int left = (j > 0 ? curr[j - 1] : INT_MAX);
                    int diag = (i > 0 && j > 0 ? prev[j - 1] : INT_MAX);
                    int best = min(diag, min(up, left));
                    curr[j] = (best == INT_MAX ? INT_MAX : best + 1);
                }
            }
        }
        prev = curr; // La fila actual pasa a ser la fila previa para la siguiente iteración.
    }
    return curr[cols - 1];
}

/*
  Función: print_memo_table
  --------------------------
  Imprime la tabla de memoización.
  Para cada celda:
    - Si la celda en el laberinto es 0, se imprime "X" (inaccesible).
    - Si el valor en la tabla memo es -1 (no calculado), se imprime "-".
    - Si el valor es INT_MAX, se imprime "X" (sin camino válido).
    - En otro caso, se imprime el valor numérico.
*/
void print_memo_table(const vector<vector<int>> &memo, const vector<vector<int>> &mat) {
    int rows = memo.size(), cols = memo[0].size();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(mat[i][j] == 0)
                cout << "X";
            else if(memo[i][j] == -1)
                cout << "-";
            else if(memo[i][j] == INT_MAX)
                cout << "X";
            else
                cout << memo[i][j];
            if(j < cols - 1)
                cout << " ";  // Espacio entre columnas
        }
        cout << endl; // Salto de línea al final de cada fila
    }
}

/*
  Función: print_iterative_table
  -------------------------------
  Imprime la tabla resultante de la versión iterativa (dp).
  Aplica la misma lógica de impresión que print_memo_table.
*/
void print_iterative_table(const vector<vector<int>> &dp, const vector<vector<int>> &mat) {
    int rows = dp.size(), cols = dp[0].size();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(mat[i][j] == 0)
                cout << "X";
            else if(dp[i][j] == INT_MAX)
                cout << "X";
            else
                cout << dp[i][j];
            if(j < cols - 1)
                cout << " ";
        }
        cout << endl;
    }
}


// ============================= OBTENER CAMINO DE LA LONGITUD CALCULADA =============================

/*
  Función: maze_parser
  ----------------------
  Reconstruye el camino mínimo encontrado y lo muestra en formato 2D.
  Se utiliza una tabla dp (calculada de forma iterativa) para conocer la longitud mínima hasta cada celda.
  Luego se retrocede desde la celda destino (rows-1, cols-1) hasta el origen (0,0) marcando el camino con '*'.
  Se crea una matriz "path" que inicialmente copia los valores del laberinto ('1' para accesible y '0' para inaccesible),
  y se reemplazan por '*' aquellas celdas que forman parte del camino.
*/
void maze_parser(const vector<vector<int>> &mat) {
    int rows = mat.size(), cols = mat[0].size();
    // Se crea y llena la tabla dp de forma iterativa.
    vector<vector<int>> dp(rows, vector<int>(cols, INT_MAX));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(mat[i][j] == 0)
                dp[i][j] = INT_MAX;
            else {
                if(i == 0 && j == 0)
                    dp[i][j] = 1;
                else {
                    int up = (i > 0 ? dp[i - 1][j] : INT_MAX);
                    int left = (j > 0 ? dp[i][j - 1] : INT_MAX);
                    int diag = (i > 0 && j > 0 ? dp[i - 1][j - 1] : INT_MAX);
                    int best = min(diag, min(up, left));
                    dp[i][j] = (best == INT_MAX ? INT_MAX : best + 1);
                }
            }
        }
    }
    // Si no existe camino (la celda destino es INT_MAX), se imprime "0".
    if(dp[rows - 1][cols - 1] == INT_MAX) {
        cout << "0" << endl;
        return;
    }
    // Se crea una matriz "path" que copia el laberinto: '1' para accesible, '0' para inaccesible.
    vector<vector<char>> path(rows, vector<char>(cols));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            path[i][j] = (mat[i][j] == 1 ? '1' : '0');
        }
    }
    // Se retrocede desde la celda destino hasta el origen marcando con '*' el camino.
    int i = rows - 1, j = cols - 1;
    while(true) {
        path[i][j] = '*';
        if(i == 0 && j == 0)
            break;
        int curr = dp[i][j];
        int next_i = i, next_j = j;
        bool found = false;
        // Se verifica si se puede retroceder por la diagonal.
        if(i > 0 && j > 0 && dp[i - 1][j - 1] == curr - 1) {
            next_i = i - 1;
            next_j = j - 1;
            found = true;
        } else if(i > 0 && dp[i - 1][j] == curr - 1) {  // O por arriba.
            next_i = i - 1;
            next_j = j;
            found = true;
        } else if(j > 0 && dp[i][j - 1] == curr - 1) {  // O por la izquierda.
            next_i = i;
            next_j = j - 1;
            found = true;
        }
        if(!found)
            break;
        i = next_i;
        j = next_j;
    }
    // Se imprime el camino en formato 2D: cada fila sin separadores entre caracteres.
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
            cout << path[i][j];
        cout << endl;
    }
}


// ============================= FUNCIÓN MAIN =============================

/*
  Función: main
  -------------
  - Procesa las opciones de línea de comandos.
  - Lee el laberinto desde un fichero (primera línea: filas y columnas; siguientes líneas: matriz).
  - Llama a las funciones de cada algoritmo (naive, memo, iterativa con matriz, iterativa con vector) y muestra sus resultados en una misma línea, separados por un espacio.
  - Si la opción --p2D está activa, llama a maze_parser para imprimir el camino en formato 2D.
  - Si la opción -t está activa, imprime las tablas intermedias (memoization table e iterative table).
*/
int main(int argc, char *argv[]) {
    bool flagT = false, flagP2D = false, flagIgnoreNaive = false;
    int mazeNaiveRes = 0, mazeMemoRes = 0, mazeItMatrixRes = 0, mazeItVectorRes = 0;
    string filename;
    // Validación de parámetros. Si falla, se muestra el uso correcto y se termina el programa.
    if(!validar_parametros(argc, argv, flagT, flagP2D, flagIgnoreNaive, filename))
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

    // Se imprimen los resultados de cada algoritmo en una misma línea, separados por un espacio.
    // Si la opción --ignore-naive está activada, se imprime "-" en lugar del resultado del algoritmo naive.
    if(flagIgnoreNaive)
        cout << "- ";
    else {
        mazeNaiveRes = maze_naive(mat, rows - 1, cols - 1);
        cout << (mazeNaiveRes == INT_MAX ? 0 : mazeNaiveRes) << " ";
    }
    mazeMemoRes = maze_memo(mat);
    cout << (mazeMemoRes == INT_MAX ? 0 : mazeMemoRes) << " ";
    mazeItMatrixRes = maze_it_matrix(mat);
    cout << (mazeItMatrixRes == INT_MAX ? 0 : mazeItMatrixRes) << " ";
    mazeItVectorRes = maze_it_vector(mat);
    cout << (mazeItVectorRes == INT_MAX ? 0 : mazeItVectorRes);
    cout << endl;

    // Si la opción --p2D está activada, se muestra el camino en formato 2D.
    if(flagP2D)
        maze_parser(mat);

    // Si la opción -t está activada, se imprimen las tablas intermedias.
    if(flagT) {
        vector<vector<int>> memo;
        compute_maze_memo(mat, memo); // Se computa la tabla de memoización.
        cout << "Memoization table:" << endl;
        print_memo_table(memo, mat);  // Se imprime la tabla de memoización.
        vector<vector<int>> dp;
        compute_maze_it_matrix(mat, dp); // Se computa la tabla iterativa.
        cout << "Iterative table:" << endl;
        print_iterative_table(dp, mat);  // Se imprime la tabla iterativa.
    }
    return 0;
}
