#include <iostream>
#include "Address.h"

Address::Address(){}

Address::Address(string street, string door, string floor, string postal, string location) {
    this->street = street;
    this->door = door;
    this->floor = floor;
    this->postalCode = postal;
    this->location = location;
}

Address::Address(string line){
    vector<string> components;
    string component = "";

    for (int x = 0; x < line.size(); x++)
    {
        if (line[x] == '/' || line[x] == '\n')
        {
            components.push_back(component);
            component = "";
            continue;
        }
        component += line[x];
    }
    components.push_back(component);


    this->street = components[0];
    this->door = components[1];
    this->floor = components[2];
    this->postalCode = components[3];
    this->location = components[4];
}

// GET methods

string Address::getStreet() const{
    return street;
}

string Address::getDoor() const{
    return door;
}

string Address::getFloor() const{
    return floor;
}

string Address::getPostalCode() const{
    return postalCode;
}

string Address::getLocation() const{
    return location;
}

string Address::getFullAddress() const {
    string info;
    info="Street: "+street+"\n\tDoor: "+door+"\n\tFloor: "+floor+"\n\tPostal Code: "+postalCode+"\n\tLocation: "+location;
    return info;
}

// SET methods

void Address::setStreet(string street){
    this->street = street;
}

void Address::setDoor(string door){
    this->door = door;
}

void Address::setFloor(string floor){
    this->floor = floor;
}

void Address::setPostalCode(string postalCode){
    this->postalCode = postalCode;
}

void Address::setLocation(string  location){
    this->location = location;
}

string Address::WriteToFile() const {
    return street + "/" + door + "/" + floor + "/" + postalCode + "/" + location;
}

bool Address::validAddress() const {
    if (street.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.,/ ") != string::npos) {cout<<"A";return false;}
    else if (door.find_first_not_of("01234567890") != string::npos) {cout<<"B";return false;}
    else if (floor.find_first_not_of("01234567890") != string::npos) {cout<<"C";return  false;}
    else if (!validPostcode()) {cout<<"D";return false;}
    else if(location.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.,/") != string::npos) {cout<<"E1";return false;}
    return true;
}

bool Address::validPostcode() const{
    if (postalCode.length() != 8) {return false;}
    else if ((!all_of(postalCode.begin(), postalCode.end() - 4, ::isdigit)) || (!all_of(postalCode.begin() + 5, postalCode.end(), ::isdigit)) || postalCode[4] != '-' ){return false;}
    return true;
}