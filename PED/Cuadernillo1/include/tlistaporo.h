#ifndef _TLISTAPORO_H_
#define _TLISTAPORO_H_

#include "tvectorporo.h"
#include <iostream>
using namespace std;

class TListaPoro;
class TListaNodo;
class TListaPosicion;

class TListaNodo {
    friend ostream & operator<<(ostream &os, const TListaPoro &lispor);
    friend class TListaPosicion;
    friend class TListaPoro;
    private:
        TPoro e;
        TListaNodo *anterior;
        TListaNodo *siguiente;
    public:
        TListaNodo();
        TListaNodo(const TListaNodo &nodo);
        ~TListaNodo();
        TListaNodo & operator=(const TListaNodo &nodo);
};

class TListaPosicion {
    friend class TListaPoro;
    friend ostream & operator<<(ostream &os, const TListaPoro &lispor);
    private:
        TListaNodo *pos;
    public:
        TListaPosicion();
        TListaPosicion(const TListaPosicion &pos);
        ~TListaPosicion();
        TListaPosicion& operator=(const TListaPosicion &pos);
        bool operator==(const TListaPosicion &pos) const;
        const TListaPosicion Anterior() const;
        const TListaPosicion Siguiente() const;
        bool EsVacia() const;
};

class TListaPoro {
    friend ostream & operator<<(ostream &os, const TListaPoro &lispor);
    private:
        TListaNodo *primero;
        TListaNodo *ultimo;
    public:
        TListaPoro();
        TListaPoro(const TListaPoro &lispor);
        ~TListaPoro();
        TListaPoro & operator=(const TListaPoro &lispor);
        bool operator==(const TListaPoro &lispor) const;
        TListaPoro operator+(const TListaPoro &lispor) const;
        TListaPoro operator-(const TListaPoro &lispor) const;
        bool EsVacia() const;
        bool Insertar(TPoro &poro);
        bool Borrar(TPoro &poro);
        bool Borrar(TListaPosicion &pos);
        const TPoro & Obtener(const TListaPosicion &pos) const;
        bool Buscar(TPoro &poro) const;
        int Longitud() const;
        TListaPosicion Primera() const;
        TListaPosicion Ultima() const;
        TListaPoro ExtraerRango(int n1, int n2);
};

#endif