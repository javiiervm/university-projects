#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

enum acciones {walk, jump, crouch, somersault};

typedef struct {
    acciones accion;
    float tiempo;
    int fuerza;
} TAcciones;

vector<TAcciones> accionesRobot = {};

typedef struct {
    char name[50];
    int identificador;
} TRobot;

bool lectorParametros(int argc, char *argv[], string &ficheroEntrada, string &ficheroSalida);
bool openReadFile(ifstream& dataFile, string fileName);
int leerEntrada(ifstream& dataFile, int &analizadas);
bool openWriteFile(ofstream& dataFile, string fileName);
void introducirNombreRob(ofstream& dataFile);
void llenarFicheroBinario(ofstream& dataFile);

int main(int argc,char *argv[]) {
    // Variables locales
    bool errorParametros = false;
    bool errorApertura = false;
    int defectuosas = 0, analizadas = 0;
    float resultado = 0.0;
    string ficheroEntrada;
    string ficheroSalida;
    ifstream entradaFile;
    ofstream salidaFile;

    // Leer parámetros
    errorParametros = lectorParametros(argc, argv, ficheroEntrada, ficheroSalida);
    if(errorParametros) {
        cout << "ERROR: Argumentos inválidos" << endl;
        return 1;
    }

    // Abrir el fichero de entrada
    errorApertura = openReadFile(entradaFile, ficheroEntrada);
    if(errorApertura) {
        cout << "ERROR: El fichero de entrada " << ficheroEntrada << " no se puede abrir" << endl;
        return 2;
    }

    // Leer datos del fichero, comprobar su validez, mostrar número de instrucciones erróneas
    defectuosas = leerEntrada(entradaFile, analizadas);
    resultado = (static_cast<float>(defectuosas) / analizadas) * 100;
    if(defectuosas>0)
        cout << "Encontradas " << defectuosas << " instrucciones erróneas de " << analizadas << " (" 
            << resultado << "%)" << endl;

    // Crear y abrir fichero binario, si no se abre mostrar error y terminar programa
    errorApertura = openWriteFile(salidaFile, ficheroSalida);
    if(errorApertura) {
        cout << "ERROR: El fichero de salida " << ficheroSalida << " no se puede abrir" << endl;
        return 3;
    }

    // Rellenar fichero binario con nombre del robot e identificador, que se le piden al usuario
    introducirNombreRob(salidaFile);

    // Escribir en el fichero binario las acciones leídas en el de texto
    llenarFicheroBinario(salidaFile);

    salidaFile.close();    // Cerrar el fichero al terminar

    return 0;
}

/* Función que comprueba los parámetros recibidos por el main
argc: número de argumentos
argv: argumentos
return: true si se ha detectado algún error, false si no
*/
bool lectorParametros(int argc, char *argv[], string &ficheroEntrada, string &ficheroSalida) {
    // Variables locales
    bool flagEntrada = false;
    
    // Verifica que hay un número par de argumentos (excluyendo el nombre del programa)
    if((argc - 1) % 2 != 0) {
        return true;  // Los argumentos deben venir en pares
    }

    // Recorre los argumentos
    for(int i = 1; i < argc; i += 2) {
        if(strcmp(argv[i], "-i") == 0) {
            if(flagEntrada) {  // Si esta señal está activada significa que ese parámetro ya se ha introducido antes y eso es un error
                return true;
            }
            ficheroEntrada = argv[i + 1];
            flagEntrada = true;
        } else if(strcmp(argv[i], "-o") == 0) {
            ficheroSalida = argv[i + 1];
        } else {
            return true;
        }
    }

    // El parámetro del nombre del fichero de entrada es obligatorio
    if(!flagEntrada) {
        return true;
    }

    // Si no se especifica el fichero de salida, se usa "output.dat" por defecto
    if(ficheroSalida.empty()) {
        ficheroSalida = "output.dat";
    }

    return false;
}

/* Función que abre ficheros, si no lo consigue envía una señal de error
dataFile: archivo
fileName: nombre archivo
return: true si hay errores, false si no
*/
bool openReadFile(ifstream& dataFile, string fileName) {
    // Abrimos el fichero
    dataFile.open(fileName);    // Modo lectura
    if(!dataFile.is_open())
        return true;
    return false;
}

/* Función que lee el fichero de entrada
dataFile: fichero de entrada
return: nada
*/
int leerEntrada(ifstream& dataFile, int &analizadas) {
    // Variables locales
    string currentLine;
    int defectuosas = 0;

    while (getline(dataFile, currentLine)) {
        // Variables locales
        TAcciones newAction;
        acciones accion;
        string accionString, tiempoString, fuerzaString;
        bool error = false;
        float tiempo;
        int fuerza, flag = 1;

        for(unsigned int i = 0; i < currentLine.size(); i++) {
            if(currentLine[i]==';') {
                flag = flag + 1;
            } else {
                switch (flag) {
                    case 1:
                        accionString.push_back(currentLine[i]);
                        break;
                    case 2:
                        tiempoString.push_back(currentLine[i]);
                        break;
                    case 3:
                        fuerzaString.push_back(currentLine[i]);
                        break;                    
                    default:
                        break;
                }
            }
        }

        if (accionString == "walk") 
            accion = walk;
        else if (accionString == "jump") 
            accion = jump;
        else if (accionString == "crouch") 
            accion = crouch;
        else if (accionString == "somersault") 
            accion = somersault;
        else
            error = true;

        tiempo = stof(tiempoString);
        if(tiempo <= 0)
            error = true;

        fuerza = stoi(fuerzaString);
        if(fuerza < 0 || fuerza > 100)
            error = true;

        if(!error) {
            newAction.accion = accion;
            newAction.fuerza = fuerza;
            newAction.tiempo = tiempo;
            accionesRobot.push_back(newAction);
        } else {
            defectuosas = defectuosas + 1;
        }

        analizadas = analizadas + 1;
    }

    return defectuosas;
} 

/* Función que abre ficheros, si no lo consigue envía una señal de error
dataFile: archivo
fileName: nombre archivo
return: true si hay errores, false si no
*/
bool openWriteFile(ofstream& dataFile, string fileName) {
    // Abrimos el fichero
    dataFile.open(fileName, ios::binary);    // Modo escritura
    if(!dataFile.is_open())
        return true;
    return false;
}

/* Función que introduce en el fichero binario el nombre del robot
return: nada
*/
void introducirNombreRob(ofstream& dataFile) {
    // Variables locales
    TRobot nuevoRobot;
    string nombre;
    int identificador = 0;

    cout << "Introduce el nombre del robot: ";
    cin >> nombre;
    cout << "Introduce el código identificador: ";
    cin >> identificador;

    for(unsigned int i = 0; i < 50; i++) {
        if(i > nombre.size())
            break;
        nuevoRobot.name[i] = nombre[i];
        nuevoRobot.identificador = identificador;
    }

    dataFile.write((const char *)&nuevoRobot, sizeof(nuevoRobot));
}

void llenarFicheroBinario(ofstream& dataFile) {
    for(unsigned int i = 0; i < accionesRobot.size(); i++) {
        TAcciones nuevasAcciones;
        nuevasAcciones.accion = accionesRobot[i].accion;
        nuevasAcciones.fuerza = accionesRobot[i].fuerza;
        nuevasAcciones.tiempo = accionesRobot[i].tiempo;
        dataFile.write((const char *)&nuevasAcciones, sizeof(nuevasAcciones));
    }
}