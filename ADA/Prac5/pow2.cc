#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

unsigned long PASOS = 0;

void resetPasos() {PASOS = 0;}

// Coste: \Theta(log n)
unsigned long pow2_1(unsigned n) {
    // 2^n = 2^(n/2) * 2^(n/2) * 2^(n%2)
    if(n == 1) return 2;
    PASOS++;
    unsigned long resultado = pow2_1(n/2);
    if(n % 2 == 0) return resultado * resultado;
    return resultado * resultado * 2;
}

// Coste: \Theta(2^n)
unsigned long pow2_2(unsigned n) {
    // 2^n = 2^(n-1) + 2^(n-1)
    if(n == 1) return 2;
    PASOS++;
    return pow2_2(n-1) + pow2_2(n-1);
}

// Coste: \Theta(n)
unsigned long pow2_3(unsigned n) {
    // 2^n = 2 * 2^(n-1)
    if(n == 1) return 2;
    PASOS++;
    return 2 * pow2_3(n-1);
}

int main(void) {
    // Abrimos el archivo donde se guardarán los resultados
    ofstream outfile("pow2.steps");

    // Iteramos sobre los exponentes
    for (int exp = 1; exp <= 30; exp++) {
        // Calculamos el resultado de 2^exp
        unsigned long result = pow(2, exp);
        // Lo escribimos en la primera columna
        outfile << exp << "\t";

        // Comprobamos que el resultado de pow2_1 sea correcto
        if (pow2_1(exp) == result) {
            // Si lo es, escribimos el número de pasos en la segunda columna
            outfile << PASOS << "\t";
        } else {
            // Si no lo es, escribimos "ERROR"
            outfile << "ERROR\t";
        }
        // Reinicializamos el número de pasos
        resetPasos();

        // Comprobamos que el resultado de pow2_2 sea correcto
        if (pow2_2(exp) == result) {
            // Si lo es, escribimos el número de pasos en la tercera columna
            outfile << PASOS << "\t";
        } else {
            // Si no lo es, escribimos "ERROR"
            outfile << "ERROR\t";
        }
        // Reinicializamos el número de pasos
        resetPasos();

        // Comprobamos que el resultado de pow2_3 sea correcto
        if (pow2_3(exp) == result) {
            // Si lo es, escribimos el número de pasos en la cuarta columna
            outfile << PASOS << "\n";
        } else {
            // Si no lo es, escribimos "ERROR"
            outfile << "ERROR\n";
        }
        // Reinicializamos el número de pasos
        resetPasos();
    }

    // Cerramos el archivo
    outfile.close();
}