#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

void cache(int cache,int tbloque,int tconjunto);
void cache_directa(int bloqCache, int tbloque);
void cache_conjuntos(int bloqCache,int tbloque, int tconjunto);
void cache_asociativa(int bloqCache,int tbloque);

#endif  // CACHE_H