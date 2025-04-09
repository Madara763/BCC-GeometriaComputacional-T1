#include "geometry.hpp"
#include <algorithm>
using namespace std;

// Algoritmo realizado graças a https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect#comment69866544_565282
// obrigado a https://stackoverflow.com/users/68063/gareth-rees
/**
 * @param intersecao valor passado por referencia, caso haja intersecao
 * Verifica se dois segmentos possuem intersecao
 * 1: se intersectam em um ponto apenas
 * 2: se intersectam em um intervalo
 * -1: nao se intersectam
 */
int temIntersecao(seg v, seg w, seg &intersecao) {
    ponto p = v.p1;
    ponto q = w.p1;
    ponto r = sub_ponto(v.p2, p);
    ponto s = sub_ponto(w.p2, q);
    ponto tr;
    int r2;
    long double t0, t1, u, t, uNum, tNum, denom, t_start, t_end;

    //u = (q − p) × r / (r × s)
    uNum = prod_vetorial(sub_ponto(q, p), r);

    //t = (q − p) × s / (r × s)
    tNum = prod_vetorial(sub_ponto(q, p), s);
    denom = prod_vetorial(r, s);

    #ifdef DEBUG        
    cout << "p: " << p.x << " " << p.y << endl;
    cout << "q: " << q.x << " " << q.y << endl;
    cout << "r: " << r.x << " " << r.y << endl;
    cout << "s: " << s.x << " " << s.y << endl;
    cout << "denom: " << denom << endl;
    #endif    
    if(denom == 0 && uNum == 0) {
        // Colineares
        r2 = prod_escalar(r, r);

        // t0 = (q − p) · r / (r · r)
        t0 = prod_escalar(sub_ponto(q, p),  r) / r2;
        // t1 = (q + s − p) · r / (r · r) 
        t1 = prod_escalar(sub_ponto(sum_ponto(q, s), p), r) / r2;

        // se s e r apontam em direcoes opostas, troca t0 e t1
        // se eh oposto, o produto escalar eh negativo
        if (s.x * r.x + s.y * r.y < 0) {
            long double temp = t0;
            t0 = t1;
            t1 = temp;
        }

        // se o intervalo entre t0 e t1 intersecta o intervalo [0, 1], entao os segmentos de reta sao colineares e sobrepostos
        t_start = max(min(t0, t1), 0.0L);
        t_end = min(max(t0, t1), 1.0L);
        if(t_start <= t_end) {
            auto start = sum_ponto(p, {t_start * r.x, t_start * r.y});
            auto end = sum_ponto(p, {t_end * r.x, t_end * r.y});
            #ifdef DEBUG
            cout << "Colineares e coincidentes entre (" << start.x << "," << start.y << ") e (" << end.x << "," << end.y << ")\n"; 
            #endif
            intersecao.p1 = start;
            intersecao.p2 = end;

            if(t_start == t_end) return 1;
            
            return 2;
        } 
        else { // colineares e disjuntos
            #ifdef DEBUG
            cout << "Colineares e disjuntos" << endl;
            #endif
            return -1;
        }
    } 
    //r × s = 0 and (q − p) × r ≠ 0: paralelas e nao coincidentes
    else if(denom == 0 && prod_vetorial(sub_ponto(q, p) , r) != 0) {
        #ifdef DEBUG
        cout << "Paralelas e nao coincidentes" << endl;
        #endif
        return -1;
    }
    // r × s ≠ 0 e 0 ≤ t ≤ 1 e 0 ≤ u ≤ 1
    // se encontram em um ponto
    else if (denom != 0){
        u = uNum / denom;
        t = tNum / denom;
        
        #ifdef DEBUG        
        cout << "uNum: " << uNum << endl;
        cout << "tNum: " << tNum << endl;
        cout << "u: " << u << endl;
        cout << "t: " << t << endl;
        #endif

        //se intersectam no ponto p + t r 
        tr = {t * r.x, t * r.y};

        if(u >= 0 && u <= 1 && t >= 0 && t <= 1) {
            ponto pInt = sum_ponto(p, tr);
            #ifdef DEBUG
            cout << "Se intersectam em (" << pInt.x << "," << pInt.y << ")\n";
            #endif
            intersecao.p1 = pInt;

            return 1;
        }
    }

    return false;
}

/**
 * Realiza a subtracao de dois vetores
 */
ponto sub_ponto(ponto p1, ponto p2){
    ponto t;
    t.x = p1.x - p2.x;
    t.y = p1.y - p2.y;
    return t;
}

/**
 * Realiza a soma de dois vetores
 */
ponto sum_ponto(ponto p1, ponto p2){
    ponto t;
    t.x = p1.x + p2.x;
    t.y = p1.y + p2.y;
    return t;
}

/**
 * Realiza o produto vetorial em R2
 */
long double prod_vetorial(ponto a, ponto b){
   return a.x * b.y - b.x * a.y; 
}

/**
 * Realiza o produto escalar em R2
 */
long double prod_escalar(ponto a, ponto b){
    return a.x * b.x + a.y * b.y;
}

bool ehMesmoPonto(ponto p1, ponto p2) {
    return (ehMesmaCoord(p1.x, p2.x) && ehMesmaCoord(p1.y, p2.y));
}

bool ehMesmaCoord(long double a, long double b) {
    return abs(a - b) < EPS;
}

bool ehHorizontal(seg s) {
    return ehMesmaCoord(s.p1.y, s.p2.y) && !ehMesmaCoord(s.p1.x, s.p2.x);
}

bool ehSimplesBF(vector<seg> &arestas) {
	for(int i = 0; i < arestas.size(); ++i) {
		for(int j = i + 1; j < arestas.size(); ++j) {
			// Ignora arestas consecutivas (incluindo início-fim)
			if((j == (i + 1) % arestas.size()) ||
			   (i == 0 && j == arestas.size() - 1))
				continue;

			seg intersecao;
			if(temIntersecao(arestas[i], arestas[j], intersecao)) {
				return true;
			}
		}
	}
	return false;
}

bool ehSimples(vector<seg> &arestas){
    vector<ponto> intersecoes = bentleyOttmann(arestas);
    // se eh simples, verifica se a quantidade de intersecoes dentro do poligono > vertices/faces do poligono
    if(arestas.size() == intersecoes.size()){
        return true;
    } else if(arestas.size() < intersecoes.size()){
        return false;
    } 
    // aqui eh certeza que houve erro de ponto flutuante. 
    // pode ocorrer pq ha coord de grandezas diferentes e acumula-se erro
    else {
        // roda bruteforce nisso. não aguento mais
        return ehSimplesBF(arestas);
    }
}

vector<ponto> recebePontos(int n) {
	ponto p, anterior;
	vector<ponto> pontos;

	// primeiro ponto
	cin >> p.x >> p.y;
	pontos.push_back(p);
	anterior = p;

	// Lê os demais pontos
	for(int i = 1; i < n; i++) {
		cin >> p.x >> p.y;
		if(ehHorizontal({p, anterior})) {
			if(p.x < anterior.x) {
				p.y += 1e-4;
			} else {
				pontos[i-1].y += 1e-4;
			}
		}
		pontos.push_back(p);
		anterior = p;
	}
	if(ehHorizontal({pontos.front(), anterior})) {
		if(pontos.front().x < anterior.x) {
			pontos.front().y += 1e-4;
		} else {
			pontos.back().y += 1e-4;  
		}
	}
	return pontos;
}

/**
 * Retorna um segmento ordenado com base em cmpEvento
 */
seg criaSegmentoOrdenado(ponto p, ponto q) {
	cmpEvento cmpPonto;

	if(!cmpPonto(p, q)) {
		swap(p, q);
	}

	return {p, q};
}

vector<seg> ordenaArestas(vector<ponto> pontos) {
	vector<seg> segs;

	// para cada ponto, ordena os mesmos
	for(int i = 1; i < pontos.size(); i++) {
		segs.push_back(criaSegmentoOrdenado(pontos[i - 1], pontos[i]));
	}
	segs.push_back(criaSegmentoOrdenado(pontos.back(), pontos.front()));

	return segs;
}
