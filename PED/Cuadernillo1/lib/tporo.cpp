#include "../include/tporo.h"
#include <ctype.h>

// Constructor con los valores por defecto
TPoro::TPoro() {
    // Inicializamos las coordenadas x e y a 0
    this->x = 0;
    this->y = 0;
    // Inicializamos el volumen a 0
    this->volumen = 0;
    // Inicializamos el color a nullptr ya que no hay color por defecto
    this->color = nullptr;
}

// Constructor parametrizado que inicializa el color a nullptr
TPoro::TPoro(int x, int y, double vol) {
    // Asignamos los valores de x e y a los parámetros proporcionados
    this->x = x;
    this->y = y;
    // Asignamos el volumen al valor proporcionado
    this->volumen = vol;
    // Inicializamos el color a nullptr ya que no hay un color proporcionado
    this->color = nullptr;
}

// Constructor parametrizado que incluye color
TPoro::TPoro(int x, int y, double vol, const char* col) : x(x), y(y), volumen(vol) {
    // Si se proporciona un color, realizamos una copia profunda
    if(col != nullptr) {
        // Reservamos memoria para el color, incluyendo espacio para el caracter nulo
        this->color = new char[strlen(col) + 1];
        // Copiamos el color proporcionado
        for(long unsigned int i = 0; i < strlen(col); i++)
            this->color[i] = tolower(col[i]);
        // Aseguramos que la cadena termina con el caracter nulo
        this->color[(int)strlen(col)] = '\0';
    } else
        // Si no se proporciona un color, inicializamos a nullptr
        this->color = nullptr;
}

// Constructor de copia
TPoro::TPoro(const TPoro &poro) : x(poro.x), y(poro.y), volumen(poro.volumen) {
    // Si el objeto TPoro proporcionado tiene un color, lo copiamos
    if (poro.color != nullptr) {
        size_t len = strlen(poro.color);
        this->color = new char[len + 1];  // Reservamos memoria para el color
        for (size_t i = 0; i < len; i++)
            this->color[i] = tolower(poro.color[i]); // Convertimos a minúsculas
        this->color[len] = '\0'; // Aseguramos que la cadena termine con el caracter nulo
    } else {
        // Si el objeto TPoro proporcionado no tiene un color, lo inicializamos a nullptr
        this->color = nullptr;
    }
}

// Destructor
TPoro::~TPoro() {
    // Resetear los valores por defecto
    this->x = 0;
    this->y = 0;
    this->volumen = 0;
    // Liberamos la memoria del color si no es nullptr
    if (this->color != nullptr) {
        delete [] this->color;
        this->color = nullptr;
    }
}

// Sobrecarga operador =
TPoro & TPoro::operator=(const TPoro &poro) {
    if (this != &poro) {
        // Liberamos la memoria anterior
        delete[] this->color;
        
        // Copiamos los valores primitivos
        this->x = poro.x;
        this->y = poro.y;
        this->volumen = poro.volumen;

        // Copiamos la cadena color con una nueva reserva de memoria
        if (poro.color != nullptr) {
            this->color = new char[strlen(poro.color) + 1];
            strcpy(this->color, poro.color);
        } else {
            this->color = nullptr;
        }
    }
    return *this;
}

// Sobrecarga operador ==
bool TPoro::operator==(TPoro &otro) const {
    // Comprobamos si las propiedades de ambos objetos son iguales
    bool mismaPos = (this->x == otro.x) && (this->y == otro.y);
    bool mismoVolumen = (this->volumen == otro.volumen);
    bool mismoColor = false;
    // Comparamos los colores teniendo en cuenta la posibilidad de ser nullptr
    if(this->color == nullptr && otro.color == nullptr)
        mismoColor = true;
    else if(this->color != nullptr && otro.color != nullptr)
        mismoColor = (strcmp(this->color, otro.color) == 0);
    // Retornamos true si todas las propiedades son iguales
    return mismaPos && mismoVolumen && mismoColor;
}

// Sobrecarga operador !=
bool TPoro::operator!=(TPoro &poro) const {
    // Devuelve true si los objetos son diferentes
    return !(*this == poro);
}

// Asigna x e y a los valores pasados por parámetro
void TPoro::Posicion(int x, int y) {
    this->x = x;
    this->y = y;
}

// Asigna vol al valor pasado por parámetro
void TPoro::Volumen(double vol) {
    this->volumen = vol;
}

// Asignador de un color nuevo al objeto TPoro
void TPoro::Color(const char* col) {
    // Liberamos la memoria previa del color si no es nullptr
    delete[] this->color;
    // Si se proporciona un color, realizamos una copia profunda
    if(col != nullptr) {
        int size = (int)strlen(col); // Guardamos el tamaño del color proporcionado
        this->color = new char[size + 1]; // Reservamos memoria
        // Copiamos el color carácter por carácter
        for(int i = 0; i < size; i++)
            this->color[i] = tolower(col[i]);
        // Aseguramos que la cadena termina con el caracter nulo
        this->color[size] = '\0';
    } else
        this->color = nullptr;
}

// Getter para la posición x
int TPoro::PosicionX() {
    return this->x;
}

// Getter para la posición y
int TPoro::PosicionY() {
    return this->y;
}

// Getter para el volumen
double TPoro::Volumen() {
    return this->volumen;
}

// Getter para el color ,ediante copia defensiva para evitar fallos
char* TPoro::Color() const {
    if (color == nullptr) return nullptr;
    char* copy = new char[strlen(color) + 1];
    strcpy(copy, color);
    return copy;
}

// Comprueba si el TPoro cumple las condiciones para considerarse vacío
bool TPoro::EsVacio() const {
    // Un TPoro se considera vacío si sus coordenadas, volumen y color son nulos
    return (this->x == 0 && this->y == 0 && this->volumen == 0 && this->color == nullptr);
}

// Sobrecarga operador <<
ostream & operator<<(ostream &os, const TPoro &poro) {
    // En caso de que el poro no esté vacío, escribimos sus datos
    if(!poro.EsVacio()){
        os.setf(ios::fixed); // Usamos notación fija
        os.precision(2); // Precisión de 2 decimales
        os << "(" << poro.x << ", " << poro.y << ") " << poro.volumen << " ";
        // Comprobamos si hay un color para mostrar
        if(poro.color!=nullptr)
            os << poro.color;
        else
            os << "-"; // Si no hay color, mostramos "-"
    } else
        os << "()"; // En caso de estar vacío, mostramos "()"
    return os;
}