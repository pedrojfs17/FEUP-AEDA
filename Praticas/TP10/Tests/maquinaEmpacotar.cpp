#include "maquinaEmpacotar.h"
#include <sstream>
#include <algorithm>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}

// a alterar
unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
    vector<Objeto>::const_iterator itO = objs.begin();
    unsigned count = 0;

	for (; itO != objs.end(); itO++) {
	    if ((*itO).getPeso() <= capacidadeCaixas) {
            objetos.push(*itO);
            objs.erase(itO);
            itO--;
            count++;
	    }
	}

	return count;
}

// a alterar
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx;
	vector<Caixa> tmp;

	while (!caixas.empty()) {
	    cx = caixas.top();
	    caixas.pop();
	    if (cx.getCargaLivre() >= obj.getPeso()) {
	        for (auto x: tmp)
	            caixas.push(x);
	        return cx;
	    }
	    else {
	        tmp.push_back(cx);
	    }
	}
    for (auto x: tmp)
        caixas.push(x);

	return Caixa(this->capacidadeCaixas);
}

// a alterar
unsigned MaquinaEmpacotar::empacotaObjetos() {

	while (!objetos.empty()) {
	    Objeto obj = objetos.top();
	    objetos.pop();
        Caixa cx = procuraCaixa(obj);
        cx.addObjeto(obj);
        caixas.push(cx);
	}

	return caixas.size();
}

// a alterar
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    if (objetos.empty())
        return "Nao ha objetos!\n";

    HEAP_OBJS tmp = objetos;
    stringstream out;

    while (!tmp.empty()) {
        Objeto o = tmp.top();
        tmp.pop();
        out << o << endl;
    }

	return out.str();
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {

    if (caixas.empty())
        throw MaquinaSemCaixas();

	Caixa cx, maior;
    HEAP_CAIXAS boxes = caixas;
    maior = boxes.top();

    while (!boxes.empty()) {
        cx = boxes.top();
        boxes.pop();
        cout << "Caixa: " << cx.imprimeConteudo() << endl;
        if (maior.getSize() < cx.getSize()) {
            cout << "Encontrou " << cx.imprimeConteudo() << endl;
            maior = cx;
        }
    }

	return maior;
}



