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
  std::vector<aresta<T>> arestas;
};

// Por padrao definiremos as semi retas (sr) tendo 
// sempre o ponto ini como o menor y e o fim com o maior y
// como se fosse "de baixo para cima"
template <typename T> struct raycasting{
  std::vector<aresta<T>> sr;
  T min_x, max_x;
};

// Funcao recebe um poligono e um ponto , retorna todos os segmentos de reta
// que podem intersectar uma semireta partindo do ponto (x,y) ate (max_x+10,y)
template <typename T> raycasting<T> ray_processa(poligono<T> pol, ponto<T> pon);

template <typename T> int num_interseccao(raycasting<T> conjunto_sr, ponto<T> pon);

// recebe duas semiretas e retorna true se elas se intersectam e false caso nao
// aresta_pol e uma das arestas do poligono
// sr e a semi reta tracada do ponto ate um ponto certamente fora do poligono 
template <typename T> bool intersecta(aresta<T> aresta_pol, aresta<T> sr); 

#endif 