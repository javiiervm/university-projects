#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

typedef struct {
    char name[20];
    char surname1[20];
    char surname2[20];
    char adress[100];
    int balance;
} TOldData;

vector<TOldData> oldData;

typedef struct {
    char fullName[75];
    char adress[75];
    float balance;
} TNewData;

vector<TNewData> newData;

bool procesarArg(int argc, char *argv[], string &nameBinario, string &nameText, bool &flagL, bool &flagS);
bool leerBin(string name);
bool escribirText(string name);
bool leerText(string name);
bool escribirBin(string name);

int main(int argc, char *argv[]) {
    // Variables locales
    bool flagL = false, flagS = false, error = false;
    string nameBinario, nameText;

    // Procesar argumentos
    error = procesarArg(argc, argv, nameBinario, nameText, flagL, flagS);
    if(error) {
        cout << "ERROR: Parámetros incorrectos" << endl;
        return 1;
    }

    if(flagL) {     // Leer datos fichero binario y guardar información en fichero de texto
        error = leerBin(nameBinario);
        if(error)
            return 2;
        error = escribirText(nameText);
        if(error)
            return 3;
    } else if(flagS) {      // Leer fichero de texto y guardar información en uno binario
        error = leerText(nameText);
        if(error)
            return 4;
        error = escribirBin(nameBinario);
        if(error)
            return 5;
    }

    return 0;
}

bool procesarArg(int argc, char *argv[], string &nameBinario, string &nameText, bool &flagL, bool &flagS) {
    if(argc != 4)
        return true;

    if(strcmp(argv[1], "-l")==0){
        flagL = true;
    } else if (strcmp(argv[1], "-s")==0) {
        flagS = true;
    } else {
        return true;
    }

    nameBinario = argv[2];
    nameText = argv[3];
    
    return false;
}

bool leerBin(string name) {
    ifstream fichero;
    TOldData data;

    fichero.open(name, ios::in | ios::binary);
    if(!fichero.is_open()) {
        cout << "ERROR AL ABRIR EL FICHERO" << endl;
        return true;
    }

    while(fichero.read((char *)&data, sizeof(data)))
        oldData.push_back(data);

    fichero.close();
    return false;
}

bool escribirText(string name) {
    ofstream fichero;
    
    fichero.open(name, ios::out);
    if(!fichero.is_open()) {
        cout << "ERROR AL ABRIR EL FICHERO" << endl;
        return true;
    }

    for(unsigned int i = 0; i < oldData.size(); i++) {
        cout << oldData[i].name << "|" << oldData[i].surname1 << "|" << oldData[i].surname2 << "|" << oldData[i].adress << "|";
        if(oldData[i].balance < 0)
            cout << "NA" << endl;
        else
            cout << oldData[i].balance << endl;
    }

    fichero.close();
    return false;
}

bool leerText(string name) {
    ifstream fichero;
    string s;
    
    fichero.open(name, ios::in);
    if(!fichero.is_open()) {
        cout << "ERROR AL ABRIR EL FICHERO" << endl;
        return true;
    }

    while(getline(fichero, s)) {
        TNewData data;
        int barras = 0, j = 0;
        string balanceString;

        for(unsigned int i = 0; i < s.size(); i++) {
            if(s[i]=='|') {
                barras = barras + 1;
                if(barras<3)
                    data.fullName[i] = ' ';
            } else {
                switch (barras) {
                case 3:
                    if(j<75) {
                        data.adress[j] = s[i];
                        j = j + 1;
                    }
                    break;

                case 4:
                    balanceString.push_back(s[i]);
                    break;
                
                default:    // Case 0, Case 1, Case 2
                    data.fullName[i] = s[i];
                    break;
                }
            }
        }
        
        if(balanceString == "NA")
            data.balance = 0;
        else
            data.balance = stof(balanceString);

        newData.push_back(data);
    }

    fichero.close();
    return false;
}

bool escribirBin(string name) {
    ofstream fichero;
    
    fichero.open(name, ios::out | ios::binary);
    if(!fichero.is_open()) {
        cout << "ERROR AL ABRIR EL FICHERO" << endl;
        return true;
    }

    for(unsigned int i = 0; i < newData.size(); i++)
        fichero.write((const char *)&newData[i], sizeof(newData[i]));

    fichero.close();
    return false;
}