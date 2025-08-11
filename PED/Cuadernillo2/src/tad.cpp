#include <iostream>
#include "tabbporo.h"
using namespace std;

/*******************************************************************/
/***** INSERCION Y BORRADOS MULTIPLES; posible desborde de memoria */
/*******************************************************************/
int main(void){
  
    TABBPoro a;

    TPoro p20(1,2,20,(char *) "rojo");
    TPoro p10(1,2,10,(char *) "rojo");
    TPoro p24(1,2,24,(char *) "rojo");
    TPoro p8(1,2,8,(char *) "rojo");
    TPoro p12(1,2,12,(char *) "rojo");
    TPoro p26(1,2,26,(char *) "rojo");
    TPoro p28(1,2,28,(char *) "rojo");
    TPoro p11(1,2,11,(char *) "rojo");

    a.Insertar(p20);
    a.Insertar(p10);
    a.Insertar(p24);
    a.Insertar(p8);
    a.Insertar(p12);
    a.Insertar(p26);
    a.Insertar(p28);
    a.Insertar(p11);


    TVectorPoro inorden(8);
    inorden[1] = p8;
    inorden[2] = p10;
    inorden[3] = p11;
    inorden[4] = p12;
    inorden[5] = p20;
    inorden[6] = p24;
    inorden[7] = p26;
    inorden[8] = p28;


    TVectorPoro preorden(8);
    preorden[1] = p20;
    preorden[2] = p10;
    preorden[3] = p8;
    preorden[4] = p12;
    preorden[5] = p11;
    preorden[6] = p24;
    preorden[7] = p26;
    preorden[8] = p28;


    TVectorPoro postorden(8);
    postorden[1] = p8;
    postorden[2] = p11;
    postorden[3] = p12;
    postorden[4] = p10;
    postorden[5] = p28;
    postorden[6] = p26;
    postorden[7] = p24;
    postorden[8] = p20;


    TVectorPoro niveles(8);
    niveles[1] = p20;
    niveles[2] = p10;
    niveles[3] = p24;
    niveles[4] = p8;
    niveles[5] = p12;
    niveles[6] = p26;
    niveles[7] = p11;
    niveles[8] = p28;

    if (a.Inorden() != inorden){
        cout << "Fallo en INORDEN" << endl;
        cout << "Expected:" << inorden << endl;
        cout << "Mine:" << a.Inorden() << endl;
    }

    if (a.Preorden() != preorden){
        cout << "Fallo en PREORDEN" << endl;
        cout << "Expected:" << preorden << endl;
        cout << "Mine:" << a.Preorden() << endl;
    }

    if (a.Postorden() != postorden){
        cout << "Fallo en POSTORDEN" << endl;
        cout << "Expected:" << postorden << endl;
        cout << "Mine:" << a.Postorden() << endl;
    }

    if (a.Niveles() != niveles){
        cout << "Fallo en NIVELES" << endl;
        cout << "Expected:" << niveles << endl;
        cout << "Mine:" << a.Niveles() << endl;
    }

    cout << "Todo bien?" << endl;

    return 1;
}
