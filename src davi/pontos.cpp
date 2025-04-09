#include "pontos.hpp"

// Funcao recebe um poligono e um ponto , retorna todos os segmentos de reta
// que podem intersectar uma semireta partindo do ponto (x,y) ate (max_x+10,y)
template <typename T> raycasting<T> ray_processa(poligono<T> pol, ponto<T> pon){

}

template <typename T> int num_interseccao(raycasting<T> conjunto_sr, ponto<T> pon){

}

// recebe duas semiretas e retorna true se elas se intersectam e false caso nao
// aresta_pol e uma das arestas do poligono
// sr e a semi reta tracada do ponto ate um ponto certamente fora do poligono 
template <typename T> bool intersecta(aresta<T> aresta_pol, aresta<T> sr){

}

// Essa funcao e chamada quando se sabe que o ponto e colinear e nao paralelo com sr
// Verifica se o ponto esta entre as pontas da aresta 
template <typename T> bool ponto_na_aresta(ponto<T> p, aresta<T> sr) {
  
  // Teste de colinearidade: produto vetorial
  T cross = (sr.x - sr.x)*(p.y - sr.y) - (sr.y - sr.y)*(p.x - sr.x);
  
  if (std::abs(cross) > EPS) return false;

  // Testa se está entre os extremos
  return std::min(a.x, b.x) - EPS <= p.x && p.x <= std::max(a.x, b.x) + EPS &&
         std::min(a.y, b.y) - EPS <= p.y && p.y <= std::max(a.y, b.y) + EPS;
}