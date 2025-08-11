
// LIBRERÍAS

#include <iostream>     // Proporciona clases de flujo de entrada y salida para leer y escribir datos
#include <fstream>      // Ofrece clases de flujo de archivo para leer y escribir archivos
#include <vector>       // Proporciona un contenedor similar a un array dinámico que puede crecer o disminuir en tamaño
#include <cctype>       // Contiene funciones para la clasificación de caracteres (por ejemplo, isdigit, isalpha)
#include <string.h>     // Proporciona funciones para la manipulación de cadenas (por ejemplo, strcpy, strlen)

using namespace std;    // Permite acceder a clases de flujo de entrada/salida (cin, cout, cerr, clog), contenedores como vector, string, funciones matemáticas
                        // y más sin tener que escribir std:: delante de cada una

// CONSTANTES Y REGISTROS

const int KMAXNAME = 50;        // Máximo de caracteres del nombre de un profesor
const int KMAXPASSWORD = 5;     // Máximo de caracteres de la contraseña de un profesor

// Registro para las preguntas
struct Question{
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// Registro para los profesores
struct Teacher{
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// Registro para la base de datos
struct Database{
    unsigned int nextId;
    vector<Question> questions;
    vector<Teacher> teachers;
};

// Tipos de errores posibles
enum Error {
    ERR_OPTION,
    ERR_EMPTY,
    ERR_UNIT,
    ERR_CHAR,
    ERR_FILE,
    ERR_NAME,
    ERR_DUPLICATED,
    ERR_PASSWORD,
    ERR_NO_QUESTIONS,
    ERR_ID,
    ERR_ARGS
};

// DECLARACIÓN DE FUNCIONES AUXILIARES

// Funciones solicitadas por el enunciado de la práctica
bool ProcesarArgumentos(int argc, char *argv[], string &nombreFichero, bool &cargarPreguntas, bool &mostrarEstadisticas);
void loadTeachers(Database& data);
void addQuestion(Database& data);
void batchAddQuestion(Database& data, string& fileName, bool cargarPreguntas);
void deleteQuestion(Database& data);
void addTeacher(Database& data);
void addAnswers(Database& data);
void viewAnswers(Database& data);
void viewStatistics(Database& data);
void exportQuestions(Database& data);
void exportTeachers(Database& data);

// Funciones auxiliares ejercicio 7.2
bool comprobadorFormato(Database& data, string currentLine, int& addedQuestions, int totalQuestions, int& emptyLines);
bool comprobadorDeBarras(string currentLine, int totalQuestions);
bool comprobadorDeUnidad(string currentLine, int totalQuestions);
bool comprobadorDePregunta(string currentLine, int totalQuestions);
bool comprobadorDeRespuesta(string currentLine, int totalQuestions);
void guardarPregunta(Database& data, string currentLine, int& addedQuestions);

// Funciones auxiliares ejercicio 7.4
bool comprobadorProfesor(string &nombreProfesor);
bool alphabetChecker(string nombreProfesor);
bool comprobadorValidezNombreProfesor(string &nombreProfesor);
bool nombreProfeRepetido(Database data, string nombreProfesor);
bool digitChecker(string password);
bool comprobadorPassword(string &password);
void encryption(string& password);

// Funciones auxiliares ejercicio 7.5
int obtenerPregunta(Database& data, string& identifier);
bool addRespuesta(Database& data, unsigned int position, unsigned int& contestadas, unsigned int& preguntasSinResponder);
int contestarPreguntas(Database& data);

// Funciones auxiliares ejercicio 7.8
bool openFileWriting(ofstream& dataFile, string fileName);

// Funciones extra utilizadas varias veces a lo largo del programa
bool emptyStringCheck(string text);
bool intervalChecker(int min, int max, int value);
bool unitChecker(int& unit);
bool verticalBarCheck(string text);
bool fileOpenedCheck(ifstream& dataFile, string fileName);
int questionIDChecker(Database data);

// FUNCIONES INICIALES
// Estas funciones aparecían en el archivo .cc inicial que se nos proporcionó

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e){
    switch (e){
        case ERR_OPTION:
            cout << "ERROR: wrong option" << endl;
            break;
        case ERR_EMPTY:
            cout << "ERROR: empty string" << endl;
            break;
        case ERR_UNIT:
            cout << "ERROR: wrong unit" << endl;
            break;
        case ERR_CHAR:
            cout << "ERROR: wrong char" << endl;
            break;
        case ERR_FILE:
            cout << "ERROR: cannot open file" << endl;
            break;
        case ERR_NAME:
            cout << "ERROR: wrong teacher name" << endl;
            break;
        case ERR_DUPLICATED:
            cout << "ERROR: duplicated name" << endl;
            break;
        case ERR_PASSWORD:
            cout << "ERROR: wrong password" << endl;
            break;      
        case ERR_NO_QUESTIONS:
            cout << "ERROR: no pending questions" << endl;
            break;
        case ERR_ID:
            cout << "ERROR: wrong id" << endl;
            break;
        case ERR_ARGS:
            cout << "ERROR: wrong arguments" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu() {
    cout << "1- Add question" << endl
        << "2- Batch add questions" << endl
        << "3- Delete question" << endl
        << "4- Add teacher" << endl
        << "5- Add answers" << endl
        << "6- View answers" << endl
        << "7- View statistics" << endl
        << "8- Export questions" << endl
        << "q- Quit" << endl
        << "Option: ";
}

/* Función principal
argc: número de argumentos que recibe
argv: array con los argumentos recibidos
return: 0
*/
int main(int argc, char *argv[]) {
    // Variables locales
    Database data;                      // Base de datos
    data.nextId = 1;                    // ID de pregunta
    char option;                        // Opción del menú
    string nombreFichero;               // Nombre del fichero en el que estén almacenadas las preguntas (para la función -f)
    bool cargarPreguntas = false;       // Señal para cargar preguntas de fichero automáticamente al iniciar el programa
    bool mostrarEstadisticas = false;   // Señal para mostrar estadísticas automáticamente al iniciar el programa
    bool errorDetected = false;         // Señal que detendrá la ejecución del programa cuando se active

    loadTeachers(data); // Cargar datos del fichero teachers.bin nada más iniciar el programa

    // Comprobar parámetros de entrada
    if(ProcesarArgumentos(argc, argv, nombreFichero, cargarPreguntas, mostrarEstadisticas)) {
        if(cargarPreguntas) {       // Importar preguntas del fichero de texto
            batchAddQuestion(data, nombreFichero, cargarPreguntas);
        }
        if(mostrarEstadisticas) {
            viewStatistics(data);   // Mostrar estadísticas
            errorDetected = true;   // Activamos la señal de error para que el programa se detenga y no muestre el menú
        }
    } else {
        errorDetected = true;       // Activar señal de error si el formato de los argumentos no es válido
        error(ERR_ARGS);
    }
    
    if(!errorDetected) {    // Solo ejecutamos el programa si no hay errores con los argumentos introducidos
        do {
            showMenu();     // Llamar a la función showMenu para mostra el menú, y comprobar elección del usuario
            cin >> option;
            cin.get();
            
            switch(option){
                case '1': // Llamar a la función "addQuestion" para añadir una nueva pregunta
                    addQuestion(data);
                    break;
                case '2': // Llamar a la función "batchAddQuestion" para añadir preguntas desde fichero
                    batchAddQuestion(data, nombreFichero, cargarPreguntas);
                    break;
                case '3': // Llamar a la función "deleteQuestion" para eliminar una pregunta
                    deleteQuestion(data);
                    break;
                case '4': // Llamar a la función "addTeacher" para añadir un nuevo profesor
                    addTeacher(data);
                    break;
                case '5': // Llamar a la función "addAnswers" para añadir respuestas a las preguntas
                    addAnswers(data);
                    break;
                case '6': // Llamar a la función "viewAnswers" para mostrar las preguntas con sus respuestas
                    viewAnswers(data);
                    break;
                case '7': // Llamar a la función "viewStatistics" para ver las estadísticas de las preguntas
                    viewStatistics(data);
                    break;
                case '8': // Llamar a la función "exportQuestions" para guardar las preguntas en fichero
                    exportQuestions(data);
                    break;
                case 'q': // Salir del programa guardando los profesores en fichero
                    exportTeachers(data);
                    break;
                default: error(ERR_OPTION);
            }
        } while(option != 'q');
    }
    return 0;
}

// FUNCIONES PRINCIPALES
// Estas son las funciones que se nos pedía realizar en el enunciado de la práctica

/* Comprueba los argumentos de entrada y extrae su valor si son correctos
argc: número de argumentos que recibe
argv: array con los argumentos recibidos
nombreFichero: nombre del fichero de texto que guarda la información de las preguntas
cargarPreguntas: true para indicar que el programa debe cargar las preguntas del fichero, false para indicar que no debe hacerlo
mostrarEstadisticas: true para indicar que el programa debe cargar las estadísticas, false para indicar que no debe hacerlo
return: true para indicar que el formato de los argumentos es correcto, false para indicar que no
*/
bool ProcesarArgumentos(int argc, char *argv[], string &nombreFichero, bool &cargarPreguntas, bool &mostrarEstadisticas) {
    // Comprobamos que no haya más de 4 argumentos (nombre del programa, -f, nombre del fichero, -s)
    if(argc > 4) {
        return false;
    } else {
        // Iteramos sobre los argumentos mientras no haya ningún error
        for(int i = 1; i < argc; i++) {
            // Verificamos si el argumento actual es -f
            if(strcmp(argv[i], "-f") == 0) {
                if(i + 1 < argc) {
                    cargarPreguntas = true;
                    nombreFichero = argv[i + 1];
                    i++; // Hemos consultado el argumento que sigue a -f, así que incrementamos i para no volver a consultarlo en la siguiente iteración
                } else {
                    return false;
                }
            // Verificamos si el argumento actual es -s
            } else if(strcmp(argv[i], "-s") == 0) {
                mostrarEstadisticas = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

/* Función para cargar datos de profesores del fichero binario
data: Base de datos
return: nada
*/
void loadTeachers(Database& data) {
    // Abrir el archivo binario para lectura
    ifstream dataFile("teachers.bin", ios::binary);

    // Crear una variable de tipo Teacher para almacenar los datos leídos del fichero binario
    Teacher profesor;

    // Verificar si el archivo se abrió correctamente
    if(dataFile.is_open()) {
        // Leer cada estructura Teacher del archivo y almacenarla en la base de datos
        while(dataFile.read(reinterpret_cast<char *>(&profesor), sizeof(profesor))) {
            data.teachers.push_back(profesor);
        }

        // Cerrar el archivo después de la lectura
        dataFile.close();
    }
}

/* Función para añdir una nueva pregunta al programa
data: Base de datos
return: nada
*/
void addQuestion(Database& data) {
    // Declaración de variables
    bool errorDetected = false;
    int unit = 0;
    string questionString;

    // Solicitar y comprobar validez de la unidad
    do {
        errorDetected = false;
        
        // Introducir unidad, comprobar que no es un string vacío y convertir a integer
        errorDetected = unitChecker(unit);
        if(errorDetected) {
            return;
        }

        // Comprobar que la unidad tiene un valor entre 1 y 5
        errorDetected = intervalChecker(1, 5, unit);
    } while (errorDetected);

    // Solicitar y comprobar texto de la pregunta
    do {
        errorDetected = false;
        
        // Introducir pregunta
        cout << "Enter question: ";
        getline(cin, questionString);
        
        // Comprobar que no es un string vacío
        errorDetected = emptyStringCheck(questionString);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        // Comprobar que el texto no contenga el carácter "|"
        errorDetected = verticalBarCheck(questionString);
    } while (errorDetected);

    // Crear una nueva pregunta con el campo answer vacío
    Question newQuestion;
    newQuestion.id = data.nextId;
    data.nextId = data.nextId + 1;  // Incrementar el contador de next ID
    newQuestion.unit = unit;
    newQuestion.question = questionString;
    data.questions.push_back(newQuestion);
}

/* Función para cargar preguntas desde un text file
data: Base de datos
fileName: Nombre del fichero de texto que contiene las preguntas
cargarPreguntas: Señal que indica si hay que pedir o no el nombre del fichero de texto
return: nada
*/
void batchAddQuestion(Database& data, string& fileName, bool cargarPreguntas) {
    // Declaración de variables
    bool errorDetected = false, emptyFile = true;
    int totalQuestions = 0, addedQuestions = 0, emptyLines = 0;
    string currentLine;
    ifstream dataFile;

    // Solicitar y comprobar validez del nombre del fichero
    do {
        if(!cargarPreguntas) {
            errorDetected = false;
            
            // Introducir nombre del fichero
            cout << "Enter filename: ";
            getline(cin, fileName);
            
            // Comprobar que no es un string vacío
            errorDetected = emptyStringCheck(fileName);
            if (errorDetected) {  // Comprobar si se ha activado la señal de error
                return; // Volver al menú
            }
        }

        // Abrir fichero y comprobar que se ha conseguido con éxito
        errorDetected = fileOpenedCheck(dataFile, fileName);
    } while (errorDetected);

    errorDetected = false;

    // COMPROBACIONES
    while (getline(dataFile, currentLine)) {
        // Declaración e inicialización de variables
        string pregunta, respuesta, unidadString;
        errorDetected = false;

        // Actualizar el número de preguntas comprobadas
        totalQuestions = totalQuestions + 1;

        // Comprobar que el formato de la línea que se está comprobando sea el adecuado
        emptyFile = comprobadorFormato(data, currentLine, addedQuestions, totalQuestions, emptyLines);
    }

    if(!emptyFile) {
        cout << "Summary: " << addedQuestions << "/" << totalQuestions - emptyLines << " questions added" << endl;
    } else {
        cout << "Summary: 0/0 questions added" << endl;
    }

    // Por último, cerramos el fichero cuando dejamos de trabajar con él
    dataFile.close();
}

/* Función para eliminar una pregunta del programa
data: Base de datos
return: nada
*/
void deleteQuestion(Database& data) {
    // Delaración de variables
    int questionToDelete = 0;

    do {
        questionToDelete = questionIDChecker(data);
        if(questionToDelete==-1)
            return;
        else if(questionToDelete==-2)
            error(ERR_ID);
    } while(questionToDelete<0);

    data.questions.erase(data.questions.begin() + questionToDelete);
}

/* Función para añadir un profesor
data: Base de datos
return: nada
*/
void addTeacher(Database& data) {
    // Variables locales
    Teacher newTeacher;
    bool errorDetected = false;
    string teacherName, password;

    // Comprobar la validez del nombre del profesor
    do {
        errorDetected = false;
        errorDetected = comprobadorProfesor(teacherName);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        errorDetected = comprobadorValidezNombreProfesor(teacherName);

        // Si el nombre es válido, comprobar que no esté duplicado
        if(!errorDetected)
            errorDetected = nombreProfeRepetido(data, teacherName);
    } while(errorDetected);

    // Cear contraseña, comprobar su validez y encriptarla
    if(comprobadorPassword(password))return;

    // Guardar datos del profesor
    newTeacher.answered = 0;
    for(int i = 0; i < KMAXNAME; i++) {
        newTeacher.name[i] = teacherName[i];
    }
    for(int i = 0; i < KMAXPASSWORD; i++) {
        newTeacher.password[i] = password[i];
    }
    data.teachers.push_back(newTeacher);
}

/* Función para añadir respuestas
data: Base de datos
return: nada
*/
void addAnswers(Database& data) {
    // Variables locales
    bool errorDetected = false;
    int profesor = 0; // Variable para almacenar la posición de la base de datos en la que se encuentra el profesor
    int contestadas = 0; // Variable para almacenar el número de preguntas contestadas por el profesor
    string teacherName, password, identifier, answer;

    // Comprobar nombre del profesor
    do {
        errorDetected = comprobadorProfesor(teacherName);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        // Si el nombre es válido, comprobar que existe en la base de datos
        if(!errorDetected) {
            errorDetected = true;
            for (unsigned int i = 0; i < data.teachers.size(); i++) {
                if(data.teachers[i].name == teacherName) {
                    errorDetected = false;
                    profesor = i;
                }
            }
            if(errorDetected)
                error(ERR_NAME);
        }
    } while(errorDetected);

    // Comprobar contraseña
    do {
        cout << "Enter password: ";
        getline(cin, password);

        // Comprobar que no se haya introducido un string vacío
        errorDetected = emptyStringCheck(password);
        if(errorDetected)return;

        // Desencriptar y comprobar que se corresponde
        encryption(password);
        if(data.teachers[profesor].password != password) {
            error(ERR_PASSWORD);
            errorDetected = true;
        }
    } while(errorDetected);

    // ¡Sesión iniciada con éxito!

    // Si todo es correcto, permitimos que el profesor empiece a contestar preguntas. Para eso, llamamos a una función auxiliar
    contestadas = contestarPreguntas(data);

    // Actualizamos los datos de preguntas contestadas del profesor
    data.teachers[profesor].answered = data.teachers[profesor].answered + contestadas;
}

/* Función para ver todas las preguntas que han sido contestadas
data: Base de datos
return: nada
*/
void viewAnswers(Database& data) {
    for(unsigned int i = 0; i < data.questions.size(); i++) {
        if(data.questions[i].answer != "") {
            cout << data.questions[i].id << ". (" << data.questions[i].unit << ") " << data.questions[i].question << ": " << data.questions[i].answer << endl;
        }
    }
}

/* Función para ver las estadísticas de preguntas contestadas
data: Base de datos
return: nada
*/
void viewStatistics(Database& data) {
    // Variables locales
    int totalPreguntas = 0, preguntasContestadas = 0;

    // Recorrer el vector preguntas y actualizar las variables de datos
    for(unsigned int i = 0; i < data.questions.size(); i++) {
        totalPreguntas = totalPreguntas + 1;
        if(data.questions[i].answer != "") {
            preguntasContestadas = preguntasContestadas + 1;
        }
    }

    // Mostrar datos
    cout << "Total number of questions: " << totalPreguntas << endl << "Number of questions answered: " << preguntasContestadas << endl;

    // Recorrer vector de profesores y mostrar datos
    for(unsigned int i = 0; i < data.teachers.size(); i++) {
        cout << data.teachers[i].name << ": " << data.teachers[i].answered << endl;
    }
}

/* Función para exportar preguntas a un fichero de texto
data: Base de datos
return: nada
*/
void exportQuestions(Database& data) {
    // Declaración de variables
    bool errorDetected = false;
    string fileName;
    ofstream dataFile;

    // Solicitar y comprobar validez del nombre del fichero
    do {
        errorDetected = false;
        
        // Introducir nombre del fichero
        cout << "Enter filename: ";
        getline(cin, fileName);
        
        // Comprobar que no es un string vacío
        errorDetected = emptyStringCheck(fileName);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return; // Volver al menú
        }

        // Abrir fichero y comprobar que se ha conseguido con éxito
        errorDetected = openFileWriting(dataFile, fileName);
    } while (errorDetected);

    for(unsigned int i = 0; i < data.questions.size(); i++) {
        if(data.questions[i].answer == "")
            dataFile << data.questions[i].unit << "|" << data.questions[i].question << endl;
        else
            dataFile << data.questions[i].unit << "|" << data.questions[i].question << "|" << data.questions[i].answer << endl;
    }

    // Por último, cerramos el fichero cuando dejamos de trabajar con él
    dataFile.close();
}

/* Función para exportar profesores a un fichero binario
data: Base de datos
return: nada
*/
void exportTeachers(Database& data) {
    // Abrir el archivo binario para escritura
    ofstream dataFile("teachers.bin", ios::binary);

    // Verificar si el archivo se abrió correctamente
    if(dataFile.is_open()) {
        // Escribir cada elemento del vector en el archivo
        for (unsigned int i = 0; i < data.teachers.size(); i++) {
            dataFile.write(reinterpret_cast<const char *>(&data.teachers[i]), sizeof(data.teachers[i]));
        }

        // Cerrar el archivo después de escribir
        dataFile.close();
    } else {
        // Mostrar un mensaje de error si no se puede abrir el archivo
        error(ERR_FILE);
        return;
    }
}

// FUNCIONES AUXILIARES APARTADO 7.2
// Estas funciones han sido declaradas para simplificar las comprobaciones de la función batchAddQuestion y facilitar su comprensión y escritura

/* Función para comprobar si el formato de la pregunta en la línea actual del fichero de texto es válido
data: Base de datos
currentLine: Línea del fichero que se está comprobando
addedQuestions: Número de preguntas con el formato correcto que fueron añadidas a la base de datos
totalQuestions: Número de preguntas comprobadas
emptyLines: Número de líneas vacías encontradas en el fichero
return: true si el fichero está vacío, false si no
*/
bool comprobadorFormato(Database& data, string currentLine, int& addedQuestions, int totalQuestions, int& emptyLines) {
    // Variables locales
    bool emptyFile = true;
    bool errorDetected = false;

    // Si la línea del fichero está vacía la ignoramos y pasamos a la siguiente
    if(currentLine!="") {

        emptyFile = false;

        // Comprobación del número de "|"
        errorDetected = comprobadorDeBarras(currentLine, totalQuestions);

        if(!errorDetected) {
            // Comprobación del valor de unit
            errorDetected = comprobadorDeUnidad(currentLine, totalQuestions);

            if(!errorDetected) {
                // Comprobar pregunta
                errorDetected = comprobadorDePregunta(currentLine, totalQuestions);

                    if(!errorDetected) {
                        // Comprobar respuesta
                        errorDetected = comprobadorDeRespuesta(currentLine, totalQuestions);
                    }
                }
            }

            if(!errorDetected) {
                guardarPregunta(data, currentLine, addedQuestions); // Guardar pregunta en database
            }
    } else {
        emptyLines = emptyLines + 1;
    }
    return emptyFile;
}

/* Función que comprueba que haya al menos un "|" pero no más de dos en cada línea del fichero. En caso contrario activa un error.
currentLine: Contenido de la línea actual del fichero de texto
linea: Número de línea actual del fichero de texto
return: true si hay un error, false si no
*/
bool comprobadorDeBarras(string currentLine, int linea) {
    int numBars = 0;
    for (unsigned int i = 0; i < currentLine.size(); i++) {
        if(currentLine[i] == '|')numBars=numBars+1;
    }
        if(numBars<1||numBars>2) {
        cout << "Error line " << linea << endl;
        return true;
    }
    return false;
}

/* Función que comprueba que la unidad no sea un carácter vacío y que esté entre 1 y 5. En caso contrario activa un error.
currentLine: Contenido de la línea actual del fichero de texto
linea: Número de línea actual del fichero de texto
return: true si hay un error, false si no
*/
bool comprobadorDeUnidad(string currentLine, int linea) {
    // Variables locales
    string unidadString;
    int unidad = 0;

    // Añadir al string de unidad todo lo que haya antes de la primera barra
    for(unsigned int i = 0; i < currentLine.size(); i++) {
        if(currentLine[i]!='|')
            unidadString.push_back(currentLine[i]);
        else
            break;
    }

    // Comprobaciones de que la unidad sea válida
    if(unidadString == "") {
        cout << "Error line " << linea << endl;
        return true;
    } else {
        unidad = atoi(unidadString.c_str());
        if (unidad < 1 || unidad > 5) {
            cout << "Error line " << linea << endl;
            return true;
        }
    }
    return false;
}

/* Función que comprueba que el campo pregunta no esté vacío. En caso contrario activa un error.
currentLine: Contenido de la línea actual del fichero de texto
linea: Número de línea actual del fichero de texto
return: true si hay un error, false si no
*/
bool comprobadorDePregunta(string currentLine, int linea) {
    for(unsigned int i = 0; i < currentLine.size(); i++) {
        if(i + 1 < currentLine.size() && currentLine[i]==currentLine[i+1] && currentLine[i]=='|') {     // El programa recorre la línea buscando dos barras
                                                                                                        // juntas, cosa que indicaría que solo hay texto en 
                                                                                                        // el campo unidad y el campo respuesta
            cout << "Error line " << linea << endl;
            return true;
        }
    }
    return false;
}

/* Función que comprueba si el campo respuesta está vacío, de ser así activa un error para cambiar el formato
currentLine: Contenido de la línea actual del fichero de texto
linea: Número de línea actual del fichero de texto
return: true si hay un error, false si no
*/
bool comprobadorDeRespuesta(string currentLine, int linea) {
    // Si hay una barra en posición final activar señal de error, ya que significa que el campo respuesta está en blanco
    if(currentLine[currentLine.size() - 1] == '|') {
        cout << "Error line " << linea << endl;
        return true;
    }
    return false;
}

/* Función que guarda cada pregunta en la base de datos
data: Base de datos
currentLine: Contenido de la línea actual del fichero de texto
addedQuestions: Número de preguntas que han sido añadidad
return: nada
*/
void guardarPregunta(Database& data, string currentLine, int& addedQuestions) {
    // Variables locales
    Question newQuestion;
    string unidadString, pregunta, respuesta;
    int unidad = 0, contadorBarras = 0;

    // Añadir al string de unidad todo lo que haya antes de la primera barra
    for(unsigned int i = 0; i < currentLine.size(); i++) {
        if(currentLine[i]!='|')
            unidadString.push_back(currentLine[i]);
        else
            break;
    }
    unidad = atoi(unidadString.c_str());

    for(unsigned int i = 0; i < currentLine.size(); i++) {
        if(currentLine[i]!='|') {
            switch (contadorBarras) {
            case 0:
                unidadString.push_back(currentLine[i]);
                break;
            case 1:
                pregunta.push_back(currentLine[i]);
                break;
            case 2:
                respuesta.push_back(currentLine[i]);
                break;
            }
        } else {
            contadorBarras = contadorBarras + 1;
        }
    }

    newQuestion.id = data.nextId;
    data.nextId = data.nextId + 1;  // Incrementar el contador de next ID
    newQuestion.unit = unidad;
    newQuestion.question = pregunta;
    newQuestion.answer = respuesta;
    data.questions.push_back(newQuestion);

    addedQuestions = addedQuestions + 1;
}

// FUNCIONES AUXILIARES APARTADO 7.4
// Estas funciones han sido declaradas para simplificar las comprobaciones de la función addTeacher y facilitar su comprensión y escritura

/* Esta función solicita al usuario que ingrese el nombre del profesor y comprueba que no sea un string vacío (en tal caso vuelve al menú)
nombreProfesor: string que contiene el nombre del profesor
return: true si hay un error, false si no
*/
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

/* Función que comprueba la validez del formato del nombre del profesor llamando a las funciones correspondientes
nombreProfesor: string que contiene el nombre del profesor
return: true si hay un error, false si no
*/
bool comprobadorValidezNombreProfesor(string &nombreProfesor) {
    // Variables
    bool errorDetected = false;

    // Comprobar validez de los caracteres
    errorDetected = alphabetChecker(nombreProfesor);
    if(errorDetected) {
        error(ERR_NAME);
        return true;
    }

    // Eliminar espacio en blanco al principio y al final, si lo hay
    if(nombreProfesor[0]==' ')
        nombreProfesor.erase(nombreProfesor.begin());
    if(nombreProfesor[nombreProfesor.size() - 1]==' ')
        nombreProfesor.erase(nombreProfesor.begin() + nombreProfesor.size() - 1);

    // Comprobar que el tamaño del string sea el adecuado
    if(nombreProfesor.size() < 3 || nombreProfesor.size() > KMAXNAME - 1) {
        error(ERR_NAME);
        return true;
    }
    
    return false;
}

/* Función que recorre el string comprobando que no contiene nada que no sean caracteres alfabéticos o espacios en blanco
nombreProfesor: string que contiene el nombre del profesor
return: true si hay un error, false si no
*/
bool alphabetChecker(string nombreProfesor) {
    // Declaración de variables
    int check = 0;  // Esta variable funciona al revés. 1 = correcto, 0 = incorrecto

    // Recorrer el string comprobando si los caracteres son válidos
    for (unsigned int i = 0; i < nombreProfesor.size(); i++) {
        check = isalpha(nombreProfesor[i]);
        if(!check && nombreProfesor[i] != ' ')return true;
    }

    return false;
}

/* Función que recorre el string de profesores comprobando que no exista uno igual al que queremos introducir
data: Base de datos
nombreProfesor: string que contiene el nombre del profesor
return: true si hay un error, false si no
*/
bool nombreProfeRepetido(Database data, string nombreProfesor) {
    for (unsigned int i = 0; i < data.teachers.size(); i++) {
        if(data.teachers[i].name == nombreProfesor) {
            error(ERR_DUPLICATED);
            return true;
        }
    }
    return false;
}

/* Función que recorre el string comprobando que no contiene nada que no sean caracteres numéricos
password: string que contiene la contraseña del profesor
return: true si hay un error, false si no
*/
bool digitChecker(string password) {
    // Declaración de variables
    int check = 0;  // Esta variable funciona al revés. 1 = correcto, 0 = incorrecto

    // Recorrer el string comprobando si los caracteres son válidos
    for (unsigned int i = 0; i < password.size(); i++) {
        check = isdigit(password[i]);
        if(!check) {
            error(ERR_PASSWORD);
            return true;
        }
    }

    return false;
}

/* Esta función solicita al usuario la contraseña y comprueba que su formato sea válido
password: string que contiene la contraseña del profesor
return: true si hay un error, false si no
*/
bool comprobadorPassword(string &password) {
    // Variables locales
    bool errorDetected = false;
    string newPassword;
    
    // Introducir nombre y comprobar que no es un carácter vacío
    do {
        errorDetected = false;
        cout << "Enter password: ";
        getline(cin, newPassword);
        errorDetected = emptyStringCheck(newPassword);
        if (errorDetected) {  // Comprobar si se ha activado la señal de error
            return true; // Volver al menú
        }

        // Comprobar que la contraseña está hecha a base de caracteres numéricos y que su longitud es adecuada
        if(newPassword.size() == KMAXPASSWORD - 1) {
            errorDetected = digitChecker(newPassword);
        } else {
            errorDetected = true;
            error(ERR_PASSWORD);
        }
    } while (errorDetected);

    // Encriptar contraseña siguiendo el código establecido
    encryption(newPassword);

    // Devolver contraseña
    password = newPassword;
    return false;
}

/* Función que encripta la contraseña del profesor en función de la tabla indicada en el enunciado
password: string que contiene la contraseña del profesor
return: nada
*/
void encryption(string& password) {
    // string encription;
    for(unsigned int i = 0; i < password.size(); i++) {
        switch (password[i]) {
        case '0':
            password[i] = 'T';
            break;
        case '1':
            password[i] = 'R';
            break;
        case '2':
            password[i] = 'W';
            break;
        case '3':
            password[i] = 'A';
            break;
        case '4':
            password[i] = 'G';
            break;
        case '5':
            password[i] = 'M';
            break;
        case '6':
            password[i] = 'Y';
            break;
        case '7':
            password[i] = 'F';
            break;
        case '8':
            password[i] = 'P';
            break;
        case '9':
            password[i] = 'D';
            break;
        }
    }
}

// FUNCIONES AUXILIARES APARTADO 7.5
// Estas funciones han sido declaradas para simplificar las comprobaciones de la función addAnswers y facilitar su comprensión y escritura

/* Función que solicita al profesor el id de la pregunta que quiere contestar y busca su posición en la base de datos
data: Base de datos
identifier: string introducido por el usuario que puede contener el id de pregunta o la señal de salida "b"
return: -1 si ha habido un error, posición de la pregunta que se busca en caso de que todo esté correcto
*/
int obtenerPregunta(Database& data, string& identifier) {
    // Variables locales
    unsigned int id = 0, position = 0;
    bool errorDetected = false;

    // Pedir y comprobar identificador de pregunta
    do {
        errorDetected = false;
        
        cout << "Enter question id: ";
        getline(cin, identifier);

        // Comprobar que no se haya introducido un string vacío
        if(emptyStringCheck(identifier))
            return -1;

        // En caso de que no se haya introducido "b" convertimos a int el string
        if(identifier!="b") {

            id = atoi(identifier.c_str());

            if(id > 0) {    // Si id > 0 entonces buscamos la posición de la pregunta con ese identificador (si existe)
                errorDetected = true;

                // Buscar la pregunta con ese identificador
                for(unsigned int i = 0; i < data.questions.size(); i++) {
                    if(id == data.questions[i].id && data.questions[i].answer=="") {
                        errorDetected = false;
                        position = i;
                        break;
                    }
                }
                if(errorDetected)error(ERR_ID);
            } else {    // Si id <= 0 activamos la señal de error
                errorDetected = true;
                //error(ERR_ID);
            }
        } else {
            break;
        }
    } while(errorDetected);
    return position;
}

/* Función que guarda en la base de datos la respuesta del profesor a la pregunta seleccionada y actualiza los datos de preguntas contestadas
data: Base de datos
position: posición de la pregunta que se quiere contestar en la base de datos
contestadas: número de preguntas contestadas con éxito
preguntasSinResponer: número de preguntas que no se han contestado
return: true si ha habido algún error, false si todo es correcto
*/
bool addRespuesta(Database& data, unsigned int position, unsigned int& contestadas, unsigned int& preguntasSinResponder) {
    // Variables locales
    bool errorDetected = false;
    string answer;

    // Pedir y comprobar validez de la respuesta
    do {
        errorDetected = false;

        cout << "Enter answer: ";
        getline(cin, answer);

        // Comprobar que no se haya introducido un string vacío
        errorDetected = emptyStringCheck(answer);
        if(errorDetected)
            return true;

        // Comprobar que no se haya introducido el caracter '|'
        for(unsigned int i = 0; i < answer.size(); i++) {
            if(answer[i]=='|') {
                errorDetected = true;
                error(ERR_CHAR);
                break;
            }
        }
    } while(errorDetected);

    // Si todo está correcto añadir respuesta a la base de datos y actualizar el número de preguntas sin contestar y de preguntas contestadas
    data.questions[position].answer = answer;
    contestadas = contestadas + 1;
    preguntasSinResponder = 0;

    for(unsigned int i = 0; i < data.questions.size(); i++) {   // Actualizar número de preguntas sin responder
        if(data.questions[i].answer == "") {
            preguntasSinResponder = preguntasSinResponder + 1;
        }
    }
    return false;
}

/* Función que permite a un profesor contestar preguntas de la base de datos
data: Base de datos
return: número de preguntas contestadas
*/
int contestarPreguntas(Database& data) {
    // Variables locales
    unsigned int preguntasSinResponder = 0, contestadas = 0;
    int finalizar = 0;
    string ending;

    // Contestar preguntas
    do {    
        // Variables locales que se reinician en cada iteración del bucle do-while
        string identifier, answer;
        unsigned int position = 0;
        bool errorDetected = false;

        preguntasSinResponder = 0;
        for(unsigned int i = 0; i < data.questions.size(); i++) {
            if(data.questions[i].answer == "")
                preguntasSinResponder = preguntasSinResponder + 1;
        }

        // Mostrar preguntas sin responder, en caso de que no haya muestra un error
        if(preguntasSinResponder == 0) {
            error(ERR_NO_QUESTIONS);
            return contestadas;
        } else {
            for(unsigned int i = 0; i < data.questions.size(); i++) {
                if(data.questions[i].answer == "") {
                    cout << data.questions[i].id << ". (" << data.questions[i].unit << ") " << data.questions[i].question << endl;
                }
            }
        }

        // Llamamos a la función que busca la posición de la pregunta que el profesor decide contestar
        position = obtenerPregunta(data, identifier);
        if((int)position == -1)  // Si la posición es -1 significa que ha habido algún error
            return contestadas;

        // Si no ha habido algún error y no se ha introducido "b" en el identificador, llamamos a la función que permite responder la pregunta
        if(identifier!="b") {
            errorDetected = addRespuesta(data, position, contestadas, preguntasSinResponder);
            if(errorDetected)
                return contestadas;
        } else {
            finalizar = 1;
        }
    } while (finalizar == 0 && preguntasSinResponder > 0);
    return contestadas;
}

// FUNCIONES AUXILIARES APARTADO 7.8
// Estas funciones han sido declaradas para simplificar las comprobaciones de la función exportQuestions y facilitar su comprensión y escritura

/* Comprobador de que el fichero se abrió correctamente, en caso de detectar un fallo muestra el error ERR_FILE y devuelve un valor booleano 
    true que activará una variable de error
dataFile: fichero que se va a abrir
fileName: nombre del fichero
return: true si hay un error, false si no
*/
bool openFileWriting(ofstream& dataFile, string fileName) {
    // Abrimos el fichero
    dataFile.open(fileName, ios::out);    // Modo escritura
    if(!dataFile.is_open()) {
        error(ERR_FILE);
        return true;
    }
    return false;
}

// FUNCIONES EXTRA
// Estas funciones se han declarado para facilitar la escritura del código cuando hay que repetir una misma acción muchas veces

/* Comprobador de strings vacíos, en caso de detectar uno muestra el error ERR_EMPTY y devuelve un valor booleano true que activará una variable de error
text: string de texto
return: true si hay un error, false si no
*/
bool emptyStringCheck(string text) {
    if (text == "") {
        error(ERR_EMPTY);
        return true; // Volver al menú
    }
    return false;
}

/* Función que comprueba que un valor está dentro de un intervalo, si no muestra un mensaje de error (además de activar una variable booleana para indicarlo)
min: valor mínimo
max: valor máximo
value: valor del que se quiere comprobar que esté entre min y max
return: true si hay un error, false si no
*/
bool intervalChecker(int min, int max, int value) {
    if (value < min || value > max) {
        error(ERR_UNIT);
        return true; // Volver al menú
    }
    return false;
}

/* Esta función pide al usuario el valor de una unidad, comprueba que no sea un string vacío, lo convierte a integer y lo devuelve
return: false si todo es correcto, true para indicar un error
*/
bool unitChecker(int& unit) {
    // Variables locales
    bool errorDetected = false;
    string unitString;
    
    // Introducir unidad y comprobar que no es un carácter vacío
    cout << "Enter unit: ";
    getline(cin, unitString);
    errorDetected = emptyStringCheck(unitString);
    if (errorDetected) {  // Comprobar si se ha activado la señal de error
        return true; // Volver al menú
    }

    unit = atoi(unitString.c_str());  // Convertir string a integer
    return false;
}

/* Comprobador de presencia de caracteres '|' en el string, en caso de detectar uno muestra el error ERR_CHAR y devuelve un valor booleano 
    true que activará una variable de error
text: string de texto
return: true si hay un error, false si no
*/
bool verticalBarCheck(string text) {
    if(text.find('|') != string::npos) {
        error(ERR_CHAR);
        return true;
    }
    return false;
}

/* Comprobador de que el fichero se abrió correctamente, en caso de detectar un fallo muestra el error ERR_FILE y devuelve un valor booleano 
    true que activará una variable de error
dataFile: fichero que se va a abrir
fileName: nombre del fichero
return: true si hay un error, false si no
*/
bool fileOpenedCheck(ifstream& dataFile, string fileName) {
    // Abrimos el fichero
    dataFile.open(fileName);    // Modo lectura
    if(!dataFile.is_open()) {
        error(ERR_FILE);
        return true;
    }
    return false;
}

/* Esta función pide al usuario el ID de una pregunta, comprueba que no sea un string vacío y que exista, lo convierte a integer y lo devuelve
data: base de datos
return: posición del ID, -1 si hay un error en el ID introducido, -2 si no se ha encontrado el ID en la base de datos
*/
int questionIDChecker(Database data) {
    // Variables locales
    bool errorDetected = false;
    string idString;
    unsigned int id = 0;
    
    // Introducir ID y comprobar que no es un carácter vacío
    cout << "Enter question id: ";
    getline(cin, idString);
    errorDetected = emptyStringCheck(idString);
    if (errorDetected) {  // Comprobar si se ha activado la señal de error
        return -1; // Volver al menú
    }

    id = atoi(idString.c_str());  // Convertir string a integer

    for(unsigned int i = 0; i < data.questions.size(); i++) {
        if(data.questions[i].id==id)return i;
    }

    return -2;
}