#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
    return numeros.find(num) != numeros.end();
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    bool insert = false;

    for (int i = 0; i < valores.size() && n > 0; i++) {
        insert = numeros.insert(valores[i]).second;
        if (insert)
            n--;
    }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    unsigned numCertos = 0;

    typename tabHInt::const_iterator it = sorteio.begin();

    for (; it != sorteio.end(); it++)
        if (contem(*it))
            numCertos++;

        /*
    for (auto x : sorteio)
        if (contem(x))
            numCertos++;
            */

    return numCertos;
}





