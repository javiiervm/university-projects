/*
ADA 2024-25
Práctica 1: "Empirical analysis of Quicksort average-time complexity."
*/

#include <iostream>
#include <stdlib.h>  // Para generar números aleatorios
#include <math.h>    // Para operaciones matemáticas como pow()
#include <ctime>     // Para medir tiempos de ejecución
#include <vector>    // Para usar un vector y almacenar los tiempos de las repeticiones

using namespace std;

//--------------------------------------------------------------
// Middle QuickSort
void middle_QuickSort(int * v, long left, long right) {
    long i, j;            // Variables para los índices de izquierda y derecha
    int pivot, aux;       // Variable para el pivote y una auxiliar para el intercambio
    
    // Condición de terminación del algoritmo, el arreglo ya está ordenado si left >= right
    if (left < right) {
        i = left;         // Establecemos i al índice izquierdo
        j = right;        // Establecemos j al índice derecho
        
        // Elegimos el pivote como el valor en la posición media del arreglo
        pivot = v[(i + j) / 2];
        
        // Se ejecuta el ciclo hasta que los índices se crucen
        do {
            // Mover el índice izquierdo hacia la derecha mientras el valor en v[i] sea menor que el pivote
            while (v[i] < pivot) i++;
            
            // Mover el índice derecho hacia la izquierda mientras el valor en v[j] sea mayor que el pivote
            while (v[j] > pivot) j--;
            
            // Si los índices no se han cruzado, intercambiamos los elementos en v[i] y v[j]
            if (i <= j) {
                aux = v[i];   // Guardamos el valor de v[i] en aux
                v[i] = v[j];  // Colocamos v[j] en v[i]
                v[j] = aux;   // Colocamos el valor de aux (original v[i]) en v[j]
                
                // Avanzamos el índice izquierdo y retrocedemos el índice derecho
                i++;
                j--;
            }
        } while (i <= j);  // Continuamos el ciclo hasta que i y j se crucen
        
        // Si el índice izquierdo es menor que el índice derecho, ordenamos la sublista izquierda (desde left hasta j)
        if (left < j) middle_QuickSort(v, left, j);
        
        // Si el índice derecho es mayor que el índice izquierdo, ordenamos la sublista derecha (desde i hasta right)
        if (i < right) middle_QuickSort(v, i, right);
    }
}

int main(void) {
    srand(0);  // Inicializamos la semilla del generador de números aleatorios

    cout << "# QuickSort CPU-times in milliseconds:" << endl
        << "# Size \t CPU time (ms.)" << endl
        << "# ----------------------------" << endl;

    // Iteramos sobre las potencias desde 2^15 hasta 2^20
    for (int exp = 15; exp <= 20; exp++) {
        size_t size = size_t(pow(2, exp)); // Calculamos el tamaño como 2^exp
        vector<double> times; // Vector para almacenar los tiempos de las 30 repeticiones
        
        // Para que la muestra sea significativa haremos 20 repeticiones
        for(int i = 0; i < 30; i++) {
            int* v = new int[size]; // Reservamos memoria para el array dinámicamente

            // Si la asignación de memoria falla, mostramos un error y terminamos el programa
            if (!v) {
                cerr << "Error, not enough memory!" << endl;
                exit(EXIT_FAILURE);  
            }

            // Llenamos el array con números aleatorios
            for (size_t j = 0; j < size; j++) 
                v[j] = rand(); 

            // Medimos el tiempo de ejecución del algoritmo de ordenación
            auto start = clock();  // Guardamos el tiempo inicial
            middle_QuickSort(v, 0, size - 1);   // Ejecutamos Quicksort
            auto end = clock();    // Guardamos el tiempo final

            // Calculamos el tiempo de ejecución en milisegundos y lo guardamos en el vector
            times.push_back(1000.0 * (end - start) / CLOCKS_PER_SEC);

            // Verificamos que el array está ordenado correctamente
            for (size_t i = 1; i < size; i++) {
                if (v[i] < v[i - 1]) { // Si encontramos un elemento desordenado
                    cerr << "Panic, array not sorted! " << i << endl; 
                    exit(EXIT_FAILURE); // Terminamos el programa con error
                }
            }

            delete[] v; // Liberamos la memoria reservada para el array
        }

        // Calculamos el promedio de los tiempos de las 30 repeticiones
        double suma = 0;
        for(double time : times)
            suma = suma + time;
        double average = suma/times.size();

        // Mostramos el resultado
        cout << size << "\t\t" << flush << average << endl; 
    }

    return 0;
}


