#include "geometry.hpp"
#include <algorithm>
using namespace std;
bool haveIntersection(seg v, seg w) {
    ponto p = v.p1;
    ponto q = w.p1;
    ponto r = sub_ponto(v.p2, p);
    ponto s = sub_ponto(w.p2, q);
    ponto tr;
    int r2;
    double t0, t1, u, t, uNum, tNum, denom, t_start, t_end;

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
            double temp = t0;
            t0 = t1;
            t1 = temp;
        }

        // se o intervalo entre t0 e t1 intersecta o intervalo [0, 1], entao os segmentos de reta sao colineares e sobrepostos

        t_start = max(min(t0, t1), 0.0);
        t_end = min(max(t0, t1), 1.0);
        if(t_start <= t_end) {
            auto start = sum_ponto(p, {t_start * r.x, t_start * r.y});
            auto end = sum_ponto(p, {t_end * r.x, t_end * r.y});
            cout << "Colineares e coincidentes entre (" << start.x << "," << start.y << ") e (" << end.x << "," << end.y << ")\n"; 
            return true;
        } 
        else { // colineares e disjuntos
            cout << "Colineares e disjuntos" << endl;
            return false;
        }
    } 
    //r × s = 0 and (q − p) × r ≠ 0: paralelas e nao coincidentes
    else if(denom == 0 && prod_vetorial(sub_ponto(q, p) , r) != 0) {
        cout << "Paralelas e nao coincidentes" << endl;
        return false;
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
            cout << "Se intersectam em (" << sum_ponto(p, tr).x << "," << sum_ponto(p, tr).y << ")\n";
            return true;
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
double prod_vetorial(ponto a, ponto b){
   return a.x * b.y - b.x * a.y; 
}

/**
 * Realiza o produto escalar em R2
 */
double prod_escalar(ponto a, ponto b){
    return a.x * b.x + a.y * b.y;
}
