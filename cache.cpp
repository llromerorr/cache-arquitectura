#include "libs/cache.h"
#include <algorithm>

using namespace std;

const int memory_direction[] = {6, 214, 175, 214, 6, 84, 65, 174, 64, 105, 85, 215};
const int memory_direction_size = 12;

void cache(int cache, int tbloque, int tconjunto)
{
    int palabras;
    int bloques;
    float auxiliar;

    // Ajusta el tamaño del bloque al siguiente número de potencia de 2
    auxiliar = log2(tbloque);
    auxiliar = ceil(auxiliar);
    tbloque = pow(2, auxiliar);

    // Calcula el número de palabras y bloques en la caché
    palabras = cache / 4;
    bloques = palabras / tbloque;

    // Muestra información sobre el tamaño de las palabras y bloques
    cout << "\nPalabras: " << palabras << endl;
    cout << "Bloques: " << bloques;

    // Llama a las funciones de caché específicas según el tipo de caché
    cache_directa(bloques, tbloque);
    cache_asociativa(bloques, tbloque);
    cache_conjuntos(bloques, tbloque, tconjunto);
}

void cache_directa(int bloqCache, int tbloque)
{
    vector<int> cache(bloqCache);  // Vector para almacenar las etiquetas de los bloques en la caché
    int despBloque = log2(tbloque); // Desplazamiento necesario para obtener el índice del bloque en la caché
    int indice;
    int etiqueta;
    int instruccion;
    int error = 0;

    cout << "\n\n--------------------------------------------------" << endl;
    cout << "                    CACHE DIRECTA";
    cout << "\n--------------------------------------------------" << endl;

    printf("%-12s%-12s%-12s%-12s\n", "DIRECCION", "ETIQUETA", "INDICE", "RESULTADO");

    // Limpiar la caché
    for (int i = 0; i < bloqCache; i++)
        cache[i] = -1;

    // Iterar sobre las instrucciones de memoria
    for (int i = 0; i < memory_direction_size; i++)
    {
        instruccion = memory_direction[i];
        etiqueta = instruccion >> despBloque;
        indice = etiqueta % bloqCache;
        bool esError = false;

        // Verificar si hay un error de caché
        if (cache[indice] != etiqueta)
        {
            cache[indice] = etiqueta;
            error++;
            esError = true;
        }

        // Mostrar la tabla de resultados
        printf("%-12d%-12d%-12d%-12s\n", instruccion, etiqueta, indice, (esError) ? "Acierto" : "Error");
    }

    // Mostrar estadísticas de fallos
    printf("\n%-12s%-12s%-12s%-12d\n", "", "", "FALLOS:", error);
    printf("%-12s%-12s%-12s%-12d\n", "", "", "POSICIONES:", bloqCache);
}

void cache_conjuntos(int bloqCache, int tbloque, int tconjunto)
{
    vector<vector<int>> vecConjunto(bloqCache / tconjunto);  // Vector de vectores para simular caché por conjuntos
    int conjuntos = bloqCache / tconjunto;
    int despBloque = log2(tbloque);

    int etiqueta;
    int indiceConjunto;
    int instruccion;
    int error = 0;

    cout << "\n--------------------------------------------------" << endl;
    cout << "                 CACHE POR CONJUNTOS";
    cout << "\n--------------------------------------------------" << endl;

    printf("%-12s%-12s%-12s%-12s\n", "DIRECCION", "ETIQUETA", "INDICE", "RESULTADO");

    // Iterar sobre las instrucciones de memoria
    for (int i = 0; i < memory_direction_size; i++)
    {
        instruccion = memory_direction[i];
        etiqueta = instruccion >> despBloque;
        indiceConjunto = etiqueta % conjuntos;

        auto it = find((vecConjunto[indiceConjunto]).begin(), (vecConjunto[indiceConjunto]).end(), etiqueta);

        int tipoResultado = 0;

        // Verificar si hay un error en el conjunto
        if (it != vecConjunto[indiceConjunto].end())
        {
            vecConjunto[indiceConjunto].erase(it);
            vecConjunto[indiceConjunto].insert(vecConjunto[indiceConjunto].begin(), etiqueta);
        }
        else if (vecConjunto[indiceConjunto].size() < static_cast<size_t>(tconjunto))
        {
            tipoResultado = 1;
            vecConjunto[indiceConjunto].push_back(etiqueta);
            error++;
        }
        else
        {
            tipoResultado = 2;
            vecConjunto[indiceConjunto].pop_back();
            vecConjunto[indiceConjunto].insert(vecConjunto[indiceConjunto].begin(), etiqueta);
            error++;
        }

        // Mostrar la tabla de resultados
        printf("%-12d%-12d%-12d%-12s\n", instruccion, etiqueta, indiceConjunto, (tipoResultado == 0) ? "Acierto" : ((tipoResultado == 1) ? "Error con espacio" : "Error sin espacio"));
    }

    // Mostrar estadísticas de fallos
    printf("\n%-12s%-12s%-12s%-12d\n", "", "", "FALLOS:", error);
    printf("%-12s%-12s%-12s%-12d\n", "", "", "CONJUNTOS:", conjuntos);
}

void cache_asociativa(int bloqCache, int tbloque)
{
    int indice;
    int instruccion;
    int despBloque = log2(tbloque);
    int etiqueta;
    int error = 0;
    vector<int> cola;

    cout << "\n--------------------------------------------------" << endl;
    cout << "                 CACHE POR ASOCIATIVA";
    cout << "\n--------------------------------------------------" << endl;

    printf("%-12s%-12s%-12s\n", "DIRECCION", "ETIQUETA", "RESULTADO");

    // Iterar sobre las instrucciones de memoria
    for (int i = 0; i < memory_direction_size; i++)
    {
        instruccion = memory_direction[i];
        etiqueta = instruccion >> despBloque;
        auto it = find(cola.begin(), cola.end(), etiqueta);
        int tipoResultado = 0;

        // Verificar si hay un error en la caché asociativa
        if (it != cola.end())
        {
            cola.erase(it);
            cola.insert(cola.begin(), etiqueta);
        }
        else if (cola.size() < static_cast<size_t>(bloqCache))
        {
            cola.push_back(etiqueta);
            error++;
            tipoResultado = 1;
        }
        else
        {
            cola.pop_back();
            cola.insert(cola.begin(), etiqueta);
            error++;
            tipoResultado = 2;
        }

        // Mostrar la tabla de resultados
        printf("%-12d%-12d%-12s\n", instruccion, etiqueta, (tipoResultado == 0) ? "Acierto" : ((tipoResultado == 1) ? "Error con espacio" : "Error sin espacio"));
    }

    // Mostrar estadísticas de fallos
    printf("\n%-12s%-12s%-12s%-12d\n", "", "", "FALLOS:", error);
    printf("%-12s%-12s%-12s%-12lu\n", "", "", "TAMANIO:", cola.size());
}