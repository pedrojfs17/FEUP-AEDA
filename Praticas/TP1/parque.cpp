#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli) {
    vagas = lot;
    clientes.clear();
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
    for (int i = 0; i < clientes.size(); i++)
        if (clientes[i].nome == nome)
            return i;
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
    if (clientes.size() < numMaximoClientes) {
        InfoCartao n;
        n.nome = nome;
        n.presente = false;
        clientes.push_back(n);
        return true;
    }
    else
        return false;
}

bool ParqueEstacionamento::entrar(const string & nome) {
    int pos = posicaoCliente(nome);
    if (pos == -1 || vagas == 0)
        return false;
    else if (clientes[pos].presente == true)
        return false;
    else {
        clientes[pos].presente = true;
        vagas--;
        return true;
    }
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
    int pos = posicaoCliente(nome);

    if (pos == -1 || clientes[pos].presente == true)
        return false;
    else {
        clientes.erase(clientes.begin() + pos);
        return true;
    }
}

bool ParqueEstacionamento::sair(const string & nome) {
    int pos = posicaoCliente(nome);

    if (pos == -1 || clientes[pos].presente == false)
        return false;
    else {
        clientes[pos].presente = false;
        vagas++;
        return true;
    }
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}



