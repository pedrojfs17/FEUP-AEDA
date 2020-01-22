#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

/*
 * Classe Zoo
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1) {
    animais.push_back(a1);
}

string Zoo::getInformacao() const {
    string out = "";

    for (int i = 0; i < animais.size(); i++)
        out += animais[i]->getInformacao();

    return out;
}

bool Zoo::animalJovem(string nomeA) const {
    typename vector<Animal *>::const_iterator itA = animais.begin();

    while (itA != animais.end()) {
        if ((*itA)->getNome() == nomeA) {
            if ((*itA)->eJovem())
                return true;
            else
                return false;
        }
        advance(itA, 1);
    }

    return false;
}

void Zoo::alocaVeterinarios(istream &isV) {
    string nome, codigo;
    int cod;

    while(!isV.eof()) {
        getline(isV, nome);
        getline(isV, codigo);
        cod = stol(codigo);
        Veterinario *vet = new Veterinario(nome, cod);
        veterinarios.push_back(vet);
    }

    typename vector<Animal *>::const_iterator itA = animais.begin();
    typename vector<Veterinario *>::const_iterator itV = veterinarios.begin();

    while (itA != animais.end()) {
        (*itA)->setVeterinario(*itV);
        advance(itV, 1);
        advance(itA, 1);
        if (itV == veterinarios.end())
            itV = veterinarios.begin();
    }
}

bool Zoo::removeVeterinario(string nomeV) {
    typename vector<Veterinario *>::const_iterator itV = veterinarios.begin(), itVFound;
    typename vector<Animal *>::const_iterator itA = animais.begin();

    while (itV != veterinarios.end()) {
        if ((*itV)->getNome() == nomeV) {
            itVFound = itV;
            advance(itV, 1);
            break;
        }
        advance(itV, 1);
    }

    if (itV == veterinarios.end())
        return false;

    while (itA != animais.end()) {
        if ((*itA)->getNomeVet() == nomeV)
            (*itA)->setVeterinario(*itV);
        advance(itA, 1);
    }

    veterinarios.erase(itVFound);
    return true;
}

bool Zoo::operator<(Zoo &zoo2) const {
    return (this->somaIdades() < zoo2.somaIdades());
}

int Zoo::somaIdades() const {
    auto itA = animais.begin();
    int somaIdades = 0;

    while (itA != animais.end()) {
        somaIdades += (*itA)->getIdade();
        advance(itA, 1);
    }

    return somaIdades;
}

