#include <iostream>
#include <string.h>

using namespace std;

// EXERCISE 1: Conditional sentence
bool multiple (int a, int b) {
    if (a != 0 && b != 0) {
        if (a % b == 0 || b % a == 0) {
            return true;
        }
    }
    return false;
}

// EXERCISE 2: Repetitive sentence
int printN(int n) {
    int totalAsterics = 0;
    if (n < 4) {
        cout << "ERROR" << endl;
    } else {
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (j == 0 || j == i || j == n - 1) {
                        cout << "*";
                        totalAsterics++;
                    } else {
                        cout << " ";
                    }
                }
            cout << endl;
        }
    }
    return totalAsterics;
}

// EXERCISE 3: Prime numbers
bool isPrime(int p) {
    for (int i = 2; i <= p/2; i++) {
        if (p % i == 0 || p == 1) {
            return false;
        }
    }
    return true;
}

int firstPrimes(int n) {
    bool numberPrime;
    int sum = 0, counter = 0;
    for (int i = 1; counter < n; i++) {
        if (i == 1) {
            numberPrime = false;
        } else {
            numberPrime = isPrime(i);
        }
        if (numberPrime == true) {
            cout << i << " ";
            counter = counter + 1;
            sum = sum + i;
        }
    }
    cout << endl;
    return sum;
}

// EXERCISE 4: Goldbach
void Goldbach(int n,int &p1,int &p2) {
    bool numberPrime;
    int lowest = 0, other = 0;
    for (int i = 1; i <= n; i++) {   // El valor de i corresponde a p1, y se mantiene fijo mientras se prueban todos los posibles valores de p2
        if (i == 1) {
            numberPrime = false;
        } else {
            numberPrime = isPrime(i);
        }
        if (numberPrime == true) {
            for (int j = 1; j <= n; j++) {   // Aquí vamos probando todos los posibles valores de p2
                if (j == 1) {
                    numberPrime = false;
                } else {
                    numberPrime = isPrime(j);
                }
                if (numberPrime == true) {
                    if (i + j == n) {
                        lowest = i;
                        other = j;
                        i = n + 1;
                        j = n + 1;
                    }
                }
            }
        }
    }
    p1 = lowest;
    p2 = other;
}

// EXERCISE 5: Vector search
int count(int v[],const int TAMVECTOR, int n) {
    int times = 0;
    for (int i = 0; i < TAMVECTOR; i++) {
        if (v[i] == n) {
            times = times + 1;
        }
    }
    return times;
}

int position(int v[],const int TAMVECTOR, int n) {
    for (int i = 0; i < TAMVECTOR; i++) {
        if (v[i] == n) {
            return i;
        }
    }
    return -1;
}

bool search(int v[], const int TAMVECTOR, int n) {
    for (int i = 0; i < TAMVECTOR; i++) {
        if (v[i] == n) {
            return true;
        }
    }
    return false;
}

// EXERCISE 6: Minimum and maximum of a vector
int minOdds(int v[],const int TAMVECTOR) {
    int number = 0, position = 0;
    for (int i = 0; i < TAMVECTOR; i++) {
        if (v[i] % 2 != 0) {
            if (number == 0 && position == 0) {
                number = v[i];
                position = i;
            } else {
                if (v[i] < number) {
                    number = v[i];
                    position = i;
                }
            }
        }
    }
    if (number != 0) {
        return number;
    }
    return -1;
}

int posMaxMultFive(int v[],const int TAMVECTOR) {
    int number = 0, position = 0;
    for (int i = 0; i < TAMVECTOR; i++) {
        if (v[i] % 5 == 0 || v[i] == 0) {
            if (number == 0 && position == 0) {
                number = v[i];
                position = i;
            } else {
                if (v[i] > number) {
                    number = v[i];
                    position = i;
                }
            }
        }
    }
    if (number != 0) {
        return position;
    }
    return -1;
}

// EXERCISE 7: Delete chars
void deleteChar(char str[], char c) {
    int length = strlen(str);
    for (int i = 0; i < length; i++) {
        if (str[i] == c) {
            for (int j = i; j < length; j++) {
                str[j] = str[j + 1];
                i = 0;
            }
        }
    }
}