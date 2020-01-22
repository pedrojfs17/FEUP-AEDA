#include <queue>
#include <cstdlib>
#include <time.h>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    this->numPresentes = rand() % 5 + 1;
}

//a alterar
int Cliente::getNumPresentes() const {
    return this->numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    this->tempo_atual = 0;
    this->prox_chegada = rand() % 20 + 1;
    this->prox_saida = 0;
    this->clientes_atendidos = 0;
}

//a alterar
void Balcao:: proximoEvento() {
    if (this->clientes.empty() || this->prox_chegada <= this->prox_saida) {
        this->tempo_atual = this->prox_chegada;
        chegada();
    }
    else {
        this->tempo_atual = this->prox_saida;
        saida();
    }
}

//a alterar
void Balcao::chegada() {
    Cliente novo;
    this->prox_saida = this->tempo_atual + novo.getNumPresentes() * this->tempo_embrulho;
    this->clientes.push(novo);
    this->prox_chegada = this->tempo_atual + rand() % 20 + 1;
    cout << "CHEGADA" << endl;
    cout << "Tempo atual: " << this->tempo_atual << endl;
    cout << "Cliente - Presentes: " << novo.getNumPresentes() << endl;
    cout << "Proxima Chegada: " << prox_chegada << endl;
    cout << "Proxima Saida: " << prox_saida << endl << endl;
}

//a alterar
void Balcao::saida() {
    try {
        Cliente client = this->getProxCliente();

        clientes.pop();
        this->prox_saida = this->tempo_atual + client.getNumPresentes() * this->tempo_embrulho;
        this->clientes_atendidos++;
        cout << "SAIDA" << endl;
        cout << "Tempo atual: " << this->tempo_atual << endl;
        cout << "Cliente - Presentes: " << client.getNumPresentes() << endl;
        cout << "Proxima Chegada: " << prox_chegada << endl;
        cout << "Proxima Saida: " << prox_saida << endl << endl;
    }
    catch (FilaVazia &e) {
        cout << e.getMsg() << endl;
        return;
    }
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1)
{
     out << "Numero de clientes atendidos: " << b1.clientes_atendidos << endl;
     out << "Numero de clientes na fila: " << b1.clientes.size();
     return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return this->tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return this->prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return this->clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    if (clientes.empty())
        throw FilaVazia();
    else
        return this->clientes.front();
}

      
