#include "tvectorporo.h"

#ifndef _TABBPORO_H_
#define _TABBPORO_H_

class TNodoABB;

class TABBPoro {
    friend class TNodoAAB;
    friend ostream & operator<<(ostream &os, TABBPoro &other);
    private:
        TNodoABB *nodo;
        void InordenAux(TVectorPoro &v, int &i) const;
        void PreordenAux(TVectorPoro &v, int &i) const;
        void PostordenAux(TVectorPoro &v, int &i) const;
        bool esHoja() const;
        TNodoABB* Copiar(const TNodoABB* nodo);
    public:
        TABBPoro();
        TABBPoro(const TABBPoro &other);
        ~TABBPoro();
        TABBPoro & operator=(const TABBPoro &other);
        bool operator==(const TABBPoro &other) const;
        bool EsVacio() const;
        bool Insertar(const TPoro &other);
        bool Borrar(const TPoro &other);
        bool Buscar(const TPoro &other) const;
        TPoro Raiz() const;
        int Altura() const;
        int Nodos() const;
        int NodosHoja() const;
        TVectorPoro Inorden() const;
        TVectorPoro Preorden() const;
        TVectorPoro Postorden() const;
        TVectorPoro Niveles() const;
        TABBPoro operator+(const TABBPoro &other) const;
        TABBPoro operator-(const TABBPoro &other) const;
};

class TNodoABB {
    friend class TABBPoro;
    private:
        TPoro item;
        TABBPoro iz, de;
    public:
        TNodoABB();
        TNodoABB(const TNodoABB &other);
        ~TNodoABB();
        TNodoABB & operator=(const TNodoABB &other);
};

#endif
