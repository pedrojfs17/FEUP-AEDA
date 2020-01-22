#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template<class N, class A>
Grafo<N, A>::Grafo() {}

template<class N, class A>
Grafo<N, A>::~Grafo() {}

template<class N, class A>
int Grafo<N, A>::numNos(void) const {
    return nos.size();
}

template<class N, class A>
int Grafo<N, A>::numArestas(void) const {
    int num_arestas = 0;

    if (numNos() > 0)
        for (int i = 0; i < nos.size(); i++)
            num_arestas += nos[i]->arestas.size();

    return num_arestas;
}


template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }


template <class N>
class ArestaRepetida
{
public:
    N info1, info2;
    ArestaRepetida(N inf1, N inf2) { info1 = inf1; info2 = inf2; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &Aresta)
{ out << "Aresta repetida: " << Aresta.info1 << " , " << Aresta.info2; return out; }

template <class N>
class ArestaInexistente {
public:
    N info1, info2;
    ArestaInexistente(N inf1, N inf2) { info1 = inf1; info2 = inf2;}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &Aresta)
{ out << "Aresta inexistente: " << Aresta.info1 << " , " << Aresta.info2; return out; }



template<class N, class A>
Grafo<N,A> &Grafo<N, A>::inserirNo(const N &dados) {
    typename vector < No <N,A> *>::const_iterator it = nos.begin();
    while(it != nos.end()) {
        if (dados == (*it)->info) {
            throw NoRepetido<N>(dados);
        }
        advance(it, 1);
    }

    No<N,A> *novo = new No<N,A>(dados);
    this->nos.push_back(novo);
    return *this;
}

template<class N, class A>
Grafo<N,A> &Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
    typename vector < No <N,A> *>::iterator it = nos.begin();
    typename vector < Aresta <N,A>>::iterator itA;
    bool found_begin = false, found_end = false;

    No<N,A> *begin_pointer = NULL, *end_pointer = NULL;

    while(it != nos.end()) {
        if (inicio == (*it)->info) {
            found_begin = true;
            begin_pointer = *it;
            for (itA = (*it)->arestas.begin(); itA != (*it)->arestas.end(); itA++)
                if (itA->destino->info == fim)
                    throw ArestaRepetida<N>(inicio,fim);
            if (found_end) {break;}
        }
        else if (fim == (*it)->info) {
            found_end = true;
            end_pointer = *it;
            if (found_begin) {break;}
        }
        advance(it, 1);
    }

    if (!found_begin) throw NoInexistente<N>(inicio);
    if (!found_end) throw NoInexistente<N>(fim);

    Aresta <N,A> novo(end_pointer,val);
    begin_pointer->arestas.push_back(novo);
    return *this;
}

template<class N, class A>
A &Grafo<N, A>::valorAresta(const N &inicio, const N &fim) {
    typename vector < No <N,A> *>::iterator it = nos.begin();
    typename vector < Aresta <N,A>>::iterator itA;

    while(it != nos.end()) {
        if (inicio == (*it)->info) {
            for (itA = (*it)->arestas.begin(); itA != (*it)->arestas.end(); itA++)
                if (itA->destino->info == fim) {
                    return itA->valor;
                }
            throw ArestaInexistente<N>(inicio, fim);
        }
        advance(it, 1);
    }

    throw NoInexistente<N>(inicio);
}

template<class N, class A>
Grafo<N,A> &Grafo<N, A>::eliminarAresta(const N &inicio, const N &fim) {
    typename vector < No <N,A> *>::iterator it = nos.begin();
    typename vector < Aresta <N,A>>::iterator itA;

    while(it != nos.end()) {
        if (inicio == (*it)->info) {
            for (itA = (*it)->arestas.begin(); itA != (*it)->arestas.end(); itA++)
                if (itA->destino->info == fim) {
                    (*it)->arestas.erase(itA);
                    return *this;
                }
            throw ArestaInexistente<N>(inicio, fim);
        }
        advance(it, 1);
    }

    throw NoInexistente<N>(inicio);
}

template<class N, class A>
void Grafo<N, A>::imprimir(std::ostream &os) const {
    typename vector < No <N,A> *>::const_iterator it = nos.begin();
    typename vector < Aresta <N,A>>::iterator itA;

    while (it != nos.end()) {
        os << "( " << (*it)->info;
        for (itA = (*it)->arestas.begin(); itA != (*it)->arestas.end(); itA++)
            os << "[ " << itA->destino->info << " " << itA->valor << "] ";
        os << ") ";
        advance(it, 1);
    }
}

template<class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N, A> &Grafo)
{ Grafo.imprimir(out); return out;}










