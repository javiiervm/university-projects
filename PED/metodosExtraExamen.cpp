
// MÉTODOS EXTRA DE EXAMEN PARA EL CUADERNILLO DE TPORO

#include "tabbporo.h"
#include "tlistaporo.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

// 1. Recorrido zig-zag (niveles alternando dirección)
TVectorPoro TABBPoro::ZigZag() {
    TVectorPoro res;
    if (EsVacio()) return res;

    std::queue<TABBPoro*> q;
    q.push(this);
    int nivel = 0;
    std::vector<TPoro> temporal;

    while (!q.empty()) {
        int size = q.size();
        temporal.clear();

        for (int i = 0; i < size; i++) {
            TABBPoro* actual = q.front(); q.pop();

            if (!actual->EsVacio()) {
                temporal.push_back(actual->Raiz());
                if (!actual->nodo->iz.EsVacio()) q.push(&(actual->nodo->iz));
                if (!actual->nodo->de.EsVacio()) q.push(&(actual->nodo->de));
            }
        }

        if (nivel % 2 == 1)
            std::reverse(temporal.begin(), temporal.end());

        int posIni = res.Longitud();
        TVectorPoro nuevo(posIni + temporal.size());
        for (int i = 1; i <= res.Longitud(); i++) nuevo[i] = res[i];
        for (size_t i = 0; i < temporal.size(); i++) nuevo[posIni + i + 1] = temporal[i];
        res = nuevo;
        nivel++;
    }

    return res;
}

// 2. Comprobar si dos ABB tienen la misma estructura
bool TABBPoro::MismaEstructura(TABBPoro &otro) {
    if (EsVacio() && otro.EsVacio()) return true;
    if (EsVacio() || otro.EsVacio()) return false;
    return nodo->iz.MismaEstructura(otro.nodo->iz) && nodo->de.MismaEstructura(otro.nodo->de);
}

// 3. Eliminar nodos con volumen menor que un valor dado
void TABBPoro::EliminarPorVolumenMenorQue(double v) {
    if (EsVacio()) return;
    nodo->iz.EliminarPorVolumenMenorQue(v);
    nodo->de.EliminarPorVolumenMenorQue(v);
    if (nodo->item.Volumen() < v) Borrar(nodo->item);
}

// 4. Contar poros por color
int TABBPoro::ContarPorColor(const char *color) {
    if (EsVacio()) return 0;
    int cuenta = 0;
    if (nodo->item.Color() != NULL && strcmp(nodo->item.Color(), color) == 0) cuenta = 1;
    return cuenta + nodo->iz.ContarPorColor(color) + nodo->de.ContarPorColor(color);
}

// 5. Profundidad de un TPoro en el árbol
int TABBPoro::ProfundidadDe(TPoro &p) {
    if (EsVacio()) return -1;
    if (Raiz() == p) return 0;
    int izq = nodo->iz.ProfundidadDe(p);
    if (izq != -1) return izq + 1;
    int der = nodo->de.ProfundidadDe(p);
    if (der != -1) return der + 1;
    return -1;
}

// 6. Comprobar si el árbol es completo (completo por niveles)
bool TABBPoro::EsCompleto() {
    if (EsVacio()) return true;
    std::queue<TABBPoro*> q;
    q.push(this);
    bool encontradoHueco = false;

    while (!q.empty()) {
        TABBPoro* actual = q.front(); q.pop();
        if (actual->EsVacio()) {
            encontradoHueco = true;
        } else {
            if (encontradoHueco) return false;
            q.push(&(actual->nodo->iz));
            q.push(&(actual->nodo->de));
        }
    }

    return true;
}

// 7. Obtener mínimo TPoro (por volumen)
TPoro TABBPoro::Minimo() {
    if (EsVacio()) return TPoro();
    TABBPoro *actual = this;
    while (!actual->nodo->iz.EsVacio()) actual = &(actual->nodo->iz);
    return actual->Raiz();
}

// 8. Obtener máximo TPoro (por volumen)
TPoro TABBPoro::Maximo() {
    if (EsVacio()) return TPoro();
    TABBPoro *actual = this;
    while (!actual->nodo->de.EsVacio()) actual = &(actual->nodo->de);
    return actual->Raiz();
}

// 9. Comprobar si el árbol es un ABB balanceado (AVL-like)
bool TABBPoro::EsBalanceado() {
    if (EsVacio()) return true;
    int altIz = nodo->iz.Altura();
    int altDe = nodo->de.Altura();
    int dif = abs(altIz - altDe);
    return dif <= 1 && nodo->iz.EsBalanceado() && nodo->de.EsBalanceado();
}

// 10. Número total de caminos de raíz a hoja
int TABBPoro::CaminosDeRaizAHoja() {
    if (EsVacio()) return 0;
    if (nodo->iz.EsVacio() && nodo->de.EsVacio()) return 1;
    return nodo->iz.CaminosDeRaizAHoja() + nodo->de.CaminosDeRaizAHoja();
}

// 11. Convertir ABB a AVL (reestructuración equilibrada por inorden)
void TABBPoro::ConvertirAAvl() {
    TVectorPoro inorden = Inorden();
    *this = TABBPoro(); // vaciar el árbol actual
    ConstruirAVL(inorden, 1, inorden.Longitud());
}

void TABBPoro::ConstruirAVL(const TVectorPoro &v, int ini, int fin) {
    if (ini > fin) return;
    int mid = (ini + fin) / 2;
    Insertar(v[mid]);
    ConstruirAVL(v, ini, mid - 1);
    ConstruirAVL(v, mid + 1, fin);
}

// 12. Reequilibrar solo si no está balanceado
void TABBPoro::ReequilibrarSiNecesario() {
    if (!EsBalanceado()) {
        ConvertirAAvl();
    }
}

// 13. InsertarExamen: inserta y devuelve tipo de inserción por referencia
bool TABBPoro::InsertarExamen(TPoro &p, int &tipoInsercion) {
    if (p.EsVacio()) return false;
    if (EsVacio()) {
        nodo = new TNodoABB();
        nodo->item = p;
        tipoInsercion = 0;
        return true;
    }
    if (p == nodo->item) return false;
    if (p.Volumen() < nodo->item.Volumen()) {
        bool ok = nodo->iz.InsertarExamen(p, tipoInsercion);
        if (ok) tipoInsercion = -1;
        return ok;
    } else {
        bool ok = nodo->de.InsertarExamen(p, tipoInsercion);
        if (ok) tipoInsercion = +1;
        return ok;
    }
}

// 14. Clasificar por tipo de inserción desde un vector
void TABBPoro::Clasificar(TVectorPoro V, TListaPoro &L1, TListaPoro &L2, TListaPoro &L3) {
    for (int i = 1; i <= V.Longitud(); i++) {
        TPoro p = V[i];
        if (p.EsVacio()) continue;
        int tipo = 0;
        if (InsertarExamen(p, tipo)) {
            if (tipo == 0) L1.Insertar(p);
            else if (tipo == -1) L2.Insertar(p);
            else if (tipo == +1) L3.Insertar(p);
        }
    }
}

// 15. TListaPoro - Eliminar poros con volumen mayor que un valor dado
void TListaPoro::EliminarMayores(double volumenLimite) {
    TListaPosicion it = Primera();
    while (!it.EsVacia()) {
        TPoro p = Obtener(it);
        TListaPosicion siguiente = it.Siguiente();
        if (p.Volumen() > volumenLimite)
            Borrar(p);
        it = siguiente;
    }
}

// 16. TListaPoro - Intersección con otra lista
TListaPoro TListaPoro::Interseccion(const TListaPoro &otra) const {
    TListaPoro resultado;
    TListaPosicion it = Primera();
    while (!it.EsVacia()) {
        TPoro p = Obtener(it);
        if (otra.Buscar(p)) resultado.Insertar(p);
        it = it.Siguiente();
    }
    return resultado;
}

// 17. TListaPoro - Unión sin duplicados
TListaPoro TListaPoro::Union(const TListaPoro &otra) const {
    TListaPoro resultado = *this;
    TListaPosicion it = otra.Primera();
    while (!it.EsVacia()) {
        TPoro p = otra.Obtener(it);
        if (!resultado.Buscar(p)) resultado.Insertar(p);
        it = it.Siguiente();
    }
    return resultado;
}

// 18. TListaPoro - Invertir lista
void TListaPoro::Invertir() {
    TListaPoro invertida;
    TListaPosicion it = Ultima();
    while (!it.EsVacia()) {
        invertida.Insertar(Obtener(it));
        it = it.Anterior();
    }
    *this = invertida;
}

// 19. TListaPoro - Comprobar si es palíndroma por volumen
bool TListaPoro::EsPalindroma() const {
    std::vector<double> vols;
    TListaPosicion it = Primera();
    while (!it.EsVacia()) {
        vols.push_back(Obtener(it).Volumen());
        it = it.Siguiente();
    }
    for (size_t i = 0; i < vols.size() / 2; i++) {
        if (vols[i] != vols[vols.size() - 1 - i]) return false;
    }
    return true;
}

// 20. TListaPoro - Eliminar duplicados consecutivos
void TListaPoro::EliminarDuplicadosConsecutivos() {
    TListaPosicion it = Primera();
    while (!it.EsVacia() && !it.Siguiente().EsVacia()) {
        TPoro actual = Obtener(it);
        TPoro siguiente = Obtener(it.Siguiente());
        if (actual == siguiente)
            Borrar(siguiente);
        else
            it = it.Siguiente();
    }
}

// 21. TABBPoro - Comprobar si todos los nodos tienen exactamente dos hijos o ninguno
bool TABBPoro::EsEstricto() {
    if (EsVacio()) return true;
    bool izVacio = nodo->iz.EsVacio();
    bool deVacio = nodo->de.EsVacio();
    if ((izVacio && !deVacio) || (!izVacio && deVacio)) return false;
    return nodo->iz.EsEstricto() && nodo->de.EsEstricto();
}

// 22. TListaPoro - Reordenar la lista por volumen (orden creciente)
void TListaPoro::OrdenarPorVolumen() {
    std::vector<TPoro> poros;
    TListaPosicion it = Primera();
    while (!it.EsVacia()) {
        poros.push_back(Obtener(it));
        it = it.Siguiente();
    }
    std::sort(poros.begin(), poros.end(), [](const TPoro &a, const TPoro &b) {
        return a.Volumen() < b.Volumen();
    });
    *this = TListaPoro();
    for (const auto &p : poros) Insertar(p);
}

// 23. TABBPoro - Comparar dos árboles (igual estructura y mismos poros)
bool TABBPoro::EsIgual(const TABBPoro &otro) const {
    if (EsVacio() && otro.EsVacio()) return true;
    if (EsVacio() || otro.EsVacio()) return false;
    if (!(Raiz() == otro.Raiz())) return false;
    return nodo->iz.EsIgual(otro.nodo->iz) && nodo->de.EsIgual(otro.nodo->de);
}

// 24. TListaPoro - Duplicar cada elemento (ej: <1,2> → <1,1,2,2>)
void TListaPoro::DuplicarElementos() {
    TListaPosicion it = Primera();
    while (!it.EsVacia()) {
        TPoro p = Obtener(it);
        Insertar(p);
        it = it.Siguiente().Siguiente(); // saltar el duplicado
    }
}
