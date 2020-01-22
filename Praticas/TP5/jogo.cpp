/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar
Jogo::Jogo()
{
    criancas.clear();
}

// a implementar
Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}

// a implementar
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const
{
    list<Crianca> res = criancas;
    return res;
}

// a implementar
string Jogo::escreve() const
{
    string res;
    list<Crianca>::const_iterator it = criancas.begin();

    for (; it != criancas.end(); it++)
        res += (*it).escreve() + "\n";

    return res;
}

// a implementar
Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c1 = new Crianca();
    list<Crianca>::const_iterator it;

    int numP = numPalavras(frase);
    int numJogador;

    while(criancas.size() > 1) {
        it = criancas.begin();
        numJogador = (numP - 1) % criancas.size();
        advance(it, numJogador);
        criancas.erase(it);
    }

    it = criancas.begin();
    (*c1) = (*it);
    return *c1;
}

// a implementar
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res;
    list<Crianca>::iterator it = criancas.begin();

    while (it != criancas.end()) {
        if ((*it).getIdade() > id) {
            res.push_back(*it);
            criancas.erase(it);
            it--;
        }
        it++;
    }

    return res;
}

// a implementar
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    criancas = l1;
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
    list<Crianca>::const_iterator it1 = criancas.begin(), it2 = j2.criancas.begin();

    while (it1 != criancas.end()) {
        if ((*it1) == (*it2)) {
            it1++;
            it2++;
        }
        else
            return false;
    }

	return true;
}

// a implementar
list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    int pos;
    list<Crianca>::const_iterator it = criancas.begin(), it2;
    srand(time(NULL));

    for (int i = 1; i < criancas.size() + 1; i++) {
        pos = rand() % i;
        it2 = res.begin();
        advance(it2, pos);
        res.insert(it2,(*it));
        it++;
    }

    return res;
}
