#include <bits/stdc++.h>
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
using namespace std;

const double EPS = 1E-9;

struct ponto {
    double x, y;
};
typedef struct ponto ponto;

struct segmento {
    ponto p1, p2;  // p1 e p2 sao o inicio e o fim do segmento no eixo y
    int id;    // id do segmento, para identificar o segmento no vetor de segmentos

    // obtem x usando a equacao parametrica da reta
    double get_x(int64_t y) {
        if (abs(p1.y - p2.y) < EPS)
            return p1.x;
        return p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
    }
   
};
typedef struct segmento seg;

struct poligono {
    vector<ponto> vertices;
};
typedef struct poligono pol;

ponto sub_ponto(ponto p1, ponto bp2);

ponto sum_ponto(ponto p1, ponto p2);

double prod_vetorial(ponto a, ponto b);

double prod_escalar(ponto a, ponto b);

bool haveIntersection(seg v, seg w);
#endif
