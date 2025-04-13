/*
  Biblioteca define funcoes e estruturas de dados
  para identificacao de poligonos e pontos
  Criado por Davi Garcia Lazzarin e Matheus Telles Batista
  Data: 07/04/25
*/

#include <vector>
#include "geometry.cpp"

#ifndef _POLIGONO_
#define _POLIGONO_

enum tipo_p{SEM_TIPO, CONVEXO, NAO_CONVEXO, NAO_SIMPLES };

template <typename T> struct ponto {
  T x, y; 
};

template <typename T> struct aresta{
  ponto<T> ini, fim; 
};

template <typename T> struct poligono{
  std::vector<ponto<T>> vertices;
  tipo_p tipo{SEM_TIPO};
};

//coverte poligono de vertices para poligono de arestas
template <typename T> vector<aresta<T>> converte_poligono(const poligono<T>& pol) {
  
  vector<aresta<T>> novo_pol;
  auto n = pol.vertices.size();
  for(int i=0; i < n; i++ ){  
    aresta<T> ar;
    ar.ini = pol.vertivces[i];
    ar.ini = pol.vertices[(i+1) % n];
    novo_pol.push_back(ar);
  }
  return novo_pol;
}

// Verifica se o poligono eh simples
template <typename T> bool ehSimplesBF(const poligono<T>& pol) {

  vector<aresta<T>> arestas = converte_poligono(pol);
	for(int i = 0; i < arestas.size(); ++i) {
		for(int j = i + 1; j < arestas.size(); ++j) {
			aresta<T> intersecao;
			if(temIntersecao(arestas[i], arestas[j], &intersecao)) 
				return false;
			
		}
	}
	return true;
}

template <typename T> int tipo_poligono(const poligono<T>& pol){

  const auto& v = pol.vertices;
  int n = pol.vertices.size();
  
  if (n < 3) return SEM_TIPO;

  if (!eh_simplesBF(pol)) return NAO_SIMPLES;

  int sinal = 0;

  for (int i = 0; i < n; i++) {
    //define os 3 vertices (2 arestas)
    const ponto<T>& A = v[i];
    const ponto<T>& B = v[(i + 1) % n];
    const ponto<T>& C = v[(i + 2) % n];

    //pega o sinal do angulo em B
    T aux = (B.x - A.x)*(C.y - B.y) - (B.y - A.y)*(C.x - B.x); 

    if (aux != 0) { //se for 0 estao alinhados numa reta
      int novo_sinal = (aux > 0) ? 1 : -1;
      
      if (sinal == 0) //primeira exec
        sinal = novo_sinal;
      else
        if (sinal != novo_sinal) // se o sinal mudou e nao convexo
          return NAO_CONVEXO;  
    }
  }

  return CONVEXO;
}//fim tipo_poligono

#endif