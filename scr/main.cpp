#include <iostream>
#include "poligono.hpp"
#include "raycast.hpp"

using namespace std;


int main(){

  //Leitura dos dados
  int qntPol, qntPon; //quantidade de poligonos e pontos respectivamente
  
  cin>>qntPol>>qntPon;
  
  list<poligono<double>> lista_poligonos;

  //le os vertices dos poligonos
  int v;
  ponto<double> p;
  for(int i=0; i<qntPol; i++){
    
    cin>>v; //le quantos vertices 
    poligono<double> pol;
    for(int j=0; j<v; j++){ //Le as coordenadas de cada vertice
      cin>>p.x>>p.y;
      pol.vertices.push_back(p);
    }//for j
    
    lista_poligonos.push_back(pol);
    
  }//for i

  list<ponto<double>> lista_pontos;
  for(int i=0; i<qntPon; i++){ //Le as coordenadas de cada vertice
    cin>>p.x>>p.y;
    lista_pontos.push_back(p);
  }//for i

  #ifdef DEBUG
  cout<<"Lista de poligonos.\n";
  for(auto it{lista_poligonos.begin()};it != lista_poligonos.end(); ++it){
    cout<<"Poligono -> ";
    for(int i = 0; i < static_cast<int> (it->vertices.size()); i++){
      cout<< (it->vertices[i]);
    }
    cout<<"\n";
  }

  cout<<"Lista de pontos.\n";
  for(auto it{lista_pontos.begin()};it != lista_pontos.end(); ++it){
    cout<<"Ponto -> ";
    cout<< *(it);
    cout<<"\n";
  }
  #endif

  int num_poligono = 1;

  for(auto it{lista_poligonos.begin()};it != lista_poligonos.end(); ++it){  
    switch (tipo_poligono((*it)))
    {
    case CONVEXO:
      (it)->tipo = CONVEXO;
      cout<<num_poligono<<" simples e convexo\n";
      break; 
    case NAO_CONVEXO:
    (it)->tipo = NAO_CONVEXO;
      cout<<num_poligono<<" simples e nao convexo\n";
      break;
    
    case NAO_SIMPLES:
      (it)->tipo = NAO_SIMPLES;
      cout<<num_poligono<<" nao simples\n";
      break;
    
    default:
      break;
    }
    num_poligono++;
  }// for poligonos

  // Verifica dentro de quais poligonos o ponto esta
  int num_ponto = 1;
  for(auto itp{lista_pontos.begin()};itp != lista_pontos.end(); ++itp){
    
    num_poligono = 1;
    cout<<num_ponto<<":";
    
    for(auto it{lista_poligonos.begin()};it != lista_poligonos.end(); ++it){  

      if((*it).tipo != NAO_SIMPLES ){ //isola os nao simples
        if( raycast( (*itp), (*it)) ){
          cout<<num_poligono<<" ";
        }
        num_poligono++;
      }//if simples
    }// for poligonos
    
    cout<<"\n";
    num_ponto++;
  }// for pontos
  return 0;
}
