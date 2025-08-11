#include "tporo.h"

#ifndef _TVECTORPORO_H_
#define _TVECTORPORO_H_

class TVectorPoro {
    friend class TABBPoro;
    friend ostream & operator<<(ostream &os, const TVectorPoro &vectorporo);
    private:
        int dimension;
        TPoro *datos;
        TPoro error;
        TVectorPoro sort();
        TVectorPoro append(TVectorPoro other);
    public:
        TVectorPoro();
        TVectorPoro(int dimens);
        TVectorPoro(TVectorPoro &vectorporo);
        ~TVectorPoro();
        TVectorPoro & operator=(TVectorPoro &vectorporo);
        bool operator==(const TVectorPoro &vectorporo) const;
        bool operator!=(const TVectorPoro &vectorporo) const;
        TPoro &operator[](int dimens);
        TPoro operator[](int dimens) const;
        int Longitud();
        int Cantidad();
        bool Redimensionar(int dimens);
};

#endif