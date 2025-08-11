#include <iostream>
#include <sstream>
#include <string>
#include "tporo.h"
#include "tvectorporo.h"
#include "tlistaporo.h"

using namespace std;

bool pruebasTPoro() {
    bool resultado = false;

    // ----------- Prueba 1: Poro vacío -----------
    cout << "Prueba 1   ";
    TPoro a1;
    ostringstream output1;
    output1 << a1 << endl; 

    if (output1.str() == "()\n") {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Output was: " << output1.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 2: Poro con valores -----------
    cout << "Prueba 2   ";
    TPoro a2(1, 2, 3, "rojo");
    ostringstream output2;
    output2 << a2 << endl; 

    if (output2.str() == "(1, 2) 3.00 rojo\n") {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Output was: " << output2.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 4: Modificar posición -----------
    cout << "Prueba 4   ";
    TPoro a3;
    a3.Posicion(10, 20);
    ostringstream output3;
    output3 << a3 << endl;

    if (output3.str() == "(10, 20) 0.00 -\n") {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Output was: " << output3.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 5: Asignación -----------
    cout << "Prueba 5   ";
    TPoro a4(1, 2, 3, "rojo"), b1;
    b1 = a4;
    ostringstream output4, output5;
    output4 << a4 << endl;
    output5 << b1 << endl;

    if (output4.str() == "(1, 2) 3.00 rojo\n" && output5.str() == "(1, 2) 3.00 rojo\n") {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Output was: " << output4.str() << " | Output was: " << output5.str();
        resultado = true;
    }

    // ----------- Prueba 6: Obtener valores -----------
    cout << "Prueba 6   ";
    TPoro a5(1, 2, 3, "rojo");
    if (a5.PosicionX() == 1 && a5.PosicionY() == 2 && a5.Volumen() == 3) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌" << endl;
        resultado = true;
    }

    // ----------- Prueba 7: Comprobación de coordenadas -----------
    cout << "Prueba 7   ";
    TPoro a6(1, 2, 3, "rojo");
    bool prueba7 = (a6.PosicionX() == 1) && (a6.PosicionY() == 2);

    cout << (prueba7 ? "EXITO!" : "ERROR! ❌") << endl;
    if (!prueba7) resultado = true;

    // ----------- Prueba 8: Comprobación de vacíos -----------
    cout << "Prueba 8   ";
    TPoro a7;
    bool vacioAntes = a7.EsVacio();
    a7.Color("rojo");
    bool vacioDespues = a7.EsVacio();

    if (vacioAntes && !vacioDespues) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌" << endl;
        resultado = true;
    }

    // ----------- Prueba 9: Destructor manual -----------
    cout << "Prueba 9   ";
    TPoro a8;
    bool antesDestructor = a8.EsVacio();
    a8.Color("rojo");
    bool despuesColor = a8.EsVacio();
    a8.~TPoro();  // No recomendado, pero para prueba manual
    bool despuesDestructor = a8.EsVacio();

    if (antesDestructor && !despuesColor && despuesDestructor) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌" << endl;
        resultado = true;
    }

    // ----------- Prueba 10: Constructores y copias -----------
    cout << "Prueba 10   ";
    TPoro a10, b10(0, 0, 0, NULL);
    TPoro c10(a10), d10(b10);

    if (a10.EsVacio() && b10.EsVacio() && c10.EsVacio() && d10.EsVacio()) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌" << endl;
        resultado = true;
    }

    return resultado;
}

bool pruebasTVectorPoro() {
    bool resultado = false;

    // ----------- Prueba 1: Longitud inicial -----------
    cout << "Prueba 1   ";
    TVectorPoro a, b(5), c(10);
    if (a.Longitud() == 0 && b.Longitud() == 5 && c.Longitud() == 10) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌" << endl;
        resultado = true;
    }

    // ----------- Prueba 2: Imprimir vector vacío -----------
    cout << "Prueba 2   ";
    ostringstream output2;
    output2 << a;
    if (output2.str() == "[]") {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Output: " << output2.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 3: Comparar vectores vacíos -----------
    cout << "Prueba 3   ";
    TVectorPoro d(5), e;
    if (d == e) {
        cout << "ERROR! ❌ (Los vectores no deberían ser iguales)" << endl;
        resultado = true;
    } else {
        cout << "EXITO!" << endl;
    }

    // ----------- Prueba 4: Asignación de elementos -----------
    cout << "Prueba 4   ";
    TPoro p(1, 2, 3, "rojo");
    TVectorPoro f(5);
    f[1] = p; f[2] = p; f[3] = p; f[4] = p; f[5] = p;

    ostringstream output4;
    output4 << f;
    string esperado4 = "[1 (1, 2) 3.00 rojo 2 (1, 2) 3.00 rojo 3 (1, 2) 3.00 rojo 4 (1, 2) 3.00 rojo 5 (1, 2) 3.00 rojo]";

    if (output4.str() == esperado4) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌" << endl << "    EXPECTED: " << esperado4 << endl << "    OBTAINED: " << output4.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 5: Copia de vectores -----------
    cout << "Prueba 5   ";
    TVectorPoro g(5), h;
    g[1] = p; g[2] = p; g[3] = p; g[4] = p; g[5] = p;
    h = g;

    ostringstream output5a, output5b;
    output5a << g;
    output5b << h;

    if (output5a.str() == output5b.str()) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Output: " << output5a.str() << " vs " << output5b.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 6: Cantidad de elementos ocupados -----------
    cout << "Prueba 6   ";
    TVectorPoro i(5);
    if (i.Cantidad() == 0) {
        i[1] = p;
        if (i.Cantidad() == 1) {
            i[2] = p;
            if (i.Cantidad() == 2) {
                cout << "EXITO!" << endl;
            } else {
                cout << "ERROR! ❌ Cantidad incorrecta1" << endl;
                resultado = true;
            }
        } else {
            cout << "ERROR! ❌ Cantidad incorrecta2" << endl;
            resultado = true;
        }
    } else {
        cout << "ERROR! ❌ Cantidad incorrecta3" << endl;
        resultado = true;
    }

    // ----------- Prueba 7: Redimensionar vector -----------
    
    // Caso 1: Redimensionar con tamaño <= 0 (debe devolver false)
    TVectorPoro v1(5);
    bool res1 = v1.Redimensionar(0);
    ostringstream output3;
    output3 << v1;
    if (!res1) {
        cout << "Prueba 7a   EXITO!" << endl;
    } else {
        cout << "Prueba 7a   ERROR! ❌" << endl;
        resultado = true;
    }

    // Caso 2: Redimensionar con el mismo tamaño (debe devolver false)
    TVectorPoro v2(5);
    bool res2 = v2.Redimensionar(5);
    ostringstream output5;
    output5 << v2;
    if (!res2) {
        cout << "Prueba 7b   EXITO!" << endl;
    } else {
        cout << "Prueba 7b   ERROR! ❌" << endl;
        resultado = true;
    }

    // Caso 3: Redimensionar a un tamaño mayor (debe devolver true y conservar los elementos)
    TVectorPoro v3(3);
    TPoro pp(1, 1, 1.0);
    v3[1] = pp; v3[2] = pp; v3[3] = pp;
    bool res3 = v3.Redimensionar(5);
    ostringstream output3a, output3b;
    output3a << v3;
    
    TVectorPoro expected3(5);
    expected3[1] = pp; expected3[2] = pp; expected3[3] = pp;
    output3b << expected3;

    if (res3 && output3a.str() == output3b.str()) {
        cout << "Prueba 7c   EXITO!" << endl;
    } else {
        cout << "Prueba 7c   ERROR! ❌ Output: " << output3a.str() << " vs " << output3b.str() << endl;
        resultado = true;
    }

    // Caso 4: Redimensionar a un tamaño menor (debe devolver true y eliminar los últimos elementos)
    TVectorPoro v4(5);
    v4[1] = p; v4[2] = p; v4[3] = p; v4[4] = p; v4[5] = p;
    bool res4 = v4.Redimensionar(3);
    ostringstream output4a, output4b;
    output4a << v4;

    TVectorPoro expected4(3);
    expected4[1] = p; expected4[2] = p; expected4[3] = p;
    output4b << expected4;

    if (res4 && output4a.str() == output4b.str()) {
        cout << "Prueba 7d   EXITO!" << endl;
    } else {
        cout << "Prueba 7d   ERROR! ❌ Output: " << output4a.str() << " vs " << output4b.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 8: Comparar longitud tras asignación -----------
    cout << "Prueba 8   ";
    TVectorPoro k(5), l;
    l = k;
    if (k.Longitud() == l.Longitud()) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Longitudes distintas tras asignación" << endl;
        resultado = true;
    }

    return resultado;
}

bool pruebasTListaPoro() {
    bool resultado = false;

    // ----------- Prueba 1: Longitud de listas vacías -----------
    cout << "Prueba 1   ";
    TListaPoro a, b, c;
    
    if (a.Longitud() == 0 && b.Longitud() == 0 && c.Longitud() == 0) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Longitudes incorrectas: " << a.Longitud() << ", " << b.Longitud() << ", " << c.Longitud() << "" << endl;
        resultado = true;
    }

    // ----------- Prueba 2: Insertar elementos y verificar longitud -----------
    cout << "Prueba 2   ";
    TPoro p(1, 1, 1), q(2, 2, 2), r(3, 3, 3);
    
    a.Insertar(p);
    b.Insertar(p); b.Insertar(q);
    c.Insertar(p); c.Insertar(q); c.Insertar(r);

    if (a.Longitud() == 1 && b.Longitud() == 2 && c.Longitud() == 3) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Longitudes incorrectas: " << a.Longitud() << ", " << b.Longitud() << ", " << c.Longitud() << "" << endl;
        resultado = true;
    }

    // ----------- Prueba 3: Imprimir lista vacía -----------
    cout << "Prueba 3   ";
    TListaPoro d;
    ostringstream output3;
    output3 << d;

    if (output3.str() == "()") {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Output incorrecto: " << output3.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 4: Comparar listas vacías e iguales -----------
    cout << "Prueba 4   ";
    TListaPoro e;
    if (d == e) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Listas vacías deberían ser iguales" << endl;
        resultado = true;
    }

    // ----------- Prueba 5: Comparar listas con elementos distintos -----------
    cout << "Prueba 5   ";
    a.Insertar(q);
    if (a == b) {
        cout << "ERROR! ❌ Listas con elementos distintos no deberían ser iguales" << endl;
        resultado = true;
    } else {
        cout << "EXITO!" << endl;
    }

    // ----------- Prueba 6: Insertar elementos ordenados y verificar salida -----------
    cout << "Prueba 6   ";
    TListaPoro f;
    f.Insertar(p); f.Insertar(q); f.Insertar(r);
    ostringstream output6;
    output6 << f;

    string esperado6 = "((1, 1) 1.00 - (2, 2) 2.00 - (3, 3) 3.00 -)";

    if (output6.str() == esperado6) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Lista desordenada o con mal formato: " << output6.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 7: Copia de lista -----------
    cout << "Prueba 7   ";
    TListaPoro g;
    g = f;

    ostringstream output7a, output7b;
    output7a << f;
    output7b << g;

    if (output7a.str() == output7b.str()) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ La copia no es idéntica: " << output7a.str() << " vs " << output7b.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 8: Borrar elementos de la lista -----------
    cout << "Prueba 8   ";
    f.Borrar(p);
    ostringstream output8;
    output8 << f;

    string esperado8 = "((2, 2) 2.00 - (3, 3) 3.00 -)";

    if (output8.str() == esperado8 && !f.Buscar(p)) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Error al borrar: " << output8.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 9: Buscar elementos en la lista -----------
    cout << "Prueba 9   ";
    if (f.Buscar(q) && !f.Buscar(p)) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Búsqueda incorrecta" << endl;
        resultado = true;
    }

    cout << "Las pruebas 10 y 11 no están correctamente implementadas!!!" << endl;

    /*// ----------- Prueba 10: Recorrer lista hacia adelante -----------
    cout << "Prueba 10   ";
    ostringstream output10;
    TListaPosicion pos = f.Primera();
    
    while (!pos.EsVacia()) {
        output10 << f.Obtener(pos) << " ";
        pos = pos.Siguiente();
    }

    string esperado10 = "(2, 2) 2.00 - (3, 3) 3.00 - ";

    if (output10.str() == esperado10) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Recorrido incorrecto: " << output10.str() << endl;
        resultado = true;
    }

    // ----------- Prueba 11: Recorrer lista hacia atrás -----------
    cout << "Prueba 11   ";
    ostringstream output11;
    pos = f.Ultima();
    
    while (!pos.EsVacia()) {
        output11 << f.Obtener(pos) << " ";
        pos = pos.Anterior();
    }

    string esperado11 = "(3, 3) 3.00 - (2, 2) 2.00 - ";

    if (output11.str() == esperado11) {
        cout << "EXITO!" << endl;
    } else {
        cout << "ERROR! ❌ Recorrido incorrecto: " << output11.str() << endl;
        resultado = true;
    }*/

    return resultado;
}

int main() {
    cout << "PROBANDO EL PROGRAMA DEL CUADERNILLO 1" << endl << endl;

    cout << "Actualmente probando TPoro..." << endl;
    if (!pruebasTPoro()) cout << "Todas las pruebas de TPoro funcionan ✅" << endl; else cout << "Algunas pruebas fallaron ❌" << endl;
    
    cout << endl << "Actualmente probando TVectorPoro..." << endl;
    if (!pruebasTVectorPoro()) cout << "Todas las pruebas de TVectorPoro funcionan ✅" << endl; else cout << "Algunas pruebas fallaron ❌" << endl;
    
    cout << endl << "Actualmente probando TListaPoro..." << endl;
    if (!pruebasTListaPoro()) cout << "Todas las pruebas de TListaPoro funcionan ✅" << endl; else cout << "Algunas pruebas fallaron ❌" << endl;
    
    return 0;
}
