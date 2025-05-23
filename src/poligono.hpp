/*
  Biblioteca define funcoes e estruturas de dados
  para identificacao de poligonos e pontos
  Criado por Davi Garcia Lazzarin e Matheus Telles Batista
  Data: 07/04/25
*/

#include <vector>
#include <iostream>

#ifndef _POLIGONO_
#define _POLIGONO_

// ====================================== Definicoes ======================================

//Alterar o tipo confome implementacao
const double EPS = 1E-9;

enum tipo_p{SEM_TIPO, CONVEXO, NAO_CONVEXO, NAO_SIMPLES };
enum tipo_interseccao{EM_UM_PONTO, EM_UM_INTERVALO};

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


// ====================================== Auxiliares ======================================

// Realiza a subtracao de dois vetores
template <typename T> ponto<T> sub_point(ponto<T> p1, ponto<T> p2){
  ponto<T> t;
  t.x = p1.x - p2.x;
  t.y = p1.y - p2.y;
  return t;
}

// Realiza a soma de dois vetores
template <typename T> ponto<T> sum_point(ponto<T> p1, ponto<T> p2){
  ponto<T> t;
  t.x = p1.x + p2.x;
  t.y = p1.y + p2.y;
  return t;
}

// Realiza o produto vetorial em R2
template <typename T> T prod_vetorial(ponto<T> a, ponto<T> b){
  return a.x * b.y - b.x * a.y; 
}

// Realiza o produto escalar em R2
template <typename T> T prod_escalar(ponto<T> a, ponto<T> b){
  return a.x * b.x + a.y * b.y;
}

// =============================== Funcoes gerais poligonos ===============================

//coverte poligono de vertices para poligono de arestas
template <typename T> std::vector<aresta<T>> converte_poligono(const poligono<T>& pol) {
  
  std::vector<aresta<T>> novo_pol;
  int n = pol.vertices.size();
  for(int i=0; i < n; i++ ){  
    aresta<T> ar;
    ar.ini = pol.vertices[i];
    ar.fim = pol.vertices[(i+1) % n];
    novo_pol.push_back(ar);
  }
  return novo_pol;
}

// Verifica se dois segmentos se interceptam
// Algoritmo realizado graças a https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect#comment69866544_565282
// obrigado a https://stackoverflow.com/users/68063/gareth-rees
/**
 * @param intersecao valor passado por referencia, caso haja intersecao
 * Verifica se dois segmentos possuem intersecao
 * 1: se intersectam em um ponto apenas
 * 2: se intersectam em um intervalo
 * -1: nao se intersectam
 */
template <typename T> int tem_Intersecao(aresta<T> v, aresta<T> w, aresta<T> *intersecao) {
  ponto<T> p = v.ini;
  ponto<T> q = w.ini;
  ponto<T> r = sub_point(v.fim, p);
  ponto<T> s = sub_point(w.fim, q);
  ponto<T> tr;
  int r2;
  long double t0, t1, u, t, uNum, tNum, denom, t_start, t_end;

  //u = (q − p) × r / (r × s)
  uNum = prod_vetorial(sub_point(q, p), r);

  //t = (q − p) × s / (r × s)
  tNum = prod_vetorial(sub_point(q, p), s);
  denom = prod_vetorial(r, s);

  #ifdef DEBUG        
  std::cout << "p: " << p.x << " " << p.y << "\n";
  std::cout << "q: " << q.x << " " << q.y << "\n";
  std::cout << "r: " << r.x << " " << r.y << "\n";
  std::cout << "s: " << s.x << " " << s.y << "\n";
  std::cout << "denom: " << denom << "\n";
  #endif    
  if(denom == 0 && uNum == 0) {
      // Colineares
      r2 = prod_escalar(r, r);

      // t0 = (q − p) · r / (r · r)
      t0 = prod_escalar(sub_point(q, p),  r) / r2;
      // t1 = (q + s − p) · r / (r · r) 
      t1 = prod_escalar(sub_point(sum_point(q, s), p), r) / r2;

      // se s e r apontam em direcoes opostas, troca t0 e t1
      // se eh oposto, o produto escalar eh negativo
      if (s.x * r.x + s.y * r.y < 0) {
          long double temp = t0;
          t0 = t1;
          t1 = temp;
      }

      // se o intervalo entre t0 e t1 intersecta o intervalo [0, 1], entao os segmentos de reta sao colineares e sobrepostos
      t_start = std::max(std::min(t0, t1), 0.0L);
      t_end = std::min(std::max(t0, t1), 1.0L);
      if(t_start <= t_end) {
          auto start = sum_point(p, {static_cast<double>(t_start * r.x), static_cast<double>(t_start * r.y)});
          auto end = sum_point(p, {static_cast<double>(t_end * r.x), static_cast<double>(t_end * r.y)});
          #ifdef DEBUG
          std::cout << "Colineares e coincidentes entre (" << start.x << "," << start.y << ") e (" << end.x << "," << end.y << ")\n"; 
          #endif
          intersecao->ini = start;
          intersecao->fim = end;

          if(t_start == t_end) return 1;
          
          return 2;
      } 
      else { // colineares e disjuntos
          #ifdef DEBUG
          std::cout << "Colineares e disjuntos" << "\n";
          #endif
          return -1;
      }
  } 
  //r × s = 0 and (q − p) × r ≠ 0: paralelas e nao coincidentes
  else if(denom == 0 && prod_vetorial(sub_point(q, p) , r) != 0) {
      #ifdef DEBUG
      std::cout << "Paralelas e nao coincidentes" << "\n";
      #endif
      return -1;
  }
  // r × s ≠ 0 e 0 ≤ t ≤ 1 e 0 ≤ u ≤ 1
  // se encontram em um point
  else if (denom != 0){
      u = uNum / denom;
      t = tNum / denom;
      
      #ifdef DEBUG        
      std::cout << "uNum: " << uNum << "\n";
      std::cout << "tNum: " << tNum << "\n";
      std::cout << "u: " << u << "\n";
      std::cout << "t: " << t << "\n";
      #endif

      //se intersectam no point p + t r 
      tr = {static_cast<double>(t * r.x), static_cast<double>(t * r.y)};

      if(u >= 0 && u <= 1 && t >= 0 && t <= 1) {
        ponto<T> pInt = sum_point(p, tr);
          #ifdef DEBUG
          std::cout << "Se intersectam em (" << pInt.x << "," << pInt.y << ")\n";
          #endif
          intersecao->ini = pInt;

          return 1;
      }
  }

  return false;
}

//Verifica se o poligono eh simples
template <typename T> bool eh_simplesBF(const poligono<T>& pol) {

  std::vector<aresta<T>> arestas = converte_poligono(pol);

  for(int i = 0; i < static_cast<int>( arestas.size() ); ++i) {
    for(int j = i + 1; j < static_cast<int>( arestas.size()); ++j) {

      aresta<T> intersecao;
      if((j == i + 1) || (i == 0 && j == static_cast<int> (arestas.size() - 1))){
        if(tem_Intersecao(arestas[i], arestas[j], &intersecao) == 2) 
          return false;
      }
      else{ 
        if(tem_Intersecao(arestas[i], arestas[j], &intersecao) == 1) 
          return false;
      }
      
    }
  }
    return true;
}

// Classifica um poligono pelos tipos definidos no ENUM tipo_p
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