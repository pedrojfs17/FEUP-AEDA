#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return this->palavra < ps1.palavra;
}

//a alterar
void Dicionario::lerDicionario(ifstream &fich)
{
    string palavra, significado;
    while (!fich.eof()) {
        getline(fich,palavra);
        getline(fich,significado);
        palavras.insert(PalavraSignificado(palavra,significado));
    }
}

//a alterar
string Dicionario::consulta(string palavra) const
{
    BSTItrIn<PalavraSignificado> it(palavras);

    PalavraSignificado a("","");

    while (!it.isAtEnd() && it.retrieve().getPalavra() <= palavra) {
        if (it.retrieve().getPalavra() == palavra)
            return it.retrieve().getSignificado();
        a = it.retrieve();
        it.advance();
    }

    PalavraSignificado b("", "");

    if (!it.isAtEnd()) {
        b = it.retrieve();
    }

    throw PalavraNaoExiste(a,b);
}

//a alterar
bool Dicionario::corrige(string palavra, string significado)
{
    BSTItrIn<PalavraSignificado> it(palavras);
    PalavraSignificado a("","");

    while (!it.isAtEnd()) {
        a = it.retrieve();
        if (a.getPalavra() == palavra) {
            a.setSignificado(significado);
            palavras.remove(it.retrieve());
            palavras.insert(a);
            return true;
        }
        it.advance();
    }

    a = PalavraSignificado(palavra, significado);

    palavras.insert(a);
    return false;
}

//a alterar
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);

    while (!it.isAtEnd()) {
        cout << it.retrieve().getPalavra() << endl << it.retrieve().getSignificado() << endl << "-----------------" << endl;
        it.advance();
    }
}

