#include <cstdlib>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <time.h>
#include <string>
#include <algorithm>
#include "Kart.h"

using namespace std;

//To help build better array
string itos(int i){
    stringstream s;
    s << i;
    return s.str();
}

void CGrupo::criaGrupo()
{
    float cilindradas[4]  = {134,250,450,600};
    bool avariados[3]  = {true,false,false};

    srand (1);   //Criar Pistas e Karts de Teste
    for(int i=1;i<=50;i++){
        vector<CKart> frota;
        for(int j=1;j<=50;j++){
            frota.push_back(CKart(avariados[rand()% 3],
                                  ("KART - "+itos(i))+itos(j),(i-1)*50+j,cilindradas[(rand() % 4)]));
        }
        adicionaPista(CPista("Pista - "+itos(i),frota));
    }
}


vector <CKart> CPista::getKartsAvariados()
{
    vector<CKart> aux;
    for (vector<CKart>::iterator it = frotaKartsPista.begin() ; it != frotaKartsPista.end(); ++it) {
        if ((it)->getAvariado()) aux.push_back((*it));
    }
    return aux;
}
 
//Exercicio 1 a)
bool sortByNumber(CKart & c1, CKart & c2) {
    return c1.getNumero() < c2.getNumero();
}

vector<CKart> CGrupo::ordenaKarts()
{
	vector<CKart> vord;
	vector<CKart> kartPista;

	vector<CPista>::iterator itP = pistasG.begin();
    vector<CKart>::iterator itK;

	for(; itP != pistasG.end(); itP++) {
	    kartPista = (*itP).getFrotaActual();
	    itK = kartPista.begin();
	    for (; itK != kartPista.end(); itK++) {
	        vord.push_back(*itK);
	    }
	}

	sort(vord.begin(), vord.end(), sortByNumber);

	return vord;
    
}

//Exercicio 1 b)  
int CGrupo::numAvariados(int cilind)
{
    vector<CKart> avariados;
    vector<CKart> kartPista;

    vector<CPista>::iterator itP = pistasG.begin();
    vector<CKart>::iterator itK;

    for(; itP != pistasG.end(); itP++) {
        kartPista = (*itP).getKartsAvariados();
        itK = kartPista.begin();
        for (; itK != kartPista.end(); itK++) {
            if ((*itK).getCilindrada() == cilind)
                avariados.push_back(*itK);
        }
    }

    return avariados.size();
}

//Exercicio 1 c)   
bool CPista::prepararCorrida(int numeroKarts, int cilind)
{
    vector<CKart>::iterator itK;
    int numKartsColocados = 0;

    for (itK = frotaKartsPista.begin(); itK != frotaKartsPista.end(); itK++) {
        if (!(*itK).getAvariado() && (*itK).getCilindrada() == cilind && numKartsColocados < numeroKarts) {
            this->kartsLinhaPartida.push(*itK);
            numKartsColocados++;
        }
    }

    return numKartsColocados == numeroKarts;
}

//Exercicio 1 d) 
int CPista::inicioCorrida()
{
    while(!kartsLinhaPartida.empty()) {
        kartsEmProva.push_back(kartsLinhaPartida.front());
        kartsLinhaPartida.pop();
    }

    return kartsEmProva.size();
}

