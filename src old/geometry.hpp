#include <bits/stdc++.h>
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
using namespace std;

const long double EPS = 1E-9;

struct ponto {
    long double x, y;
};

struct poligono {
    vector<ponto> vertices;
};
typedef struct poligono pol;


/**
 * Realiza a subtracao de dois pontos
 */
ponto sub_ponto(ponto p1, ponto bp2);

/**
 * Realiza a soma de dois pontos
 */
ponto sum_ponto(ponto p1, ponto p2);

/**
 * Realiza o produto vetorial em R2
 */
long double prod_vetorial(ponto a, ponto b);

/**
 * Realiza o produto escalar em R2
 */
long double prod_escalar(ponto a, ponto b);

bool ehMesmoPonto(ponto p1, ponto p2);

bool ehMesmaCoord(long double a, long double b);


struct segmento {
    ponto p1, p2;  // p1 e p2 sao o inicio e o fim do segmento no eixo y

    // obtem x usando a equacao parametrica da reta
    long double getX(long double y) const{
        // se eh um segmento degenerado, retorna qualquer ponto
		if(ehMesmoPonto(p1, p2)){
			return p1.x;
		}
        if (abs(p1.y - p2.y) < EPS){
            return y;
        }
        return p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
    }

    // verifica se a função do segmento gera o mesmo x que o ponto (f(p.y) = p.x)
    long double testaX(ponto p) const{
        // se for horizontal, verifica se o ponto esta em cima
        if(abs(p1.y - p2.y) < EPS){
            return ehMesmaCoord(p1.y, p.y);
        }
        return ehMesmaCoord(getX(p.y), p.x);
    }
};
typedef struct segmento seg;

/**
 * Testa se o segmento é horizontal
 */
bool ehHorizontal(seg s);

/**
 * Comparador customizado de evento
 **/
struct cmpEvento {
	bool operator()(const ponto &p, const ponto &q) const {
		if(abs(p.y - q.y) < EPS)
			return p.x < q.x;

		return p.y > q.y;
	}
};

/**
 * Comparador customizado de segmento
 */
struct cmpSeg {
	const long double &y_atual, &x_atual;
	cmpSeg(const long double &x_ref, const long double &y_ref) : x_atual(x_ref), y_atual(y_ref) {}
	bool operator()(const seg &s, const seg &q) const {
		//aqui garante que se dois segmentos voltem para a arvore, o horizontal sempre fique por ultimo
        if(ehHorizontal(s) && !ehHorizontal(q)) return x_atual + EPS < q.getX(y_atual);
		if(!ehHorizontal(s) && ehHorizontal(q)) return s.getX(y_atual) < x_atual + EPS;

		// se os dois segmentos advem do mesmo ponto, não precisa de erro
		if(ehMesmoPonto(s.p1, q.p1))
			return s.getX(y_atual) < q.getX(y_atual);

		return s.getX(y_atual) + EPS < q.getX(y_atual);
	}
};

/**
 * Verifica se dois segmentos se interceptam
 */
int temIntersecao(seg v, seg w, seg *intersecao = nullptr);

/**
 * Realiza o algoritmo de bentley Ottmann
 */
vector<ponto> bentleyOttmann(vector<seg> segmentos);

/**
 * Verifica se o poligono é simples ou nao
 */
bool ehSimplesBF(vector<seg> &arestas);

/**
 * Verifica se o poligono é simples ou nao
 */
bool ehSimples(vector<seg> &arestas);

/**
 * Recebe os pontos e impede de que haja futuramente segmentos horizontais
 */
vector<ponto> recebePontos(int n);

/**
 * Retorna um segmento ordenado com base em cmpEvento
 */
seg criaSegmentoOrdenado(ponto p, ponto q);

/**
 * Ordena as arestas para uso do algoritmo de Bentley Ottmann
 */
vector<seg> ordenaArestas(vector<ponto> pontos);
#endif
