#include <iostream>
#include <string.h>
using namespace std;

#ifndef _TPORO_H_
#define _TPORO_H_

class TPoro {
    friend class TListaPoro;
    friend class TABBPoro;
    friend ostream & operator<<(ostream &os, const TPoro &poro);
    private:
        int x;
        int y;
        double volumen;
        char* color;
    public:
        TPoro();
        TPoro(int x, int y, double vol);
        TPoro(int x, int y, double vol, const char* col);
        TPoro(const TPoro &poro);
        ~TPoro();
        TPoro & operator=(const TPoro &poro);
        bool operator==(const TPoro &poro) const;
        bool operator!=(const TPoro &poro) const;
        void Posicion(int x, int y);
        void Volumen(double vol);
        void Color(const char* col);
        int PosicionX();
        int PosicionY();
        double Volumen();
        char * Color() const;
        bool EsVacio() const;
};

#endif