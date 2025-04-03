#include "geometry.hpp"
#include <bits/stdc++.h>

using namespace std;

/**
 * soh para testar se a intersecao de dois segmentos funciona
 */
int main() {
    seg v, w;
    ponto p1, p2, p3, p4;
    while(cin >> p1.x >> p1.y) {
        cin >> p2.x >> p2.y;
        cin >> p3.x >> p3.y;
        cin >> p4.x >> p4.y;
        v = {p1, p2};
        w = {p3, p4};
        #ifdef DEBUG
        cout << "p1: " << v.p1.x << " " << v.p1.y << endl;
        cout << "p2: " << v.p2.x << " " << v.p2.y << endl;
        cout << "p3: " << w.p1.x << " " << w.p1.y << endl;
        cout << "p4: " << w.p2.x << " " << w.p2.y << endl;
        #endif
        if(haveIntersection(v, w)) {
        } else {
            cout << "nao intersectam" << endl;
        }
    }
    return 0;
}