//
// Created by pedro on 14/10/2019.
//

#include "Material.h"

int Material::nextID = 1;

Material::Material() : price(15), ID(nextID) {} //ex: 15 euro por 45 minutos

Material::Material(string type, double price, int amount, int used, bool existing) : price(price), ID(nextID){
    this->type = type;
    this->totalAmount = amount;
    this->usedAmount = used;
    this->existing =existing;
    nextID++;
}

string Material::getType() const {
    return type;
}

double Material::getPrice() const {
    return price;
}

int Material::getTotal() const {
    return totalAmount;
}

int Material::getUsed() const {
    return usedAmount;
}

int Material::getID() const {
    return this->ID;
}

void Material::setType(string type) {
    this->type = type;
}

void Material::setTotal(int total) {
    this->totalAmount = total;
}

void Material::setUsed(int used) {
    this->usedAmount = used;
}

string Material::WriteToFile() const {
    string out = "", price = to_string(this->price);
    out += this->type + ";";
    out += price.substr(0, price.find_first_of(".") + 3) + ";";
    out += to_string(this->totalAmount) + ";";
    out += to_string(this->usedAmount) + ";";
    if(this->existing){
        out+="E";
    }
    else{
        out+="D";
    }
    return out;
}

bool Material::getExisting() const {
    return existing;
}

void Material::setExisting(bool existing) {
    this->existing=existing;
}

//----------------------------------------------------------------------------------------------------------------------


