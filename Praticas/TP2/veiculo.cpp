#include "veiculo.h"
#include <iostream>

using namespace std;



Veiculo::Veiculo(string mc, int m, int a) {
    marca = mc;
    mes = m;
    ano = a;
}

string Veiculo::getMarca() const {
    return marca;
}

int Veiculo::getAno() const {
    return ano;
}

int Veiculo::info() const {
    cout << "Marca: " << marca << endl;
    cout << "Mes: " << mes << endl;
    cout << "Ano: " << ano << endl;
    return 3;
}

bool Veiculo::operator<(const Veiculo &v) const {
    if (ano < v.ano)
        return true;
    else if (ano > v.ano)
        return false;
    else {
        if (mes < v.mes)
            return true;
        else
            return false;
    }
}




Motorizado::Motorizado(string mc, int m, int a, string c, int cil): Veiculo(mc, m, a) {
    combustivel = c;
    cilindrada = cil;
}

string Motorizado::getCombustivel() const {
    return combustivel;
}

int Motorizado::info() const {
    Veiculo::info();
    cout << "Combustivel: " << combustivel << endl;
    cout << "Cilindrada: " << cilindrada << endl;
    return 5;
}

float Motorizado::calcImposto() const {
    if (combustivel == "gasolina") {
        if (cilindrada <= 1000) {
            if (ano > 1995)
                return 14.56;
            else
                return 8.10;
        }
        else if (cilindrada <= 1300) {
            if (ano > 1995)
                return 29.06;
            else
                return 14.56;
        }
        else if (cilindrada <= 1750) {
            if (ano > 1995)
                return 45.15;
            else
                return 22.65;
        }
        else if (cilindrada <= 2600) {
            if (ano > 1995)
                return 113.98;
            else
                return 54.89;
        }
        else if (cilindrada <= 3500) {
            if (ano > 1995)
                return 181.17;
            else
                return 87.13;
        }
        else {
            if (ano > 1995)
                return 320.89;
            else
                return 140.37;
        }
    }
    else {
        if (cilindrada <= 1500) {
            if (ano > 1995)
                return 14.56;
            else
                return 8.10;
        }
        else if (cilindrada <= 2000) {
            if (ano > 1995)
                return 29.06;
            else
                return 14.56;
        }
        else if (cilindrada <= 3000) {
            if (ano > 1995)
                return 45.15;
            else
                return 22.65;
        }
        else {
            if (ano > 1995)
                return 113.98;
            else
                return 54.89;
        }
    }
}



Automovel::Automovel(string mc, int m, int a, string c, int cil): Motorizado(mc, m, a, c, cil) {}

int Automovel::info() const {
    Motorizado::info();
    return 5;
}



Camiao::Camiao(string mc, int m, int a, string c, int cil, int cm): Motorizado(mc, m, a, c, cil) {
    carga_maxima = cm;
}

int Camiao::info() const {
    Motorizado::info();
    cout << "Carga Maxima: " << carga_maxima << endl;
    return 6;
}



Bicicleta::Bicicleta(string mc, int m, int a, string t): Veiculo(mc, m, a) {
    tipo = t;
}

int Bicicleta::info() const {
    Veiculo::info();
    cout << "Tipo: " << tipo << endl;
    return 4;
}

float Bicicleta::calcImposto() const {
    return 0;
}



