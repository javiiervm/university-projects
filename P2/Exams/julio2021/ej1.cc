#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>

using namespace std;

typedef struct {
    unsigned int codigo;
    char nombre[100];
    double importeTotal;
    bool riesgo;
} TCliente;

vector<TCliente> clientes;

bool procesarArg(int argc, char *argv[], bool &iFlag, bool &sFlag, string &nombreFichero);
bool cargarDatos(string nombreFichero, bool iFlag, bool sFlag);
void showMenu(int &eleccion);
void ampliarPrestamo();
void mostrarRiesgo();

int main(int argc, char *argv[]) {
    // Variables locales
    bool iFlag = false, sFlag = false, error = false, acabar = false;
    string nombreFichero;
    int eleccion = 0;

    // Procesar argumentos
    error = procesarArg(argc, argv, iFlag, sFlag, nombreFichero);
    if(error) {
        cout << "ERROR ARGUMENTOS" << endl;
        return 1;
    }

    // Cargar datos del fichero de texto
    error = cargarDatos(nombreFichero, iFlag, sFlag);
    if(error)
        return 2;

    // Menú con opciones
    do {
        showMenu(eleccion);
        switch (eleccion) {
            case 1:
                ampliarPrestamo();
                break;
            
            case 2:
                mostrarRiesgo();
                break;
            
            default:
                error = guardarDatos(nombreFichero, iFlag, sFlag);
                acabar = true;
                if(error)
                    return 3;
                break;
        }
    } while(!acabar);

    return 0;
}

bool procesarArg(int argc, char *argv[], bool &iFlag, bool &sFlag, string &nombreFichero) {
    if(argc != 1 && argc != 3)
        return true;
    
    if(argv[1]=="-i") {
        iFlag = true;
        nombreFichero = argv[2];
    } else if(argv[1]=="-s") {
        sFlag = true;
        nombreFichero = argv[2];
    } else {
        return true;
    }

    return false;
}

bool cargarDatos(string nombreFichero, bool iFlag, bool sFlag) {
    ifstream fichero;
    string s;

    if(iFlag || sFlag)
        fichero.open(nombreFichero, ios::in);
    else
        fichero.open("endeudados.txt", ios::in);
    
    if(!fichero.is_open()) {
        cout << "ERROR FICHERO" << endl;
        return true;
    }

    while(getline(fichero, s)) {
        TCliente cliente;
        cliente.codigo = stoi(s);
        getline(fichero, s);
        for(unsigned int i = 0; i < s.size(); i++)
            cliente.nombre[i] = s[i];
        getline(fichero, s);
        cliente.importeTotal = stod(s);
        getline(fichero, s);
        if(s=="T")
            cliente.riesgo = true;
        else
            cliente.riesgo = false;
        clientes.push_back(cliente);
    }

    fichero.close();

    if(sFlag) {
        for(unsigned int i = 0; i < clientes.size(); i++)
            cout << clientes[i].codigo << endl << clientes[i].nombre << endl << clientes[i].riesgo << endl;
    }

    return false;
}

void showMenu(int &eleccion) {
    cout << "-------------- MAIN MENU --------------" << endl;
    cout << "1. Ampliar préstamo" << endl;
    cout << "2. Mostrar clientes de riesgo" << endl;
    cout << "0. Salir del programa" << endl;
    do {
        cout << "Elija una opción: ";
        cin >> eleccion;
    } while(eleccion < 0 || eleccion > 2);
}

void ampliarPrestamo() {
    unsigned int cliente = 0, ubicacion = 0;
    bool encontrado = false;
    double importe = 0.0;

    cout << "Introduce el código del cliente: ";
    cin >> cliente;

    for(unsigned int i = 0; i < clientes.size(); i++) {
        if(clientes[i].codigo == cliente) {
            encontrado = true;
            ubicacion = i;
            break;
        }
    }

    if(!encontrado) {
        cout << "ERROR CLIENTE" << endl;
        return;
    }

    if(!clientes[ubicacion].riesgo) {
        cout << "Introduce un importe: ";
        cin >> importe;

        if(clientes[ubicacion].importeTotal+importe<=5000 && importe > 0) {
            clientes[ubicacion].importeTotal = clientes[ubicacion].importeTotal + importe;
        } else {
            cout << "ERROR" << endl;
        }
    } else {
        cout << "ERROR" << endl;
    }
}

void mostrarRiesgo() {
    double total = 0.0;
    for(unsigned int i = 0; i < clientes.size(); i++) {
        if(clientes[i].riesgo) {
            cout << clientes[i].codigo << endl << clientes[i].nombre << endl << clientes[i].importeTotal << endl;
            total = total + clientes[i].importeTotal;
        }
    }
    cout << "DEUDA TOTAL: " << total << endl;
}

bool guardarDatos(string nombreFichero, bool iFlag, bool sFlag) {
    ofstream fichero;
    string s;

    if(iFlag || sFlag)
        fichero.open(nombreFichero, ios::out);
    else
        fichero.open("endeudados.txt", ios::out);
    
    if(!fichero.is_open()) {
        cout << "ERROR FICHERO" << endl;
        return true;
    }

    for(unsigned int i = 0; i < clientes.size(); i++) {
        cout << clientes[i].codigo << endl << clientes[i].nombre << endl << clientes[i].importeTotal << endl;
        if(clientes[i].riesgo)
            cout << "T" << endl;
        else
            cout << "F" << endl;
    }

    fichero.close();
    return false;
}