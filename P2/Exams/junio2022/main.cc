#include <iostream>
#include "Producto.h"
#include "Ingrediente.h"
#include "Receta.h"

using namespace std;

int main() {
    Producto *tomate=new Producto("Tomate",180);
    Producto *patata=new Producto("Patata",770);
    Producto *huevo=new Producto("Huevo",1550);

    Receta ensalada("Ensalada murciana");
    ensalada.addIngrediente(patata,0.5);
    ensalada.addIngrediente(tomate,1);
    cout << ensalada << endl;

    Receta tortilla("Tortilla de patatas");
    tortilla.addIngrediente(huevo,0.1);
    tortilla.addIngrediente(patata,0.5);
    cout << tortilla << endl;

    return 0;
}