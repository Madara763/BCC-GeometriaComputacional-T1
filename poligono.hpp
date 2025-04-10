/*
  Biblioteca define funcoes e estruturas de dados
  para identificacao de poligonos e pontos
  Criado por Davi Garcia Lazzarin 
  Data: 07/04/25
*/

#include <vector>

#ifndef _POLIGONO_
#define _POLIGONO_

template <typename T> struct ponto {
  T x, y; 
};

template <typename T> struct aresta{
  ponto<T> ini, fim; 
};

template <typename T> struct poligono{
  std::vector<ponto<T>> vertices;
};

#endif