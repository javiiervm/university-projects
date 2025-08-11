#include "../include/tvectorporo.h"

// Constructor por defecto
TVectorPoro::TVectorPoro() {
    // Inicializamos la dimensión a 0 porque el vector está vacío
    this->dimension = 0;
    // Inicializamos el puntero de datos a nullptr porque aún no hay elementos
    this->datos = nullptr;
}

// Constructor parametrizado
TVectorPoro::TVectorPoro(int dimens) {
    // Si la dimensión es positiva, inicializamos los datos con el tamaño especificado
    if(dimens > 0) {
        this->dimension = dimens;
        this->datos = new TPoro[dimension]; // Asignamos memoria para los datos
    } else {
        // Si la dimensión es 0 o negativa, configuramos los valores por defecto
        this->dimension = 0;
        this->datos = nullptr;
    }
}

// Constructor de copia
TVectorPoro::TVectorPoro(TVectorPoro &vectorporo) {
    // Copiamos la dimensión del vector proporcionado
    this->dimension = vectorporo.dimension;
    // Si el vector proporcionado tiene datos, realizamos una copia profunda
    if (vectorporo.datos != nullptr) {
        this->datos = new TPoro[this->dimension]; // Asignamos memoria para copiar los datos
        for (int i = 0; i < this->dimension; i++)
            this->datos[i] = vectorporo.datos[i]; // Copiamos cada elemento
    } else {
        this->datos = nullptr; // Si no hay datos, establecemos a nullptr
    }
}

// Destructor
TVectorPoro::~TVectorPoro() {
    // Reiniciamos la dimensión a 0
    this->dimension = 0;
    // Liberamos la memoria asignada si no es nullptr
    if (this->datos != nullptr) {
        delete[] this->datos;
        this->datos = nullptr; // Establecemos a nullptr para evitar dangling pointers
    }
}

// Sobrecarga del operador de asignación
TVectorPoro & TVectorPoro::operator=(TVectorPoro &vectorporo) {
    // Verificamos la auto-asignación
    if(this != &vectorporo) {
        // Copiamos la dimensión
        this->dimension = vectorporo.dimension;
        // Si el vector proporcionado tiene datos, realizamos una copia profunda
        if (vectorporo.datos != nullptr) {
            this->datos = new TPoro[this->dimension];
            for (int i = 0; i < this->dimension; i++)
                this->datos[i] = vectorporo.datos[i];
        } else {
            this->datos = nullptr; // Si no hay datos, establecemos a nullptr
        }
    }
    return *this; // Permitimos la asignación en cascada
}

// Sobrecarga del operador de igualdad
bool TVectorPoro::operator==(const TVectorPoro &vectorporo) const {
    // Comprobamos si las dimensiones son iguales
    if(this->dimension != vectorporo.dimension)
        return false;
    // Comparamos cada elemento
    for(int i = 0; i < this->dimension; i++)
        if(this->datos[i] != vectorporo.datos[i])
            return false;
    return true; // Si todas las comprobaciones pasan, son iguales
}

// Sobrecarga del operador de desigualdad
bool TVectorPoro::operator!=(const TVectorPoro &vectorporo) const {
    // Retornamos el contrario del operador de igualdad
    if(this->dimension != vectorporo.dimension)
        return true;
    for(int i = 0; i < this->dimension; i++)
        if(this->datos[i] != vectorporo.datos[i])
            return true;
    return false;
}

// Operador de acceso (Setter)
TPoro &TVectorPoro::operator[](int dimens) {
    // Verificamos si el índice está dentro de los límites
    if (dimens >= 1 && dimens <= this->dimension)
        return this->datos[dimens - 1]; // Devolvemos una referencia modificable
    return this->error; // Devolvemos un objeto de error
}

// Operador de acceso (Getter)
TPoro TVectorPoro::operator[](int dimens) const {
    // Verificamos si el índice está dentro de los límites
    if (dimens >= 1 && dimens <= this->dimension)
        return this->datos[dimens - 1]; // Devolvemos una copia del elemento
    return this->error; // Devolvemos un objeto de error
}

// Getter de la longitud
int TVectorPoro::Longitud() {
    return this->dimension; // Retornamos la dimensión actual del vector
}

// Devuelve la cantidad de elementos no vacíos
int TVectorPoro::Cantidad() {
    int contador = 0;
    // Iteramos sobre los datos y contamos los no vacíos
    for(int i = 0; i < this->dimension; i++)
        if(!(this->datos[i].EsVacio())) contador++;
    return contador;
}

// Redimensiona el vector, devuelve true si tiene éxito
bool TVectorPoro::Redimensionar(int dimens) {
    // Si la nueva dimensión no es positiva o es igual a la actual no hacemos nada
    if(dimens <= 0 || dimens == this->dimension) return false;

    TPoro *aux = new TPoro[dimens]; // Creamos un nuevo arreglo auxiliar
    TPoro *vacio = new TPoro(); // Poro vacío para inicializar nuevas posiciones

    // Copiamos los datos antiguos al nuevo arreglo y añadimos nuevos elementos vacíos si es necesario
    if(dimens > this->dimension) {
        for(int i = 0; i < dimens; i++)
            if(i < this->dimension)
                aux[i] = this->datos[i];
            else 
                aux[i] = (*vacio);
    } else {
        // Si la nueva dimensión es menor, copiamos solo los datos que caben
        for(int i = 0; i < dimens; i++)
            aux[i] = this->datos[i];
    }

    // Actualizamos la dimensión y los datos
    this->dimension = dimens;
    delete[] this->datos;
    this->datos = aux;
    return true;
}

// Sobrecarga del operador de inserción en flujo de salida
ostream & operator<<(ostream &os, const TVectorPoro &vectorporo) {
    if(vectorporo.dimension != 0) {
        os << "[";
        for(int i = 0; i < vectorporo.dimension; i++) {
            os << i + 1 << " " << vectorporo.datos[i];
            if(i + 1 != vectorporo.dimension) os << " ";
        }
        os << "]";
    } else {
        os << "[]";
    }
    return os; // Devolvemos el stream modificado para permitir la concatenación
}

TVectorPoro TVectorPoro::sort() {
    for(int i = 1; i < this->dimension; i++) {
        TPoro aux2 = this->datos[i];
        TPoro aux1 = this->datos[i-1];
        if(aux1.Volumen() > aux2.Volumen()) {
            this->datos[i-1] = aux2;
            this->datos[i] = aux1;
        }
    }
    return *this;
}

TVectorPoro TVectorPoro::append(TVectorPoro other) {
    int oldDim = this->dimension;
    this->Redimensionar(this->dimension + other.dimension);
    for(int i = oldDim; i < this->dimension; i++) {
        this->datos[i] = other.datos[i - oldDim];
    }
    return *this;
}
