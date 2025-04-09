#include "pontos.hpp"

// Verifica se o ponto esta entre as pontas da aresta 
template <typename T> bool ponto_na_aresta(const ponto<T> p, const aresta<T> sr) {
  
  // Verifica se e colinear 
  T aux = (sr.fim.x - sr.ini.x)*(p.y - sr.ini.y) - (sr.fim.y - sr.ini.y)*(p.x - sr.ini.x);
  
  // Se nao for colinear retorna falso
  if (std::abs(aux) > EPS) return false; 

  // Testa se está entre os extremos, ja que nesse caso nao pode ser paralelo 
  // Verifica se o ponto esta dentro do "quadrado" do qual a aresta eh diagonal principal
  return std::min(sr.ini.x, sr.fim.x) - EPS <= p.x && p.x <= std::max(sr.ini.x, sr.fim.x) + EPS &&
         std::min(sr.ini.y, sr.fim.y) - EPS <= p.y && p.y <= std::max(sr.ini.y, sr.fim.y) + EPS;
}

// Funcao principal do raycasting
// Recebe o poligono e o ponto, retorna se esta dentro do poligono ou nao
template <typename T> bool raycast(const ponto<T> p, const poligono<T>& pol) {
  
  int n = pol.vertices.size(); //tamanho do poligono
  int cruzamentos = 0;     //contagem de cruzamentos

  for (int i = 0; i < n; i++) {
    aresta<T> sr;
    sr.ini = pol.vertices[i];
    sr.fim = pol.vertices[(i + 1) % n];
    
    // Ponto sobre a aresta
    if (ponto_na_aresta(p, sr)) return true;

    // Ignora arestas horizontais
    if (std::abs(sr.ini.y - sr.fim.y) < EPS) continue;

    // Garante que o inicio da semireta esta sempre "abaixo" do fim
    if (sr.ini.y > sr.fim.y) std::swap(sr.ini, sr.fim);


    // Verifica se a semi reta cruza a aresta
    // ponto esta entre os limites sup e inf da sr no eixo y 
    if (p.y > sr.ini.y - EPS && p.y < sr.fim.y - EPS) { 
      
      // Acha o ponto x em que a reta horizontal do ponto cruza a sr
      double x_intersecao = (double)(sr.fim.x - sr.ini.x) * (p.y - sr.ini.y) / (sr.fim.y - sr.ini.y) + sr.ini.x; 
      
      // Falta um caso especial onde essa reta passa em cima de um vertice

      //Como a reta vai do ponto para a direita, se tiver a esqueda nao conta, estar em cima ja foi tratado
      if (x_intersecao > p.x + EPS)
        cruzamentos++;
    }
  }

  // Retorna true se impar, false se par
  return cruzamentos % 2 == 1; 
}