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
 * Verifica se dois segmentos se interceptam
 */
int haveIntersection(seg v, seg w, seg &intersecao);


/**
 * Testa se o segmento é horizontal
 */
bool ehHorizontal(seg s);

/**
 * Realiza o algoritmo de bentley Ottmann
 */
vector<ponto> bentleyOttmann(vector<seg> segmentos);
#endif
