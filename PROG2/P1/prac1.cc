#include <iostream>
#include <vector>
#include <string.h>
#include <string>

using namespace std;

const int MAXSUBJECT=50;

// Registro para las fechas
struct Date{
    int day;
    int month;
    int year;
};

// Registro para las frases épicas
struct Phrase{
    string text;
    Date date;
    int rating;
};

// Registro para los profesores
struct Teacher{
    string name;
    string nickname;
    char subject[MAXSUBJECT];
    int rating;
    vector<Phrase> listPhrases;
};

// Registro para los cursos
struct AcademicYear{
    int id;
    vector<Teacher> listTeachers;
};

// Tipos de error posibles
enum Error{
    ERR_OPTION,
    ERR_EMPTY,
    ERR_DUPLICATED,
    ERR_NOT_EXIST,
    ERR_RATING
};

// Declaración de funciones
void addAcademicYear(vector<AcademicYear> &academicYears);
void deleteAcademicYear(vector<AcademicYear> &academicYears);
void addTeacher(vector<AcademicYear> &academicYears);
void deleteTeacher(vector<AcademicYear> &academicYears);
void showTeacher(vector<AcademicYear> &academicYears);
void addPhrase(vector<AcademicYear> &academicYears);
void summary(vector<AcademicYear> &academicYears);
bool emptyStringCheck(string text);
bool duplicatedYearCheck(vector<AcademicYear> &academicYears, int year, int length);
bool existYearCheck(vector<AcademicYear> &academicYears, int year, int length);
bool nombreRepetido (vector<AcademicYear> &academicYears, string nombreProfesor, int length);
int conversorYear ();
bool comprobadorProfesor (string &nombreProfesor);
int valoracionProfesor ();
int encontrarProfesor(vector<AcademicYear> &academicYears, string nombreProfesor, int length);
void drawRating(vector<AcademicYear> &academicYears, int ID, int selectedTeacher);
int maxYear(vector<AcademicYear> &academicYears, int limit);

// FUNCIONES INICIALES
// Estas funciones aparecían en el archivo .cc inicial que se nos proporcionó

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch(e){
        case ERR_OPTION: cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY: cout << "ERROR: empty string" << endl;
            break;
        case ERR_DUPLICATED: cout << "ERROR: duplicated value" << endl;
            break;
        case ERR_NOT_EXIST: cout << "ERROR: value does not exist" << endl;
            break;
        case ERR_RATING: cout << "ERROR: number out of range" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu(){
    cout << "1- Add academic year" << endl
        << "2- Delete academic year" << endl
        << "3- Add teacher" << endl
        << "4- Delete teacher" << endl
        << "5- Show teacher" << endl
        << "6- Add phrase" << endl
        << "7- Summary" << endl
        << "q- Quit" << endl
        << "Option: ";
}

// Función principal. Tendrás que añadir más código tuyo
int main(){
    char option;
    vector<AcademicYear> academicYears;
    
    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
                addAcademicYear(academicYears);
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
                deleteAcademicYear(academicYears);
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
                addTeacher(academicYears);
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
                deleteTeacher(academicYears);
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
                showTeacher(academicYears);
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
                addPhrase(academicYears);
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
                summary(academicYears);
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}

// FUNCIONES PRINCIPALES
// Estas son las funciones que se nos pedía realizar en el enunciado de la práctica

// Función para añadir un año académico
void addAcademicYear(vector<AcademicYear> &academicYears) {
    // Definición de variables
    bool errorDetected = false;
    int length = academicYears.size(), ID = 0;

    // Solicitar y comprobar validez del año académico
    do {
        errorDetected = false;
        
        // Introducir ID, comprobar que no es un string vacío y convertir a integer
        ID = conversorYear();
        if (ID == -1) {
            return;
        }

        // Comprobar que el ID no está repetido y, en caso de que lo esté, activar variable de error para volver a pedirlo
        errorDetected = duplicatedYearCheck(academicYears, ID, length);
    } while (errorDetected);

    // Crear nuevo AcademicYear y añadir al vector
    AcademicYear newAcademicYear;
    newAcademicYear.id = ID;
    academicYears.push_back(newAcademicYear);
}

// Función para eliminar un año académico
void deleteAcademicYear(vector<AcademicYear> &academicYears) {
    // Definición de variables
    bool errorDetected = false;
    int length = academicYears.size(), ID = 0, academicYearToDelete = 0;

    // Solicitar y comprobar validez del año académico
    do {
        errorDetected = false;
        
        // Introducir ID, comprobar que no es un string vacío y convertir a integer
        ID = conversorYear();
        if (ID == -1) {
            return;
        }

        // Comprobar que el ID existe y, en caso contrario, activar variable de error para volver a pedirlo
        errorDetected = existYearCheck(academicYears, ID, length);
    } while (errorDetected);

    // Encontrar la posición del vector en que se encuentra el año académico que se desea borrar
    for (int i = 0; i < length; i++) {
        if (academicYears[i].id == ID) {
            academicYearToDelete = i;
            i = length;
        }
    }

    // Borrar el academicYear seleccionado del vector
    academicYears.erase(academicYears.begin() + academicYearToDelete);
}

// Función para añadir un profesor
void addTeacher(vector<AcademicYear> &academicYears) {
    // Definición de variables
    bool errorDetected = false;
    int length = academicYears.size(), ID = 0, rating = 0;
    string nombreProfesor, asignatura, ratingString, nickname, subject;
    Teacher newTeacher;

    // Solicitar y comprobar validez del año académico
    do {
        errorDetected = false;
        
        // Introducir ID, comprobar que no es un string vacío y convertir a integer
        ID = conversorYear();
        if (ID == -1) {
            return;
        }

        // Comprobar que el ID existe y, en caso contrario, activar variable de error para volver a pedirlo
        errorDetected = existYearCheck(academicYears, ID, length);
    } while (errorDetected);
    
    // Si todo es correcto, comprobamos el nombre del profesor
    do {
        errorDetected = comprobadorProfesor(nombreProfesor);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        // Comprobar que el nombre no está repetido y, en caso de que lo esté, activar variable de error para volver a pedirlo
        errorDetected = nombreRepetido(academicYears, nombreProfesor, length);
    } while (errorDetected);

    newTeacher.name = nombreProfesor;

    // Introducir nickname (opcional)
    cout << "Enter nickname: ";
    getline(cin, nickname);
    newTeacher.nickname = nickname;

    // Introducir asignatura
    cout << "Enter subject: ";
    getline(cin, subject);
    errorDetected = emptyStringCheck(subject);
    if (errorDetected) {  // Comprobar si se ha activado la señal de error
        return; // Volver al menú
    }
    
    for (int i = 0; i < 50; i++) {  // Truncar nombre si supera el límite
        newTeacher.subject[i] = subject[i];
    }

    // Introducir valoración profesor
    do {
        rating = valoracionProfesor();
    } while (rating == -1);
    newTeacher.rating = rating;

    // Añadir profesor al año académico seleccionado
    for (int i = 0; i < length; i++){
        if (academicYears[i].id == ID) {
            // Inicializar vector de frases antes de agregar el nuevo profesor
            newTeacher.listPhrases = {};
            // Agregar profesor
            academicYears[i].listTeachers.push_back(newTeacher);
            i = length;
        }
    }
}

// Función para eliminar un profesor
void deleteTeacher(vector<AcademicYear> &academicYears) {
    // Definición de variables
    bool errorDetected = false;
    int length = academicYears.size(), teacherToDelete = 0;
    string nombreProfesor;

    // Comprobamos el nombre del profesor
    do {
        errorDetected = comprobadorProfesor(nombreProfesor);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        // Comprobar que el nombre del profesor existe
        teacherToDelete = encontrarProfesor(academicYears, nombreProfesor, length);
    } while (teacherToDelete == -1);

    // Borrar el profesor seleccionado
    for (int i = 0; i < length; i++) {
        if (nombreProfesor == academicYears[i].listTeachers[teacherToDelete].name) {
            academicYears[i].listTeachers.erase(academicYears[i].listTeachers.begin() + teacherToDelete);
            i = length;
        }
    }
}

// Función para mostrar datos de profesor
void showTeacher(vector<AcademicYear> &academicYears) {
    // Definición de variables
    bool errorDetected = false;
    int length = academicYears.size(), ID = 0, selectedTeacher = 0;
    string nombreProfesor;

    do {
        errorDetected = comprobadorProfesor(nombreProfesor);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        // Comprobar que el nombre del profesor existe
        selectedTeacher = encontrarProfesor(academicYears, nombreProfesor, length);
    } while (selectedTeacher == -1);

    for (int i = 0; i < length; i++) {
        if (nombreProfesor == academicYears[i].listTeachers[selectedTeacher].name) {
            ID = i;
            i = length;
        }
    }

    // Mostrar datos del profesor seleccionado
    cout << "Academic year: " << academicYears[ID].id << endl;                                      // Academic year
    cout << "Name: " << academicYears[ID].listTeachers[selectedTeacher].name << endl;               // Name
    if(academicYears[ID].listTeachers[selectedTeacher].nickname!="")
        cout << "Nickname: " << academicYears[ID].listTeachers[selectedTeacher].nickname << endl;   // Nickname
    cout << "Subject: " << academicYears[ID].listTeachers[selectedTeacher].subject << endl;         // Subject
    if(academicYears[ID].listTeachers[selectedTeacher].rating!=0) {
        cout << "Rating: ";                                                                         // Rating
        drawRating(academicYears, ID, selectedTeacher);         // Función que dibuja los asteriscos 
    }                                      
    // Frases épicas
    for (unsigned int i = 0; i < academicYears[ID].listTeachers[selectedTeacher].listPhrases.size(); i++) {
        cout << "Phrase " << i + 1;
        if (academicYears[ID].listTeachers[selectedTeacher].listPhrases[i].date.year != 0) {
            cout << " (" << academicYears[ID].listTeachers[selectedTeacher].listPhrases[i].date.year 
                << "-" << academicYears[ID].listTeachers[selectedTeacher].listPhrases[i].date.month 
                << "-" << academicYears[ID].listTeachers[selectedTeacher].listPhrases[i].date.day << ")";
        }
        if (academicYears[ID].listTeachers[selectedTeacher].listPhrases[i].rating != 0) {
            cout << " [" << academicYears[ID].listTeachers[selectedTeacher].listPhrases[i].rating << "]";
        }
        cout << ": " << academicYears[ID].listTeachers[selectedTeacher].listPhrases[i].text << endl;
    }
}

// Función para añadir una nueva frase a un profesor
void addPhrase(vector<AcademicYear> &academicYears) {
    // Variables
    bool errorDetected = false;
    string teacherName, phraseText, dateString, ratingString;
    int selectedTeacher = 0, rating = 0, length = academicYears.size();
    Date date;

    // Comprobamos el nombre del profesor
    do {
        errorDetected = comprobadorProfesor(teacherName);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        // Comprobar que el nombre del profesor existe
        selectedTeacher = encontrarProfesor(academicYears, teacherName, length);
    } while (selectedTeacher == -1);

    // Introducir frase
    cout << "Enter phrase: ";
    getline(cin, phraseText);

    // Comprobador de empty string
    if (emptyStringCheck(phraseText)) {
        return; // Return to the main menu
    }

    // Introducir string de fecha
    cout << "Enter date (year-month-day): ";
    getline(cin, dateString);

    // Convertir la fecha al formato int adecuado
    if (!dateString.empty()) {
        sscanf(dateString.c_str(), "%d-%d-%d", &date.year, &date.month, &date.day);
    } else {    // Si es un string vacío, asignar valor 0 a todos los campos de la fecha
        date.year = 0;
        date.month = 0;
        date.day = 0;
    }

    // Introducir rating de la frase
    cout << "Enter rating: ";
    getline(cin, ratingString);

    // Si no es un string vacío, convertir a integer
    if (!ratingString.empty()) {
        rating = stoi(ratingString);
        if (rating < 1 || rating > 10) {    // Comprobar si rating es un número válido
            error(ERR_RATING);
            return; // Volver al main menu
        }
    }

    // Crear un nuevo struct Phrase para almacenar la información nueva
    Phrase newPhrase;
    newPhrase.text = phraseText;
    newPhrase.date = date;
    newPhrase.rating = rating;

    // Añadir el struct al profesor correspondiente
    for (int i = 0; i < length; i++) {
        if (teacherName == academicYears[i].listTeachers[selectedTeacher].name) {
            academicYears[i].listTeachers[selectedTeacher].listPhrases.push_back(newPhrase);
            i = length;
        }
    }
}

// Función para mostrar todas las frases almacenadas
void summary(vector<AcademicYear> &academicYears) {
    int year = 0;       // Año actual que queremos mostrar
    int nonEmpty = 0;   // Variable que indica si la lista de frases está vacía (0) o no (1)

    // Iteración por los años en orden creciente
    for (unsigned i = 0; i < academicYears.size(); i++) {
        year = maxYear(academicYears, year);
        nonEmpty = 0;
        
        // Comprobar si hay profesores en el año correspondiente
        if (!academicYears[year].listTeachers.empty()) {
            
            // Iterar en el vector de profesores
            for (unsigned int j = 0; j < academicYears[year].listTeachers.size(); j++) {
                if(!academicYears[year].listTeachers[j].listPhrases.empty()) nonEmpty = 1;
            }

            // Solo mostramos la información correspondiente al año académico si al menos uno de los profesores almacenados tiene al menos una frase
            if(nonEmpty) {
                cout << "Academic year: " << academicYears[year].id << endl;
                // Iterar en el vector de profesores
                for (unsigned int j = 0; j < academicYears[year].listTeachers.size(); j++) {
                    string teacherName = academicYears[year].listTeachers[j].name;

                    // Iterar en el vector de frases
                    for (unsigned int k = 0; k < academicYears[year].listTeachers[j].listPhrases.size(); k++) {
                        cout << teacherName;
                        if (academicYears[year].listTeachers[j].listPhrases[k].rating != 0) {
                            cout << " - " << academicYears[year].listTeachers[j].listPhrases[k].rating;
                        }
                        cout << " - " << academicYears[year].listTeachers[j].listPhrases[k].text << endl;
                    }
                }
            }
        }

        year = academicYears[year].id;
    }
}

// FUNCIONES EXTRA
// Estas funciones se han declarado para facilitar la escritura del código cuando hay que repetir una misma acción muchas veces

// Comprobador de strings vacíos, en caso de detectar uno muestra el error ERR_EMPTY y devuelve un valor booleano true que activará una variable de error
bool emptyStringCheck(string text) {
    if (text == "") {
        error(ERR_EMPTY);
        return true; // Volver al menú
    }
    return false;
}

// Comprobador de años repetidos, en caso de detectar uno muestra el error ERR_DUPLICATED y vuelve a pedir el dato al usuario
bool duplicatedYearCheck(vector<AcademicYear> &academicYears, int year, int length) {
    for (int i = 0; i < length; i++) {
        if (year == academicYears[i].id) {
            error(ERR_DUPLICATED);
            return true;
        }
    }
    return false;
}

// Comprobador de que el ID existe. En caso contrario, mostrar ERR_NOT_EXIST y activar variable de error para volver a pedirlo
bool existYearCheck(vector<AcademicYear> &academicYears, int year, int length) {
    for (int i = 0; i < length; i++) {
        if (year == academicYears[i].id) {
            return false;
        }
    }
    error(ERR_NOT_EXIST);
    return true;
}

// Comprobador de que el nombre no está duplicado. En caso contrario, mostrar ERR_DUPLICATED y activar variable de error para volver a pedirlo
bool nombreRepetido (vector<AcademicYear> &academicYears, string nombreProfesor, int length) {
    for (int i = 0; i < length; i++) {
        int size = academicYears[i].listTeachers.size();
        for (int j = 0; j < size; j++) {
            if (nombreProfesor == academicYears[i].listTeachers[j].name) {
                error(ERR_DUPLICATED);
                return true;
            }
        }
    }
    return false;
}

// Esta función solicita al usuario que ingrese el año escolar, comprueba que no sea un string vacío (en tal caso vuelve al menú) y lo convierte en una variable
// de tipo int, la cual devuelve
int conversorYear () {
    // Variables locales
    bool errorDetected = false;
    char id[4];
    int year = 0;
    
    // Introducir ID y comprobar que no es un carácter vacío
    cout << "Enter academic year: ";
    cin.getline(id, 5);
    errorDetected = emptyStringCheck(id);
    if (errorDetected) {  // Comprobar si se ha activado la señal de error
        return -1; // Volver al menú
    }

    year = stoi(id);  // Convertir ID string a integer
    return year;
}

// Esta función solicita al usuario que ingrese el nombre del profesor y comprueba que no sea un string vacío (en tal caso vuelve al menú)
bool comprobadorProfesor (string &nombreProfesor) {
    // Variables locales
    bool errorDetected = false;
    string nombre;
    
    // Introducir nombre y comprobar que no es un carácter vacío
    cout << "Enter teacher name: ";
    getline(cin, nombre);
    errorDetected = emptyStringCheck(nombre);
    if (errorDetected) {  // Comprobar si se ha activado la señal de error
        return true; // Volver al menú
    }

    // Si todo es correcto, actualizamos el nombre del profesor
    nombreProfesor = nombre;

    return false;
}

// Esta función solcita la valoración del profesor, comprueba si es un string vacío o un carácter válido y convierte dicha valoración en una variable
// de tipo int, la cual devuelve
int valoracionProfesor () {
    // Variables locales
    char ratingArray[5];
    string ratingString;
    int rating = 0;
    
    // Introducir valoración y comprobar su validez
    cout << "Enter rating: ";
    cin.getline(ratingArray, 5);
    ratingString = ratingArray;
    if (ratingString == "") {     // Si es un string vacío asignamos el valor 0
        return 0;
    } else {
        rating = stoi(ratingString);    // Convertimos el string a integer
        if (rating < 1 || rating > 5) { // Comprobamos si el valor es válido, en caso contrario indicar error
            error(ERR_RATING);
            return -1;
        }
    }
    return rating;
}

// Esta función busca el nombre del profesor en el vector de años académicos, si lo encuentra devuelve la posición del vector en la que está, si no
// devuelve una variable de error
int encontrarProfesor(vector<AcademicYear> &academicYears, string nombreProfesor, int length) {
    for (int i = 0; i < length; i++) {  // Vector de años académicos
        int size = academicYears[i].listTeachers.size();
        for (int j = 0; j < size; j++) {    // Vector de profesores en el año académico
            if (nombreProfesor == academicYears[i].listTeachers[j].name) {
                return j;
            }
        }
    }
    error(ERR_NOT_EXIST);
    return -1;
}

// Esta función recibe la variable rating de un profesor y dibuja el número de asteriscos correspondiente
void drawRating(vector<AcademicYear> &academicYears, int ID, int selectedTeacher) {
    // Declaración de variables
    int rating = 0;
    rating = academicYears[ID].listTeachers[selectedTeacher].rating;

    for (int i = 0; i <= rating; i++) {
        if(i)cout << "*";
    }
    cout << endl;
}

// Esta función recibe el vector de años académicos y una variable int que contiene el año más alto encontrado hasta el momento
int maxYear(vector<AcademicYear> &academicYears, int limit) {
    int max = 0;
    // Si el límite es distinto de cero significa que ya se ha encontrado un año antes, con lo cual se buscará el año más alto inmediatamente después de ese
    if(limit) {
        for (unsigned int i = 0; i < academicYears.size(); i++) {
            if(academicYears[i].id > max && academicYears[i].id < limit) {
                max = academicYears[i].id;
            }
        }
    // Si el límite es cero no hay que realizar ninguna comprobación adicional, el programa buscará el año más alto
    } else {
        for (unsigned int i = 0; i < academicYears.size(); i++) {
            if(academicYears[i].id > max) {
                max = academicYears[i].id;
            }
        }
    }
    // Por último, la función devuelve una variable correspondiente a la posición del vector donde se encuentra el año más alto
    for (unsigned int i = 0; i < academicYears.size(); i++) {
        if(academicYears[i].id == max) {
            max = i;
        }
    }
    return max;
}