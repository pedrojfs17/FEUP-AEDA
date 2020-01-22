#include "jogador.h"

//a alterar
void Jogador::adicionaAposta(const Aposta & ap)
{
    apostas.insert(ap);
}

//a alterar
unsigned Jogador::apostasNoNumero(unsigned num) const
{
    unsigned count = 0;

	for (auto x : apostas)
	    if (x.contem(num))
	        count++;

	return count;
}

//a alterar
tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;

	for (auto x : apostas)
	    if (x.calculaCertos(sorteio) > 3)
	        money.insert(x);

	return money;
}
