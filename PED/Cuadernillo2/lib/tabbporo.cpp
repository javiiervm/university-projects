#include "tabbporo.h"
#include <queue>


// =================== TNodoABB ===================

TNodoABB::TNodoABB() {
    this->item = TPoro();
    this->iz = TABBPoro();
    this->de = TABBPoro();
}

TNodoABB::TNodoABB(const TNodoABB &other) {
    this->item = other.item;
    this->iz = other.iz;
    this->de = other.de;
}

TNodoABB::~TNodoABB() {
    this->item.~TPoro();
    //this->iz.~TABBPoro();
    //this->de.~TABBPoro();
}

TNodoABB & TNodoABB::operator=(const TNodoABB &other) {
    this->item = other.item;
    this->iz = other.iz;
    this->de = other.de;
    return *this;
}


// =================== TABBPoro ===================

void TABBPoro::InordenAux(TVectorPoro &v, int &i) const {
    if(this->nodo != nullptr) {
        // Primero visitamos la parte izquierda del nodo actual
        this->nodo->iz.InordenAux(v, i);
        // Luego guardamos el elemento actual en el vector
        v[i] = this->nodo->item;
        // Incrementamos el indice para el proximo elemento
        ++i;
        // Por ultimo visitamos la parte derecha del nodo actual
        this->nodo->de.InordenAux(v, i);
    }
}

void TABBPoro::PreordenAux(TVectorPoro &v, int &i) const {
    if(this->nodo != nullptr) {
        // Primero guardamos el elemento actual en el vector
        v[i] = this->nodo->item;
        // Incrementamos el indice para el proximo elemento
        ++i;
        // Luego visitamos la parte izquierda del nodo actual
        this->nodo->iz.PreordenAux(v, i);
        // Por ultimo visitamos la parte derecha del nodo actual
        this->nodo->de.PreordenAux(v, i);
    }
}

void TABBPoro::PostordenAux(TVectorPoro &v, int &i) const {
    if(this->nodo != nullptr) {
        // Primero visitamos la parte izquierda del nodo actual
        this->nodo->iz.PostordenAux(v, i);
        // Luego visitamos la parte derecha del nodo actual
        this->nodo->de.PostordenAux(v, i);
        // Por ultimo guardamos el elemento actual en el vector
        v[i] = this->nodo->item;
        // Incrementamos el indice para el proximo elemento
        ++i;
    }
}

// Función auxiliar que devuelve una copia de un nodo
TNodoABB* TABBPoro::Copiar(const TNodoABB* nodo) {
    if (nodo == nullptr) return nullptr;
    TNodoABB* nuevo = new TNodoABB();
    nuevo->item = nodo->item;
    nuevo->iz.nodo = Copiar(nodo->iz.nodo);
    nuevo->de.nodo = Copiar(nodo->de.nodo);
    return nuevo;
}


TABBPoro::TABBPoro() {
    this->nodo = nullptr;
}

TABBPoro::TABBPoro(const TABBPoro &other) {
    this->nodo = Copiar(other.nodo);
}

TABBPoro::~TABBPoro() {
    if(this->nodo != nullptr) {
        this->nodo->iz.~TABBPoro();
        this->nodo->de.~TABBPoro();
        delete this->nodo;
        this->nodo = nullptr;
    }
}

TABBPoro & TABBPoro::operator=(const TABBPoro &other) {
    if (this->nodo != nullptr && this->nodo != other.nodo)
        delete this->nodo;
    this->nodo = Copiar(other.nodo);
    return *this;
}

bool TABBPoro::operator==(const TABBPoro &other) const {
    TVectorPoro recorridoThis = this->Inorden();
    TVectorPoro recorridoOther = other.Inorden();
    recorridoThis.sort();
    recorridoOther.sort();
    return recorridoThis == recorridoOther;
}

bool TABBPoro::EsVacio() const {
    return this->nodo == nullptr;
}

bool TABBPoro::Insertar(const TPoro &other) {
    // Si el árbol está vacío, se crea un nuevo nodo con el elemento
    if (EsVacio()) {
        nodo = new TNodoABB();
        nodo->item = other;
        return true;
    }

    // Si el elemento ya existe en el árbol (volumen igual), no se puede insertar
    if (other.volumen == nodo->item.Volumen())
        return false;

    // Si el volumen del nuevo TPoro es menor, insertar en el subárbol izquierdo
    if (other.volumen < nodo->item.Volumen()) {
        return nodo->iz.Insertar(other);
    }

    // Si el volumen del nuevo TPoro es mayor, insertar en el subárbol derecho
    return nodo->de.Insertar(other);
}

bool TABBPoro::Borrar(const TPoro &p) {
    // Si el árbol está vacío, no se puede borrar nada
    if (EsVacio())
        return false;

    // Si el elemento a borrar es menor, buscar en el subárbol izquierdo
    if (p.volumen < nodo->item.Volumen())
        return nodo->iz.Borrar(p);

    // Si el elemento a borrar es mayor, buscar en el subárbol derecho
    if (p.volumen > nodo->item.Volumen())
        return nodo->de.Borrar(p);

    // Si el volumen coincide, comprobamos si el TPoro completo es igual
    if (!(nodo->item == p))
        return false;

    // CASO 1: nodo hoja
    if (nodo->iz.EsVacio() && nodo->de.EsVacio()) {
        delete nodo;
        nodo = nullptr;
        return true;
    }

    // CASO 2: solo hijo izquierdo
    if (!nodo->iz.EsVacio() && nodo->de.EsVacio()) {
        TNodoABB* temp = nodo;
        nodo = nodo->iz.nodo;
        temp->iz.nodo = nullptr;
        delete temp;
        return true;
    }

    // CASO 3: solo hijo derecho
    if (nodo->iz.EsVacio() && !nodo->de.EsVacio()) {
        TNodoABB* temp = nodo;
        nodo = nodo->de.nodo;
        temp->de.nodo = nullptr;
        delete temp;
        return true;
    }

    // CASO 4: dos hijos
    // Buscar el mayor del subárbol izquierdo
    TABBPoro* aux = &nodo->iz;
    while (!aux->nodo->de.EsVacio()) {
        aux = &aux->nodo->de;
    }

    // Guardamos el TPoro a mover
    TPoro itemAEliminar = aux->nodo->item;

    // Sustituimos el item actual por el mayor de la izquierda
    nodo->item = itemAEliminar;

    // Eliminamos el duplicado que ahora está en el subárbol izquierdo
    return nodo->iz.Borrar(itemAEliminar);
}

bool TABBPoro::Buscar(const TPoro &other) const {
    // Si el árbol está vacío, no se encuentra el elemento
    if (EsVacio()) return false;

    // Si el volumen coincide, comprobar si el TPoro es exactamente igual
    if (nodo->item.Volumen() == other.volumen)
        return nodo->item == other;

    // Si el volumen buscado es menor, buscar en el subárbol izquierdo
    if (other.volumen < nodo->item.Volumen())
        return nodo->iz.Buscar(other);

    // Si es mayor, buscar en el subárbol derecho
    return nodo->de.Buscar(other);
}

TPoro TABBPoro::Raiz() const {
    if(this->EsVacio())
        return TPoro();
    return this->nodo->item;
}

int TABBPoro::Altura() const {
    if(this->EsVacio()) return 0;
    return 1 + (max((this->nodo->iz.Altura()), (this->nodo->de.Altura())));
}

int TABBPoro::Nodos() const {
    if(this->EsVacio()) return 0;
    return 1 + this->nodo->iz.Nodos() + this->nodo->de.Nodos();
}

int TABBPoro::NodosHoja() const {
    if(this->EsVacio())
        return 0;
    else if(this->nodo->de.EsVacio() && this->nodo->iz.EsVacio()) 
        return 1;
    return this->nodo->iz.NodosHoja() + this->nodo->de.NodosHoja();
}

// Devuelve el recorrido en inorden
TVectorPoro TABBPoro::Inorden() const {
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    InordenAux(v, posicion);
    return v;
}

// Devuelve el recorrido en preorden
TVectorPoro TABBPoro::Preorden() const {
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    PreordenAux(v, posicion);
    return v;
}

// Devuelver el recorrido en postorden
TVectorPoro TABBPoro::Postorden() const {
    // Posición en el vector que almacena el recorrido
    int posicion = 1;
    // Vector del tamaño adecuado para almacenar todos los nodos
    TVectorPoro v(Nodos());
    PostordenAux(v, posicion);
    return v;
}

TVectorPoro TABBPoro::Niveles() const {
    TVectorPoro solucion;
    solucion.Redimensionar(this->Nodos());

    TABBPoro copia;
    copia.nodo = this->nodo;
    
    queue<TABBPoro*> cola;
    cola.push(&copia);
    
    TABBPoro* aux;

    while(!cola.empty()) {
        aux = cola.front();
        solucion[solucion.Cantidad()+1] = aux->nodo->item;
        if(!cola.front()->nodo->iz.EsVacio()) {
            cola.push(&aux->nodo->iz);
        }
        if(!cola.front()->nodo->de.EsVacio()) {
            cola.push(&aux->nodo->de);
        }
        cola.pop();
    }

    return solucion;
}

TABBPoro TABBPoro::operator+(const TABBPoro &other) const {
    TABBPoro copia = *this;
    TVectorPoro recorrido = other.Inorden();
    for(int i = 0; i < recorrido.dimension; i++) {
        copia.Insertar(recorrido[i]);
    }
    return copia;
}

TABBPoro TABBPoro::operator-(const TABBPoro &other) const {
    TABBPoro copia = *this;
    TVectorPoro recorrido = other.Inorden();
    for(int i = 0; i < recorrido.dimension; i++) {
        copia.Borrar(recorrido[i]);
    }
    return copia;
}

ostream & operator<<(ostream &os, TABBPoro &other) {
    os << other.Niveles();
    return os;
}

bool TABBPoro::esHoja() const {
    return (!(this->EsVacio()) && this->nodo->de.EsVacio() && this->nodo->iz.EsVacio());
}
