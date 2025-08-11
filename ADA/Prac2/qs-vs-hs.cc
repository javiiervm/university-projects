/*
ADA. 2024-25
Practice 2: "Empirical analysis by means of program-steps account of two sorting algorithms: Middle-Quicksort and Heapsort."
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <numeric>
#include <unistd.h>
#include <math.h>

using namespace std;

double PASOS = 0;

void resetPasos() {PASOS = 0;}

//--------------------------------------------------------------
// Middle-Quicksort:
// The algorithm selects the middle element of the array as the "pivot".
// In a process called "partitioning", it rearranges the elements so that
// all elements smaller than the pivot are placed to its left, and
// all elements greater than the pivot are placed to its right.
// The process is then repeated recursively on the two resulting
// subarrays (left and right of the pivot).
//--------------------------------------------------------------

void middle_QuickSort(int *v, long left, long right) {
    long i, j;
    int pivot;
    if (left < right) {
        i = left; j = right;
        pivot = v[(i + j) / 2];
        // pivot based partitioning:
        do {
            while (v[i] < pivot) {i++; PASOS++;}
            while (v[j] > pivot) {j--; PASOS++;}
            if (i <= j) {
                PASOS++;
                swap(v[i], v[j]);
                i++; j--;
            }
        } while (i <= j);
        // Repeat for each non-empty subarray:
        if (left < j) middle_QuickSort(v, left, j);
        if (i < right) middle_QuickSort(v, i, right);
    }
}

//--------------------------------------------------------------
// Heapsort:
// The algorithm works by repeatedly selecting the largest remaining element
// and placing it at the end of the vector in its correct position.
//
// To efficiently select the largest element, it builds a max-heap.
//
// The sink procedure is used for heap construction (or reconstruction).
//--------------------------------------------------------------

void sink(int *v, size_t n, size_t i)
// Sink an element (indexed by i) in a tree to maintain the heap property.
// n is the size of the heap.
{
    size_t largest;
    size_t l, r; // indices of left and right childs

    do {
        PASOS++;

        largest = i;  // Initialize largest as root
        l = 2 * i + 1;  // left = 2*i + 1
        r = 2 * i + 2;  // right = 2*i + 2

        // If the left child exists and is larger than the root
        if (l < n && v[l] > v[largest])
            largest = l;

        // If the right child exists and is larger than the largest so far
        if (r < n && v[r] > v[largest])
            largest = r;

        // If the largest is still the root, the process is done
        if (largest == i) break;

        // Otherwise, swap the new largest with the current node i and repeat the process with the children
        swap(v[i], v[largest]);
        i = largest;
    } while (true);
}

//--------------------------------------------------------------
// Heapsort algorithm (ascending sorting)
void heapSort(int *v, size_t n)
{
    // Build a max-heap with the input array ("heapify"):
    // Starting from the last non-leaf node (right to left), sink each element to construct the heap.
    for (size_t i = n / 2 - 1; true; i--) {
        PASOS++;
        sink(v, n, i);
        if (i == 0) break; // As size_t is an unsigned type
    }

    // At this point, we have a max-heap. Now, sort the array:
    // Repeatedly swap the root (largest element) with the last element and rebuild the heap.
    for (size_t i = n - 1; i > 0; i--) {
        PASOS++;
        // Move the root (largest element) to the end by swapping it with the last element.
        swap(v[0], v[i]);
        // Rebuild the heap by sinking the new root element.
        // Note that the heap size is reduced by one in each iteration (so the element moved to the end stays there)
        sink(v, i, 0);
        // The process ends when the heap has only one element, which is the smallest and remains at the beginning of the array.
    }
}

int main(void) {
    srand(0);   // Inicializamos la semilla del generador de números aleatorios
    cout.setf(ios::fixed);
    cout.precision(3);

    // Mostramos la tabla para las salidas
    cout << "# QUICKSORT VERSUS HEAPSORT" << endl
		<< "# Average processing Msteps (millions of program steps)" << endl
        << "# Number of samples (arrays of integer): 30" << endl
        << "# \t\t RANDOM ARRAYS \t\t\t SORTED ARRAYS \t\t\t REVERSE SORTED ARRAYS" << endl
        << "# \t\t ------------------------ \t ------------------------ \t ------------------------" << endl
        << "# Size \t\t QuickSort \t HeapSort \t QuickSort \t HeapSort \t QuickSort \t HeapSort" << endl
        << "# =======================================================================================================" << endl;

    // Iteramos sobre diferentes tamaños del array, de 2^15 hasta 2^20
    for (int exp = 15; exp <= 20; exp++){

        // ---------------------- INICIALIZACIÓN ----------------------

        size_t size = size_t(pow(2,exp));
        int* v_quicksort = new int [size];
		int* v_heapsort = new int [size];

        // Si la asignación de memoria falla, mostramos un error y terminamos el programa
        if (!v_quicksort || /*!v_creciente ||*/ !v_heapsort){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }

        cout << size << "\t\t" << flush;   // Mostramos el tamaño del array

        // ---------------------- VECTOR ALEATORIO ----------------------

        for (size_t j = 0; j < size; j++) {
                v_quicksort[j] = rand();
                v_heapsort[j] = v_quicksort[j];
            }

        for(int i = 0; i < 30; i++)
            middle_QuickSort(v_quicksort, 0, size - 1);

		cout << (PASOS/1000000)/30 << flush << "\t\t";
		resetPasos();   // Volvemos a poner los pasos a cero para volver a empezar a contar para el siguiente

        for(int i = 0; i < 30; i++)
            heapSort(v_quicksort, size);
        
        cout << (PASOS/1000000)/30 << flush << "\t\t";
		resetPasos();

        // Verificamos la correcta ordenación del vector
		for (size_t i = 1; i < size; i++)
			if (v_quicksort[i] < v_quicksort[i-1]){ 
				cerr << "Panic, array not sorted! " << i << endl; 
				exit(EXIT_FAILURE);            
			}

        // ---------------------- VECTOR CRECIENTE ----------------------

        for(int i = 0; i < 30; i++)
            middle_QuickSort(v_quicksort, 0, size - 1);
        
        cout << (PASOS/1000000)/30 << flush << "\t\t";
		resetPasos();

        for(int i = 0; i < 30; i++)
            heapSort(v_quicksort, size);
        
        cout << (PASOS/1000000)/30 << flush << "\t\t";
		resetPasos();

        // Verificamos la correcta ordenación del vector
        for (size_t i = 1; i < size; i++)
			if (v_quicksort[i] < v_quicksort[i-1]){ 
				cerr << "Panic, array not sorted! " << i << endl; 
				exit(EXIT_FAILURE);            
			}

        // ---------------------- VECTOR DECRECIENTE ----------------------

        /*for (size_t j = 0; j < size; j++)  {
            v_heapsort[j] = (size - 1) - j;
            v_quicksort[j] = v_heapsort[j];
        }*/

        for(size_t j = 0; j < size/2; j++) {
            swap(v_heapsort[j], v_heapsort[size-j-1]);
            v_quicksort[j] = v_heapsort[j];
        }
            
        for(int i = 0; i < 30; i++)
            middle_QuickSort(v_heapsort, 0, size - 1);
        
        cout << (PASOS/1000000)/30 << flush << "\t\t";
		resetPasos();

        for(int i = 0; i < 30; i++)
            heapSort(v_heapsort, size);
        
        cout << (PASOS/1000000)/30 << flush << "\t\t";
		resetPasos();

        // Verificamos la correcta ordenación del vector
		for (size_t i = 1; i < size; i++)
			if (v_heapsort[i] < v_heapsort[i-1]){ 
				cerr << "Panic, array not sorted! " << i << endl; 
				exit(EXIT_FAILURE);            
			}

        delete[] v_quicksort; 
        delete[] v_heapsort;    

        cout << endl; 
    }
}