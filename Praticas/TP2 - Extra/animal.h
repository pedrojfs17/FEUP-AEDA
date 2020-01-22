
#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
using namespace std;


class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
	bool HasVet = false;
public:
	Animal(string nome, int idade);
	virtual ~Animal(){};
	virtual bool eJovem() const;
	string getNome() const;
	static int getMaisJovem();
	virtual string getInformacao() const;
	void setVeterinario(Veterinario *vet);
	string getNomeVet() const;
	int getIdade() const;
};


class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	bool eJovem() const;
	string getInformacao() const;
	//completar
};


class Voador {
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
    virtual ~Voador(){};
    string getInformacao() const;
	//completar
};


class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
    bool eJovem() const;
    string getInformacao() const;
	//completar
};


#endif /* SRC_ANIMAL_H_ */
