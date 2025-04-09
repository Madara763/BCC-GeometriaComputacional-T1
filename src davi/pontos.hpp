/*
  Biblioteca define funcoes e estruturas de dados
  para identificacao de poligonos e pontos
  Criado por Davi Garcia Lazzarin 
  Data: 07/04/25
*/

#ifndef _POLIGONOS_
#define _POLIGONOS_

#include <cstdlib>
#include <vector>
#include <list>

template <typename T> struct ponto {
  T x, y;
};

template <typename T> struct aresta{
  ponto<T> ini, fim; 
};

template <typename T> struct poligono{
  std::vector<ponto<T>> vertices;
};

// Por padrao definiremos as semi retas (sr) tendo 
// sempre o ponto ini como o menor y e o fim com o maior y
// como se fosse "de baixo para cima"
template <typename T> struct raycasting{
  poligono<T> sr;
  T min_x, max_x;
};

// ============================= Funcoes usadas no RayCasting =============================

// Verifica se o ponto esta entre as pontas da aresta 
template <typename T> bool ponto_na_aresta(const ponto<T> p, const aresta<T> sr);

// Funcao principal do raycasting
// Recebe o poligono e o ponto, retorna se esta dentro do poligono ou nao
template <typename T> bool raycast(const ponto<T> p, const poligono<T>& pol);

#endif 