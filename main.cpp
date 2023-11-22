#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "libs/cache.h"

using namespace std;

int main(int argc, char * argv[]) {
    int sizeCache;
    int sizeBloque;
    int sizeConjunto;
    
    // Preguntas al usuario para obtener información sobre la memoria caché
    cout << "Tamanio de la cache (Kb): ";            cin >> sizeCache;
    cout << "Tamanio de los bloques (palabras): ";   cin >> sizeBloque;
    cout << "Tamanio de los conjuntos (bloques): ";  cin >> sizeConjunto;

    // Llamada a la función `cache` del archivo `cache.cpp` con los parámetros proporcionados por el usuario
    cache(sizeCache * 1024, sizeBloque, sizeConjunto);
    
    // Fin del programa
    return 0;
}