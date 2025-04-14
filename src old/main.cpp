#include <bits/stdc++.h>
#include "geometry.hpp"

using namespace std;

int main() {
	int qntdPoligonos, qntdPontos, n;
    vector<vector<seg>> poligonos;
    vector<ponto> pontos;
	cin >> qntdPoligonos >> qntdPontos;

	for(int i = 0; i < qntdPoligonos; ++i) {
        cin >> n;
        vector<seg> arestas(n);

		arestas = ordenaArestas(recebePontos(n));
        poligonos.push_back(arestas);

        #ifdef DEBUG
		cout << "Quantidade de pontos = " << pontos.size() << "\n";
		for(const auto& aresta : arestas) {
			cout << "(" << aresta.p1.x << ", " << aresta.p1.y << ") -> ";
			cout << "(" << aresta.p2.x << ", " << aresta.p2.y << ")\n";
		}        
        cout << pontos.size() << " pontos\n";

        #endif
		cout << i + 1 << (ehSimples(arestas) ? " simples" : " nao simples") << endl;
	}

    for (int i = 0; i < qntdPontos; i++) {
        ponto p;
        cin >> p.x >> p.y;
        pontos.push_back(p);

        // aqui eh verificar se o ponto ta dentro de quais poligonos
    }
    

	return 0;
}
