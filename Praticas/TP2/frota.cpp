#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1) {
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const {
    return veiculos.size();
}

int Frota::menorAno() const {
    int menor = 999999;
    for (int i = 0; i < veiculos.size(); i++) {
        if (veiculos[i]->getAno() < menor)
            menor = veiculos[i]->getAno();
    }

    if (menor == 999999)
        return 0;
    else
        return menor;
}

float Frota::totalImposto() const {
    float total = 0;
    for (int i = 0; i < veiculos.size(); i++) {
        total += veiculos[i]->calcImposto();
    }
    return total;
}

vector<Veiculo *> Frota::operator () (int anoM) const {
    vector<Veiculo *> newvec;
    for (int i = 0; i < veiculos.size(); i++) {
        if (veiculos[i]->getAno() == anoM)
            newvec.push_back(veiculos[i]);
    }
    return newvec;
}
