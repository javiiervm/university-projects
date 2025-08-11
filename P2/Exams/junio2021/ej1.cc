#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

typedef struct {
    string nombre;
    string materia;
    int tarifa;
    int valoracion;
} TEmpleado;

vector<TEmpleado> empleados;

int mostrarMenu();
bool procesarArgumentos(int argc, char *argv[], bool &argumentos);
void cargarDatos();
void insertarEmpleado();
void mostrarEmpleado(bool argumentos, string cadena);
void guardarDatos();

int main(int argc, char *argv[]) {
    // Variables locales
    bool argumentos = false;
    bool error = false;
    int eleccion = -1;
    string materia;

    // Cargar datos del fichero binario mercenacas.dat (si existe)
    cargarDatos();

    // Comprobar parámetros
    error = procesarArgumentos(argc, argv, argumentos);
    if(error)
        return 1;
    if(argumentos)
        return 0;

    // Menú: insertar empleados, introducir materia y mostrar datos empleados, salir del programa
    while(eleccion!=0) {
        eleccion = mostrarMenu();
        switch (eleccion) {
            case 1:
                insertarEmpleado();
                break;
            
            case 2:
                mostrarEmpleado(argumentos, materia);
                break;
            
            default:
                guardarDatos();
                break;
        }
    }

    return 0;
}

int mostrarMenu() {
    // Variables locales
    int eleccion = 0;

    cout << "---------------- MENÚ DEL PROGRAMA ----------------" << endl
        << "1. Añadir empleado" << endl
        << "2. Buscar por materia" << endl
        << "0. Salir" << endl
        << "Tu elección: ";
    cin >> eleccion;
    if(eleccion < 0 || eleccion > 2)
        mostrarMenu();

    return eleccion;
}

bool procesarArgumentos(int argc, char *argv[], bool &argumentos) {
    if(argc == 1)
        return false;
    
    if(argc != 1 && argc != 3) {
        cout << "ERROR ARGUMENTOS" << endl;
        return true;
    }
    
    if(strcmp(argv[1], "-mat") != 0) {
        cout << "ERROR ARGUMENTOS" << endl;
        return true;
    }

    argumentos = true;
    mostrarEmpleado(argumentos, argv[2]);    

    return false;
}

void cargarDatos() {
    TEmpleado empleado;

    ifstream fichero;
    fichero.open("mercenacas.dat", ios::in | ios::binary);

    if(!fichero.is_open())
        return;

    while (fichero.read((char *)&empleado, sizeof(empleado))) {
        empleados.push_back(empleado);
    }
    
    fichero.close();
}

void insertarEmpleado() {
    // Variables locales
    TEmpleado empleado;
    
    cout << "Nombre y apellidos: ";
    cin >> empleado.nombre;
    cout << "Materia: ";
    cin >> empleado.materia;
    cout << "Tarifa: ";
    cin >> empleado.tarifa;
    cout << "Valoración: ";
    cin >> empleado.valoracion;
    while (empleado.valoracion < 1 || empleado.valoracion > 5) {
        cout << "LA VALORACIÓN DEBE SITUARSE ENTRE 1 Y 5" << endl << "Valoración: ";
        cin >> empleado.valoracion;
    }
    empleados.push_back(empleado);
}


void mostrarEmpleado(bool argumentos, string materia) {
    if(!argumentos) {
        cout << "Introduce una materia: ";
        cin >> materia;
    }

    for(unsigned int i = 0; i < empleados.size(); i++) {
        if(empleados[i].materia == materia) {
            cout << empleados[i].nombre << endl << empleados[i].tarifa << endl << empleados[i].valoracion << endl;
        }
    }
}

void guardarDatos() {
    ofstream fichero;
    fichero.open("mercenacas.dat", ios::out | ios::binary);

    if(!fichero.is_open()) {
        cout << "ERROR: No se han podido guardar los datos" << endl;
        return;
    }

    for(unsigned int i = 0; i < empleados.size(); i++) {
        TEmpleado empleado;
        empleado.nombre = empleados[i].nombre;
        empleado.materia = empleados[i].materia;
        empleado.tarifa = empleados[i].tarifa;
        empleado.valoracion = empleados[i].valoracion;
        fichero.write((const char *)&empleado, sizeof(empleado));
    }
    
    fichero.close();
}