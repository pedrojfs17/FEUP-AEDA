#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;



ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    for (unsigned int i = 0; i < clientes.size(); i++) {
        if (clientes[i].nome == nome)
            return i;
    }
    return -1;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);

    if (pos == -1)
        throw ClienteNaoExistente(nome);
    else
        return clientes[pos].frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	clientes[pos].frequencia++;
	vagas--;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia() {
    for (unsigned int i = 1; i < clientes.size(); i++)
    {
        InfoCartao tmp = clientes[i];
        int j;
        for (j = i; j > 0 && tmp.frequencia >= clientes[j-1].frequencia; j--) {
            if (tmp.frequencia == clientes[j-1].frequencia)
                if (tmp.nome > clientes[j-1].nome)
                    continue;
            clientes[j] = clientes[j-1];
        }
        clientes[j] = tmp;
    }
}

void ParqueEstacionamento::ordenaClientesPorNome() {
    for (unsigned int i = 1; i < clientes.size(); i++) {
        InfoCartao tmp = clientes[i];
        int j;
        for (j = i; j > 0 && tmp.nome < clientes[j-1].nome; j--) {
            clientes[j] = clientes[j-1];
        }
        clientes[j] = tmp;
    }
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    ordenaClientesPorFrequencia();
    vector<string> nomes;

    for (unsigned int i = 0; i < clientes.size(); i++) {
        if (clientes[i].frequencia >= n1 && clientes[i].frequencia <= n2)
            nomes.push_back(clientes[i].nome);
    }

    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    InfoCartao person;

    for(size_t i = 0; i < pe.clientes.size(); i++) {
        person = pe.getClienteAtPos(i);
        os << "Nome: " << person.nome << ", Presente: ";
        if (person.presente)
            os << "Sim";
        else
            os << "Nao";
        os << ", Frequencia: " << person.frequencia << endl;
    }

    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;

    if (p > clientes.size() || p < 0)
        throw PosicaoNaoExistente(p);

    info = clientes[p];
    return info;
}
