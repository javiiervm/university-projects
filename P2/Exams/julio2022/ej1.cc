#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

typedef struct {
    unsigned int DNI;
    char nombre[49];
    char tarjeta[16];
    int saldo;
} TCliente;

vector<TCliente> clientes;
vector<string> dnisofuscados;

bool analizarArgumentos(int argc, char *argv[], bool &fFlag, bool &dniFlag, bool &tFlag, string &binarioName);
bool leerBinario(string nombre);
void ofuscardni();
void ofuscartarjeta();
bool escribirTexto(bool dniFlag, bool tFlag);

int main(int argc, char *argv[]) {
    // Variables locales
    bool error = false, fFlag = false, dniFlag = false, tFlag = false;
    string binarioName;

    // Analizar argumentos
    error = analizarArgumentos(argc, argv, fFlag, dniFlag, tFlag, binarioName);
    if(error) {
        cout << "ERROR ARGUMENTOS" << endl;
        return 1;
    }

    // Abrir fichero binario y leer su contenido
    error = leerBinario(binarioName);
    if(error)
        return 2;

    // Ofuscar dni (opcional)
    if(dniFlag)
        ofuscardni();

    // Ofuscar tarjeta (opcional)
    if(tFlag)
        ofuscartarjeta();

    // Crear fichero de texto y transferir datos
    error = escribirTexto(dniFlag, tFlag);
    if(error)
        return 3;

    return 0;
}

bool analizarArgumentos(int argc, char *argv[], bool &fFlag, bool &dniFlag, bool &tFlag, string &binarioName) {
    if(argc < 3 || argc > 5)
        return true;
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-f") == 0) {
            if(fFlag || i + 1 > argc)
                return true;
            fFlag = true;
            binarioName = argv[i+1];
            i = i + 1;
        } else if(strcmp(argv[i], "-dni") == 0) {
            dniFlag = true;
        } else if(strcmp(argv[i], "-t") == 0) {
            tFlag = true;
        } else {
            return true;
        }
    }

    if(!fFlag)
        return true;

    return false;
}

bool leerBinario(string nombre) {
    ifstream fichero;
    TCliente cliente;

    fichero.open(nombre, ios::binary);

    if(!fichero.is_open()) {
        cout << "ERROR: No se pudo abrir el fichero" << endl;
        return true;
    }

    while(fichero.read((char *)&cliente, sizeof(cliente)))
        clientes.push_back(cliente);

    fichero.close();

    return false;
}

void ofuscardni() {
    char letras[] = {'T', 'R', 'W', 'A', 'G', 'M', 'Y', 'F', 'P', 'D'};
    for(unsigned int i = 0; i < clientes.size(); i++) {
        string dni = to_string(clientes[i].DNI);
        for(int j = 0; j < 16; j++) {
            dni[j] = letras[j];
        }
        dnisofuscados.push_back(dni);
    }
}

void ofuscartarjeta() {
    for(unsigned int i = 0; i < clientes.size(); i++) {
        for(int j = 0; j < 16; j++) {
            if(j >= 4 && j <= 12)
                clientes[i].tarjeta[j] = '*';
        }
    }
}

bool escribirTexto(bool dniFlag, bool tFlag) {
    ofstream fichero;
    float suma = 0.0;
    fichero.open("datos.txt", ios::out);

    if(!fichero.is_open()) {
        cout << "ERROR: No se pudo abrir el fichero" << endl;
        return true;
    }

    for(unsigned int i = 0; i < clientes.size(); i++) {
        if(dniFlag)
            cout << dnisofuscados[i];
        else
            cout << clientes[i].DNI;
        cout << "," << clientes[i].nombre << "," << clientes[i].tarjeta << "," << clientes[i].saldo << endl;
        suma = suma + (-1)*clientes[i].saldo;
    }

    cout << "Total: " << suma << " (" << suma/clientes.size() << " por cliente)" << endl;

    fichero.close();

    return false;
}