#include "jogo.h"
#include <sstream>


//a alterar
ostream &operator << (ostream &os, Circulo &c1)
{
    os << c1.pontuacao << "-";

    if (c1.estado)
        os << "true";
    else
        os << "false";

    os << "-" << c1.nVisitas << endl;
	return os;
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados) {
    Circulo c1(pontos[pos], estados[pos]);
    if (niv == 0) return BinaryTree<Circulo>(c1);
    BinaryTree<Circulo> filhoEsq = iniciaJogo(2 * pos + 1, niv - 1, pontos, estados);
    BinaryTree<Circulo> filhoDir = iniciaJogo(2 * pos + 2, niv - 1, pontos, estados);
    return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}

//a alterar
Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
    jogo = iniciaJogo(0, niv,pontos,estados);
}

//a alterar
string Jogo::escreveJogo()
{
    BTItrLevel<Circulo> it(jogo);
    stringstream out;

    while(!it.isAtEnd()) {
        out << it.retrieve();
        it.advance();
    }

    return out.str();
}

//a alterar
int Jogo::jogada()
{
    BTItrLevel<Circulo> it(jogo);
    Circulo pont;
    int pos = 0, advance = 0;

    while(!it.isAtEnd()) {

        pont = it.retrieve();

        if (!it.retrieve().getEstado()) {
            advance = 2 * pos + 1 - pos;
            pos = 2 * pos + 1;
        }
        else {
            advance = 2 * pos + 2 - pos;
            pos = 2 * pos + 2;
        }

        it.retrieve().mudaEstado();
        it.retrieve().incNVisitas();

        for (int i = 0; i < advance; i++) {
            if (it.isAtEnd())
                break;
            it.advance();
        }
    }

    return pont.getPontuacao();
}


//a alterar
int Jogo::maisVisitado()
{
    BTItrLevel<Circulo> it(jogo);
    it.advance();
    Circulo pont = it.retrieve();

    while (!it.isAtEnd()) {
        if (it.retrieve().getNVisitas() > pont.getNVisitas())
            pont = it.retrieve();
        it.advance();
    }

    return pont.getNVisitas();
}

