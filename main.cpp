#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
#define xx first
#define yy second

int main(){

  //Leitura dos dados
  int m,n; //quantidade de poligonos e pontos respectivamente
  
  cin>>m>>n;

  //Aloca a estrutura para os poligonos
  //Lista para um vetor de pontos (vertices)
  //[] -> {(x,y), (x,y), (x,y)}

  list<vector<pair<int64_t, int64_t>>> lista{}; //estou pensando sobre como fazer isso da melhor forma

  //le os vertices dos m poligonos
  int v;
  int64_t x,y;
  for(int i=0; i<m; i++){
    
    cin>>v; //le quantos vertices 
    
    vector<pair<int64_t, int64_t>> vetor(v); //Cria o vetor que armazenara a seq de pontos

    for(int j=0; j<v; j++){ //Le as coordenadas de cada vertice
      cin>>vetor[j].xx>>vetor[j].yy;
    }//for j
    lista.insert
    
  }//for i


  return 0;
}
