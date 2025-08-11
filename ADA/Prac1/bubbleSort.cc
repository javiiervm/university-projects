/*
ADA. 2024-25
Práctica 1.
*/

#include <unistd.h>  // Para funcionalidades del sistema operativo (no se usa en este código)
#include <iostream>  // Para entrada y salida estándar
#include <math.h>    // Para operaciones matemáticas como pow()
#include <ctime>     // Para medir tiempos de ejecución

using namespace std;

//--------------------------------------------------------------
// Implementación del algoritmo de ordenación Bubble Sort
void bubbleSort(int * v, size_t size){
    // Iteramos sobre el array de tamaño `size`
    for (size_t i = 1; i < size; i++)
        // Recorremos los elementos no ordenados del array
        for (size_t j = 0; j < size - i; j++)
            // Si el elemento actual es mayor que el siguiente, los intercambiamos
            if (v[j] > v[j+1]){ 
                int aux = v[j];  // Guardamos el valor de v[j] en una variable auxiliar
                v[j] = v[j+1];   // Asignamos el valor de v[j+1] a v[j]
                v[j+1] = aux;    // Asignamos el valor original de v[j] a v[j+1]
            }
}  
//--------------------------------------------------------------                

int main(void){
    srand(0);  // Inicializamos la semilla del generador de números aleatorios

    // Mostramos encabezados para la salida de tiempos de ejecución
    cout << "# BubbleSort CPU times in milliseconds:" << endl
        << "# Size \t CPU time (ms.)" << endl
        << "# ----------------------------" << endl;

    // Iteramos sobre diferentes tamaños del array, de 2^10 hasta 2^16
    for (int exp = 10; exp <= 16; exp++){
        size_t size = size_t(pow(2, exp)); // Calculamos el tamaño como 2^exp
        int* v = new int[size]; // Reservamos memoria para el array dinámicamente

        // Si la asignación de memoria falla, mostramos un error y terminamos el programa
        if (!v){
            cerr << "Error, not enough memory!" << endl;
            exit(EXIT_FAILURE);  
        }

        cout << size << "\t\t" << std::flush; // Mostramos el tamaño del array

        // Llenamos el array con números aleatorios
        for (size_t j = 0; j < size; j++) 
            v[j] = rand(); 

        // Medimos el tiempo de ejecución del algoritmo de ordenación
        auto start = clock();  // Guardamos el tiempo inicial
        bubbleSort(v, size);   // Ejecutamos Bubble Sort
        auto end = clock();    // Guardamos el tiempo final

        // Calculamos y mostramos el tiempo de ejecución en milisegundos
        cout << 1000.0 * (end - start) / CLOCKS_PER_SEC  << endl;

        // Verificamos que el array está ordenado correctamente
        for (size_t i = 1; i < size; i++)
            if (v[i] < v[i-1]){ // Si encontramos un elemento desordenado
                cerr << "Panic, array not sorted! " << i << endl; 
                exit(EXIT_FAILURE); // Terminamos el programa con error
            }

        delete[] v; // Liberamos la memoria reservada para el array
    }
}


























































/*
ADA. 2024-25
Práctica 1.
*/

/*#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;

//--------------------------------------------------------------
// Bubble sort basic algorithm

void bubbleSort(int * v, size_t size){

    for (size_t i = 1; i < size; i++)
        for (size_t j = 0; j < size - i; j++)
            if (v[j]>v[j+1]){ swap
                int aux = v[j]; 
                v[j] = v[j+1]; 
                v[j+1] = aux;
            }
}  
//--------------------------------------------------------------                


int main(void){

    srand(0);

    cout << "# BubbleSort CPU times in milliseconds:"
        << endl
        << "# Size \t CPU time (ms.)"
        << endl
        << "# ----------------------------"
        << endl;

    for (int exp = 10; exp <= 16; exp++){
        size_t size = size_t( pow(2,exp) );
        int* v = new int [size];
        if (!v){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }

        cout << size << "\t\t" << std::flush;

        for (size_t j = 0; j < size; j++) 
            v[j] = rand(); 

        auto start = clock();
        bubbleSort(v,size);
        auto end = clock();


        cout << 1000.0 * (end-start) / CLOCKS_PER_SEC  << endl;

        for (size_t i = 1; i < size; i++)
            if (v[i] < v[i-1]){ 
                cerr << "Panic, array not sorted! " << i << endl; 
                exit(EXIT_FAILURE);            
            }

        delete[] v; 
    }
}*/


