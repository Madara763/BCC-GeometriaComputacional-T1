#include <iostream>
#include "pontos.hpp"

using namespace std;


int main(){

  //Leitura dos dados
  int m,n; //quantidade de poligonos e pontos respectivamente
  
  cin>>m>>n;
  
  list<poligono<double>> lista_poligonos;

  //le os vertices dos m poligonos
  int v;
  int64_t x,y;
  for(int i=0; i<m; i++){
    
    cin>>v; //le quantos vertices 
    
    lista_poligonos
    

    for(int j=0; j<v; j++){ //Le as coordenadas de cada vertice
      cin>>vetor[j].x>>vetor[j].y;
    }//for j

    
  }//for i


  return 0;
}
