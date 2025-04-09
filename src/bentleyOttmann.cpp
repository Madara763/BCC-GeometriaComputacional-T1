
#include <algorithm>

#include "geometry.hpp"
using namespace std;

const long double EPS_DESCIDA = 1e-8;
long double altura_varredura = 0;
long double xEventoAtual = 0;

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
		if(ehHorizontal(s) && !ehHorizontal(q)) return x_atual + EPS < q.getX(y_atual);
		if(!ehHorizontal(s) && ehHorizontal(q)) return s.getX(y_atual) < x_atual + EPS;

		// se os dois segmentos advem do mesmo ponto, não precisa de erro
		if(ehMesmoPonto(s.p1, q.p1))
			return s.getX(y_atual) < q.getX(y_atual);

		return s.getX(y_atual) + EPS < q.getX(y_atual);
	}
};
void imprimeSegmentoCompleto(const segmento &s, long double altura_varredura) {
    cout << "Segmento ["
         << "p1=(" << s.p1.x << ", " << s.p1.y << "), "
         << "p2=(" << s.p2.x << ", " << s.p2.y << ")"
         << "], x(altura=" << altura_varredura << ") = " << s.getX(altura_varredura)
         << endl;
}

void ordenaPonto(ponto &p1, ponto &p2) {
	if(p1.y == p2.y) {
		if(p1.x > p2.x) {
			swap(p1, p2);
		}
	} else if(p1.y < p2.y) {
		swap(p1, p2);
	}
}
/**
 * Verifica se o ponto reside na extremidade superior, inferior, ou no meio
 * 1: extremidade superior
 * 2: extremidade inferior
 * 3: dentro do segmento
 * -1: fora do segmento
 */
int testaCasosEvento(seg s, ponto p) {
	// se for o ponto inferior do proprio segmento
	if(ehMesmoPonto(s.p1, p))
		return 1;
	else if(ehMesmoPonto(s.p2, p))
		return 2;
	else if(s.testaX(p))
		return 3;

	return -1;
}

/**
 * Insere, caso necessario, dependendo onde o ponto reside (ou não) em seg, retorna o numero de caso de evento
 * 1: superior
 * 2: inferior
 * 3: interior
 * -1: sem caso
 */
int tratarCasosEvento(vector<seg> &superiores, vector<seg> &inferiores, vector<seg> &interiores, seg s, ponto p) {
	switch(testaCasosEvento(s, p)) {
	case 1:
		// superiores.push_back(s);
		// return 1;
		break;
	case 2:
		inferiores.push_back(s);
		return 2;
		break;
	case 3:
		interiores.push_back(s);
		return 3;
		break;
	default:
		return -1;
		break;
	}

	return -1;
}

void apagarSegmentosArvore(set<seg, cmpSeg> &arvore_seg, vector<seg> v) {
	for(auto it = v.begin(); it != v.end(); it++)
		arvore_seg.erase(*it);
}

void inserirSegmentosArvore(set<seg, cmpSeg> &arvore_seg, vector<seg> v) {
	vector<seg> horizontais;  // segmentos horizontais por ultimo
	for(auto it = v.begin(); it != v.end(); it++) {
		if(ehHorizontal(*it)){
			horizontais.push_back(*it);
		} else {
			auto [inserted_it, inserted] = arvore_seg.insert(*it);

			// if (!inserted) {
			// 	cout << "Não inseriu o segmento ";
			// 	imprimeSegmentoCompleto(*it, altura_varredura);
			// 	for (const auto &seg_existente : arvore_seg) {
			// 		cmpSeg cmp(xEventoAtual, altura_varredura);
			// 		if (!cmp(*it, seg_existente) && !cmp(seg_existente, *it)) {
			// 			cout << "Segmento considerado igual ao existente:" << endl;
			// 			imprimeSegmentoCompleto(seg_existente, altura_varredura);
			// 			cout << "Novo: getX = " << it->getX(altura_varredura) << endl;
			// 			cout << "Existente: getX = " << seg_existente.getX(altura_varredura) << endl;
			// 		}
			// 	}
			// }
		}
	}
	while(!horizontais.empty()) {
		arvore_seg.insert(horizontais.back());
		horizontais.pop_back();
	}
}

/**
 * verifica se os segmentos se intersectam após a linha de varredura ou se se intersectam mas a direita do ponto p
 */
void acharNovosEventos(seg sl, seg sr, ponto p, multimap<ponto, optional<seg>, cmpEvento> &filaEvento) {
	seg intersecao;

	if(haveIntersection(sl, sr, intersecao) == 1) {
		if(intersecao.p1.y < altura_varredura) {
			if(filaEvento.find(intersecao.p1) == filaEvento.end()) {
				#ifdef DEBUG
				cout << "adicionado evento (" << intersecao.p1.x << "," << intersecao.p1.y << ")\n";
				#endif
				filaEvento.insert({intersecao.p1, {}});
			}
		} else if(intersecao.p1.x > p.x) {
			if(filaEvento.find(intersecao.p1) == filaEvento.end()) {
				#ifdef DEBUG
				cout << "adicionado evento (" << intersecao.p1.x << "," << intersecao.p1.y << ")\n";
				#endif
				filaEvento.insert({intersecao.p1, {}});
			}
		}
	}
}

/**
 * retorna o segmento mais a direita ou a esquerda do vetor
 * Retorna nullopt caso nao haja
 * @param opcao 1 para direita 0 para esquerda
 */
optional<seg> extremos(vector<seg> v, int opcao) {
	long double coordXSeg;
	auto it = v.begin();
	bool encontrado = false;
	seg s;
	if(opcao == 1) {
		coordXSeg = -DBL_MAX;
		for(; it != v.end(); it++) {
			if(coordXSeg < (*it).getX(altura_varredura)) {
				coordXSeg = (*it).getX(altura_varredura);
				s = *it;
				encontrado = true;
			}
		}
	} else if(opcao == 0) {
		coordXSeg = DBL_MAX;
		for(; it != v.end(); it++) {
			if(coordXSeg > (*it).getX(altura_varredura) && !ehHorizontal(*it)) {
				coordXSeg = (*it).getX(altura_varredura);
				s = *it;
				encontrado = true;
			}
		}
	}

	if(encontrado) return s;
	return nullopt;
}

void tratarEvento(set<seg, cmpSeg> &arvore_seg, vector<ponto> &intersecao, multimap<ponto, optional<seg>, cmpEvento> &filaEvento) {
	// superiores = segmentos que a extremidade superior eh p
	// inferiores = segmentos que a extremidade inferior eh p
	// interiores = segmentos que tem p em seu interior
	vector<seg> superiores, inferiores, interiores;
	seg maisDireita, maisEsquerda;
	set<seg>::iterator segEsquerda, segDireita;
	seg sl, sr;
	ponto p;
	seg pontoToSeg;
	auto evento = (*filaEvento.begin());
	p = evento.first;
	altura_varredura = p.y;
	pontoToSeg.p1 = p;
	pontoToSeg.p2 = p;
	xEventoAtual = p.x;
	auto range = filaEvento.equal_range(p);

	for(auto it = range.first; it != range.second; ++it) {
		if(it->second.has_value()) {
			superiores.push_back(it->second.value());
		}
	}
	std::vector<seg> debug_vec(arvore_seg.begin(), arvore_seg.end());

	if(auto it = arvore_seg.lower_bound(pontoToSeg);
	   it != arvore_seg.end() && ((ehMesmaCoord((*it).p1.y, p.y) &&
	                               p.x >= (*it).p1.x && p.x <= (*it).p2.x) ||
	                              ehMesmaCoord((*it).getX(p.y), p.x))) {
		auto s = *(it);
		auto nextIt = next(it);
		auto prevIt = make_reverse_iterator(it);

		auto caso = tratarCasosEvento(superiores, inferiores, interiores, s, p);

		// verifica se os anteriores ou os proximos tambem contem o ponto
		while((nextIt != arvore_seg.end()) &&
		      ((ehMesmaCoord((*nextIt).p1.y, p.y) &&
		        p.x >= (*nextIt).p1.x && p.x <= (*nextIt).p2.x) ||
		       ehMesmaCoord((*nextIt).getX(p.y), p.x))) {
			caso = tratarCasosEvento(superiores, inferiores, interiores, *nextIt, p);
			if(caso == -1) break;
			nextIt++;
		}

		while((prevIt != arvore_seg.rend()) &&
		      ((ehMesmaCoord((*prevIt).p1.y, p.y) &&
		        p.x >= (*prevIt).p1.x && p.x <= (*prevIt).p2.x) ||
		       ehMesmaCoord((*prevIt).getX(p.y), p.x))) {
			caso = tratarCasosEvento(superiores, inferiores, interiores, *prevIt, p);
			if(caso == -1) break;
			prevIt++;
		}
	}

	// se os sup, inf, int forem > 1
	if(superiores.size() + inferiores.size() + interiores.size() > 1) {
		intersecao.push_back(p);
	}
	// deletar inferiores e os que contem no interior da arvore
	apagarSegmentosArvore(arvore_seg, inferiores);
	apagarSegmentosArvore(arvore_seg, interiores);

	// inserir segmentos superiores e interiores na arvore como se fossem um pouco abaixo da linha de varredura
	auto aux = altura_varredura;
	altura_varredura -= EPS_DESCIDA;
	inserirSegmentosArvore(arvore_seg, superiores);
	inserirSegmentosArvore(arvore_seg, interiores);
	altura_varredura = aux;

	if(superiores.size() + interiores.size() == 0) {
		segEsquerda = arvore_seg.lower_bound(pontoToSeg);
		segDireita = segEsquerda;
		if(segEsquerda != arvore_seg.begin() && segDireita != --arvore_seg.end())
			acharNovosEventos(*(--segEsquerda), *(++segDireita), p, filaEvento);
	} else {
		superiores.insert(superiores.end(), interiores.begin(), interiores.end());
		altura_varredura -= EPS_DESCIDA;
		if(auto maisEsquerda = extremos(superiores, 0); maisEsquerda.has_value()) {
			if(auto leftIt = arvore_seg.lower_bound(maisEsquerda.value()); leftIt != arvore_seg.begin()) {
				sl = *(--leftIt);
				acharNovosEventos(sl, maisEsquerda.value(), p, filaEvento);
			}
		}
		if(auto maisDireita = extremos(superiores, 1); maisDireita.has_value()) {
			if(auto rightIt = arvore_seg.lower_bound(maisDireita.value()); rightIt != prev(arvore_seg.end())) {
				sr = *(++rightIt);
				acharNovosEventos(sr, maisDireita.value(), p, filaEvento);
			}
		}
		altura_varredura = aux;
	}
}

vector<ponto> acharIntersecoes(vector<seg> segmentos) {
	multimap<ponto, optional<seg>, cmpEvento> filaEvento;
	vector<ponto> intersecao;
	cmpSeg comparador(xEventoAtual, altura_varredura);
	cmpEvento cmp;
	set<seg, cmpSeg> arvore_seg(comparador);

	int i = 0;
	for(auto it = segmentos.begin(); it != segmentos.end(); it++) {
		auto s = *it;

		// apenas insere segmentos nos upper points
		filaEvento.insert(pair<ponto, optional<seg>>{s.p1, s});
		filaEvento.insert(pair<ponto, optional<seg>>{s.p2, nullopt});
	}

#ifdef DEBUG
	std::cout << "Fila de eventos:\n";
	for(auto it = filaEvento.begin(); it != filaEvento.end();) {
		ponto atual = it->first;
		std::cout << "Ponto de evento " << i++ << ": (" << atual.x << ", " << atual.y << ")\n";

		// Itera sobre todos os segmentos com essa chave
		auto range = filaEvento.equal_range(atual);
		for(auto jt = range.first; jt != range.second; ++jt) {
			if(jt->second.has_value()) {
				const seg &s = jt->second.value();
				std::cout << "  Segmento: (" << s.p1.x << ", " << s.p1.y << ") -> ("
				          << s.p2.x << ", " << s.p2.y << ")\n";
			} else {
				std::cout << "  Fim de segmento.\n";
			}
		}

		it = range.second;  // pula para o próximo ponto diferente
	}

#endif

	while(!filaEvento.empty()) {
		auto e = *filaEvento.begin();
		tratarEvento(arvore_seg, intersecao, filaEvento);
		auto range = filaEvento.equal_range(e.first);
		filaEvento.erase(range.first, range.second);
	}
	return intersecao;
}

vector<ponto> bentleyOttmann(vector<seg> segmentos) {
	return acharIntersecoes(segmentos);
}

/**
 * Recebe os pontos e impede de que haja futuramente segmentos horizontais
 */
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

int main() {
	vector<seg> arestas;
	vector<ponto> pontos, intersecoes;
	seg v;
	int n;
	ponto p1, p2, aux, start;
	cin >> n >> n >> n;
	pontos = recebePontos(n);
	
	arestas = ordenaArestas(pontos);
	
	// cout << "Quantidade de pontos = " << pontos.size() << "\n";
	// for (const auto& aresta : arestas) {
	// 	cout << "(" << aresta.p1.x << ", " << aresta.p1.y << ") -> ";
	// 	cout << "(" << aresta.p2.x << ", " << aresta.p2.y << ")\n";
	// }
	
	intersecoes = bentleyOttmann(arestas);

	cout << pontos.size() << " pontos\n";
	cout << "qntd de intersecoes = " << intersecoes.size() << "\n";
	// for(auto it = intersecoes.begin(); it != intersecoes.end(); it++) {
	// 	auto p = *(it);
	// 	cout << "(" << p.x << "," << p.y << ")";
	// }

	cout << "\n";
}
