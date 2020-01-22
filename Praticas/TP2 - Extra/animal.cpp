
#include "animal.h"
#include <sstream>
using namespace std;

/*
 * Classe Animal
 */

int Animal::maisJovem = 0;

Animal::Animal(string nome, int idade){
    this->nome = nome;
    this->idade = idade;
    if (maisJovem == 0)
        maisJovem = idade;
    else if (idade < maisJovem)
        maisJovem = idade;
}

string Animal::getNome() const {
	return nome;
}

int Animal::getMaisJovem() {
    return maisJovem;
}

bool Animal::eJovem() const {
    return false;
}

string Animal::getInformacao() const {
    string out = "";
    out +=  nome + ", " + to_string(idade);
    if (HasVet)
        out += ", " + vet->getNome() + ", " + to_string(vet->getCod());
    return out;
}

void Animal::setVeterinario(Veterinario *veterinario) {
    this->vet = veterinario;
    HasVet = true;
}

string Animal::getNomeVet() const {
    if (HasVet)
        return vet->getNome();
    else
        return "";
}

int Animal::getIdade() const {
    return idade;
}





Cao::Cao(string nome, int idade, string raca) : Animal(nome, idade) {
    this->raca = raca;
}

bool Cao::eJovem() const {
    if (idade < 5)
        return true;
    else
        return false;
}

string Cao::getInformacao() const {
    string out = "";
    out += Animal::getInformacao();
    out += ", " + raca;
    return out;
}






Voador::Voador(int vmax, int amax) {
    this->altura_max = amax;
    this->velocidade_max = vmax;
}

string Voador::getInformacao() const {
    string out = "";
    out += ", " + to_string(velocidade_max) + ", " + to_string(altura_max);
    return out;
}






Morcego::Morcego(string nome, int idade, int vmax, int amax) : Animal(nome, idade) , Voador(vmax, amax) {}

bool Morcego::eJovem() const {
    if (idade < 4)
        return true;
    else
        return false;
}

string Morcego::getInformacao() const {
    string out = "";
    out += Animal::getInformacao();
    out += Voador::getInformacao();
    return out;
}