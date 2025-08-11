#include "../include/tlistaporo.h"

// ----------- TListaNodo -----------

// Constructor con los valores por defecto
TListaNodo::TListaNodo() : e() {
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

// Constructor de copia
TListaNodo::TListaNodo(const TListaNodo &nodo) : e(nodo.e) {
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

// Destructor
TListaNodo::~TListaNodo() {
    /* 
        ! No hay que invocar al destructor de TPoro de forma explícita, ya que
        ! el compilador ya se encarga de llamar a su destructor cuando se destruye un objeto 
        ! de tipo TListaNodo. Al llamar manualmente a this->e.~TPoro(), se produce una doble 
        ! destrucción del objeto e cuando el destructor del nodo finaliza, lo que causa 
        ! un error de segmentation fault al liberar memoria de forma incorrecta
    */
    this->siguiente = nullptr;
    this->anterior = nullptr;
}

// Sobrecarga operador =
TListaNodo & TListaNodo::operator=(const TListaNodo &nodo) {
    // Asignamos el valor del TPoro
    this->e = nodo.e;
    // No modificamos los punteros anterior y siguiente
    return *this;
}


// ----------- TListaPosicion -----------

// Constructor con los valores por defecto
TListaPosicion::TListaPosicion() {
    this->pos = nullptr;
}

// Constructor de copia
TListaPosicion::TListaPosicion(const TListaPosicion &pos) {
    if(pos.pos != nullptr) this->pos = pos.pos; else this->pos = nullptr;
}

// Destructor
TListaPosicion::~TListaPosicion() {
    // ! No se debe hacer delete this->pos
    this->pos = nullptr;
}

// Sobrecarga operador =
TListaPosicion& TListaPosicion::operator=(const TListaPosicion &pos) {
    // Asignamos el puntero
    this->pos = pos.pos;
    return *this;
}

// Sobrecarga operador ==
bool TListaPosicion::operator==(const TListaPosicion &pos) const {
    return (this->pos == pos.pos);
}

// Devuelve el anterior de TListaNodo
const TListaPosicion TListaPosicion::Anterior() const {
    TListaPosicion auxList; // Nos apoyamos en un TListaPosicion auxiliar
    if(this->pos != nullptr && pos->anterior != nullptr)
        auxList.pos = this->pos->anterior;
    return auxList;
}

// Devuelve el siguiente de TListaNodo
const TListaPosicion TListaPosicion::Siguiente() const {
    TListaPosicion auxList; // Nos apoyamos en un TListaPosicion auxiliar
    if(this->pos != nullptr && pos->siguiente != nullptr)
        auxList.pos = this->pos->siguiente;
    return auxList;
}

// Comprobador de si TListaPosicion está vacía
bool TListaPosicion::EsVacia() const {
    return (this->pos == nullptr);
}


// ----------- TListaPoro -----------

TListaPoro::TListaPoro() {
    this->primero = nullptr;
    this->ultimo = nullptr;
}

TListaPoro::TListaPoro(const TListaPoro &lispor) {
    // Si la lista que se copia (lispor) está vacía, se inicializa la lista
    // actual de la misma manera: punteros a nullptr
    if (lispor.EsVacia()) {
        this->primero = nullptr;
        this->ultimo = nullptr;
    } else {
        // Inicializamos el puntero a la primera posición de la lista que se copia
        TListaNodo* punterolispor = lispor.primero;
        // Creamos el primer nodo de la lista actual y lo asignamos como el primer nodo
        TListaNodo* punteronuevo = new TListaNodo(*punterolispor);
        this->primero = punteronuevo;

        // Recorremos la lista que se copia, y por cada nodo, creamos un nuevo nodo en la lista
        // actual y lo asignamos como el siguiente nodo del anterior
        while (punterolispor->siguiente != nullptr) {
            punterolispor = punterolispor->siguiente;
            punteronuevo->siguiente = new TListaNodo(*punterolispor);
            // Ajustamos los punteros anterior y siguiente del nuevo nodo
            punteronuevo->siguiente->anterior = punteronuevo;
            punteronuevo = punteronuevo->siguiente;
        }
        // Al final, asignamos el puntero al último nodo de la lista actual
        this->ultimo = punteronuevo;
    }
}

TListaPoro::~TListaPoro() {
    // Puntero auxiliar para recorrer la lista que voy a borrar
    TListaPosicion puntero;
    // Inicializamos el puntero auxiliar a la primera posición
    puntero.pos = this->primero;
    while(puntero.Siguiente().pos != nullptr) {
        // Movemos el punteor auxiliar a la siguiente posición
        puntero.pos = puntero.Siguiente().pos;
        delete puntero.pos->anterior;
    }
    delete this->ultimo;
    this->primero = nullptr;
    this->ultimo = nullptr;
}

// Sobrecarga del operador de asignación
TListaPoro & TListaPoro::operator=(const TListaPoro &lispor) {
    if (this != &lispor) { // Verificamos que no se esté asignando a sí misma
        // Liberamos la memoria actual
        this->~TListaPoro();
        
        // Inicializamos los punteros
        this->primero = nullptr;
        this->ultimo = nullptr;
        
        // Si la lista a copiar está vacía, terminamos
        if (lispor.EsVacia()) {
            return *this;
        }
        
        // Copiamos el primer elemento
        this->primero = new TListaNodo(*lispor.primero);
        
        TListaPosicion oldpos, newpos;
        oldpos.pos = lispor.primero;
        newpos.pos = this->primero;
        
        // Recorremos la lista a copiar y creamos nuevos nodos en la lista actual
        // asignando los punteros anterior y siguiente adecuados
        while(oldpos.Siguiente().pos != nullptr) {
            if(oldpos.Anterior().pos != nullptr)
                newpos.pos->anterior = new TListaNodo(*oldpos.Anterior().pos);
            else
                newpos.pos->anterior = nullptr;
            
            oldpos.pos = oldpos.Siguiente().pos;
            newpos.pos->siguiente = new TListaNodo(*oldpos.pos);
            newpos.pos = newpos.Siguiente().pos;
        }
        
        // Asignamos el puntero al último nodo
        this->ultimo = new TListaNodo(*oldpos.pos);
        this->ultimo->anterior = newpos.Anterior().pos;
    }
    
    return *this;
}

bool TListaPoro::operator==(const TListaPoro &lispor) const {
    // Si las listas tienen distinta longitud, no pueden ser iguales
    if (this->Longitud() != lispor.Longitud()) 
        return false;

    // Punteros para recorrer ambas listas desde el principio
    TListaNodo *nodo1 = this->primero;
    TListaNodo *nodo2 = lispor.primero;

    // Recorremos ambas listas comparando los elementos
    while (nodo1 != nullptr && nodo2 != nullptr) {
        if (!(nodo1->e == nodo2->e)) // Comparar los TPoro en cada nodo
            return false;

        nodo1 = nodo1->siguiente;
        nodo2 = nodo2->siguiente;
    }

    // Si una lista terminó antes que la otra, son diferentes
    return nodo1 == nullptr && nodo2 == nullptr;
}

TListaPoro TListaPoro::operator+(const TListaPoro &lispor) const {
    // Definimos la nueva lista que vamos a crear
    TListaPoro nuevaLista;

    // Punteros auxiliares para recorrer las listas
    TListaPosicion aux1, aux2;
    aux1.pos = this->primero;
    aux2.pos = lispor.primero;

    while(aux1.pos != nullptr) {
        nuevaLista.Insertar(aux1.pos->e);
        aux1.pos = aux1.Siguiente().pos;
    }

    while(aux2.pos != nullptr) {
        nuevaLista.Insertar(aux2.pos->e);
        aux2.pos = aux2.Siguiente().pos;
    }

    return nuevaLista;
}

TListaPoro TListaPoro::operator-(const TListaPoro &lispor) const {
    // Definimos la nueva lista que vamos a crear
    TListaPoro nuevaLista;

    TListaPosicion aux;
    aux.pos = this->primero;

    while (aux.pos != nullptr) {
        TPoro poro = this->Obtener(aux);
        if (!lispor.Buscar(poro)) { // Solo insertamos si no está en lispor
            nuevaLista.Insertar(poro);
        }
        aux.pos = aux.Siguiente().pos;
    }

    return nuevaLista;
}

bool TListaPoro::EsVacia() const {
    return (this->primero == nullptr && this->ultimo == nullptr);
}

bool TListaPoro::Insertar(TPoro &poro) {
    // Comprobamos si la lista está vacía, en tal caso hacemos la inserción
    if(this->primero == nullptr) {
        this->primero = new TListaNodo();
        this->primero->e = poro;
        this->primero->siguiente = nullptr;
        this->primero->anterior = nullptr;
        this->ultimo = this->primero;
        return true;
    }

    // Punteros auxiliares para recorrer la lista
    TListaPosicion puntero, aux1, aux2;
    // Inicializamos el puntero al primer nodo de la lista
    puntero.pos = this->primero;

    // Recorremos la lista mientras el puntero no sea nulo
    while(puntero.pos != nullptr) {
        // Si encontramos un nodo con el mismo TPoro, no insertamos y devolvemos false
        if(puntero.pos->e == poro) return false;

        // Si encontramos la posición donde el TPoro debe ser insertado 
        // basándonos en el volumen, insertamos el nuevo nodo aquí
        if(puntero.pos->e.Volumen() >= poro.Volumen()) {
            // Puntero auxiliar que se queda en el elemento izquierdo
            aux1.pos = puntero.pos->anterior;
            // Puntero auxiliar que se queda en el elemento siguiente a aux1 antes de la inserción
            aux2.pos = puntero.pos;

            // Si aux1 es nulo, significa que estamos insertando al inicio de la lista
            if(aux1.pos == nullptr) {
                // Creamos un nuevo nodo y lo asignamos como el primer nodo
                this->primero = new TListaNodo();
                // Ajustamos los punteros siguiente y anterior
                this->primero->e = poro;
                this->primero->siguiente = aux2.pos;
                aux2.pos->anterior = this->primero;
            } else {
                // Insertamos el nuevo nodo entre aux1 y aux2
                aux1.pos->siguiente = new TListaNodo();
                aux1.pos->siguiente->e = poro;
                aux1.pos->siguiente->siguiente = aux2.pos;
                aux2.pos->anterior = aux1.pos->siguiente;
            }
            return true; // Nodo insertado correctamente
        }
        // Actualizamos el puntero para avanzar al siguiente nodo
        puntero.pos = puntero.Siguiente().pos;
    }

    // Si llegamos al final de la lista sin encontrar la posición, insertamos al final
    if(puntero.pos == nullptr) {
        // Creamos un nuevo nodo al final de la lista
        this->ultimo->siguiente = new TListaNodo();
        this->ultimo->siguiente->e = poro;
        this->ultimo->siguiente->anterior = this->ultimo;
        // Actualizamos el puntero del último nodo
        this->ultimo = this->ultimo->siguiente;
        return true; // Nodo insertado correctamente
    }
    return false; // En caso de que no se pueda insertar (aunque este caso no debería ocurrir)
}

bool TListaPoro::Borrar(TPoro &poro) {
    // Puntero auxiliar para recorrer la lista
    TListaPosicion puntero;
    puntero.pos = this->primero;

    while (puntero.pos != nullptr) {  
        if (this->Obtener(puntero) == poro) return Borrar(puntero);
        puntero.pos = puntero.Siguiente().pos;
    }

    return false;
}

bool TListaPoro::Borrar(TListaPosicion &pos) {
    if (pos.EsVacia()) return false; // Si la posición pasada por parámetro está vacía no hay nada que borrar

    TListaNodo *aBorrar = pos.pos; // Nodo a eliminar

    // Si es el único nodo
    if (primero == ultimo) {
        primero = ultimo = nullptr;
    } 
    // Si es el primer nodo
    else if (aBorrar == primero) {
        primero = primero->siguiente;
        primero->anterior = nullptr;
    } 
    // Si es el último nodo
    else if (aBorrar == ultimo) {
        ultimo = ultimo->anterior;
        ultimo->siguiente = nullptr;
    } 
    // Si está en medio
    else {
        aBorrar->anterior->siguiente = aBorrar->siguiente;
        aBorrar->siguiente->anterior = aBorrar->anterior;
    }

    delete aBorrar; // Liberar memoria
    pos.pos = nullptr; // Posición ahora es inválida
    return true;
}

const TPoro & TListaPoro::Obtener(const TListaPosicion &pos) const {
    static TPoro vacio;  // Se construye con el constructor por defecto: (0, 0, 0, NULL)
    if (pos.EsVacia())
        return vacio;
    return pos.pos->e;
}

bool TListaPoro::Buscar(TPoro &poro) const {
    // Puntero auxiliar para recorrer la lista
    TListaPosicion puntero;
    puntero.pos = this->primero;

    while (puntero.pos != nullptr) {
        if (this->Obtener(puntero) == poro) return true;
        puntero.pos = puntero.Siguiente().pos;
    }

    return false;
}

int TListaPoro::Longitud() const {
    int contador = 0;   // Contador de elementos de la lista

    // Puntero auxiliar para recorrer la lista
    TListaPosicion puntero;
    puntero.pos = this->primero;

    // Recorremos la lista contando los elementos
    while (puntero.pos != nullptr) { // Mientras la posición no esté vacía
        contador++;  
        puntero.pos = puntero.Siguiente().pos; // Avanzamos al siguiente nodo
    }

    return contador;
}

TListaPosicion TListaPoro::Primera() const {
    TListaPosicion auxList; // Nos apoyamos en un TListaPosicion auxiliar
    if(!(this->EsVacia())) auxList.pos = this->primero;
    return auxList;
}

TListaPosicion TListaPoro::Ultima() const {
    TListaPosicion auxList; // Nos apoyamos en un TListaPosicion auxiliar
    if(!(this->EsVacia())) auxList.pos = this->ultimo;
    return auxList;
}

TListaPoro TListaPoro::ExtraerRango(int n1, int n2) {
    TListaPoro nuevaLista;

    int posActual = 1;
    TListaPosicion pos, aux;
    pos.pos = this->Primera().pos;
    
    if(n2 > this->Longitud()) {
        while(posActual < n1) {pos.pos = pos.Siguiente().pos; posActual = posActual + 1;}
        while(posActual <= this->Longitud()) {
            aux.pos = pos.Siguiente().pos;
            TPoro temp = this->Obtener(pos);
            nuevaLista.Insertar(temp);
            this->Borrar(pos);
            pos.pos = aux.pos;
            posActual = posActual + 1;
        }
    } else if(n1 <= 0) {
        while(posActual <= n2) {
            aux.pos = pos.Siguiente().pos;
            TPoro temp = this->Obtener(pos);
            nuevaLista.Insertar(temp);
            this->Borrar(pos);
            pos.pos = aux.pos;
            posActual = posActual + 1;
        }
    } else if(n1 == n2) {
        TPoro temp = this->Obtener(pos);
        nuevaLista.Insertar(temp);
    } else if(n1 > n2) {
        return nuevaLista;
    }

    return nuevaLista;
}

ostream & operator<<(ostream &os, const TListaPoro &lispor) {
    os << "("; // Paréntesis de apertura

    if (!lispor.EsVacia()) { // Si la lispor no está vacía
        TListaPosicion pos;
        pos = lispor.Primera();

        while (!pos.EsVacia()) {
            os << pos.pos->e; // Mostrar el elemento TPoro usando su operador <<

            pos = pos.Siguiente(); // Avanzar a la siguiente posición
            if (!pos.EsVacia()) {
                os << " "; // Separador entre elementos
            }
        }
    }

    os << ")"; // Paréntesis de cierre
    return os;
}
