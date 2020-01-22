/*
 * Postman.cpp
 */
#include "Postman.h"

int Postman::idValue = 1;

Postman::Postman(): id(0) {}

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

Postman::Postman(string name) : id(idValue) {
    idValue++;
    this->name = name;
    this->myMail.clear();
}

bool Postman::operator<(const Postman &p2) {
    typename vector<Mail *>::const_iterator it1 = this->myMail.begin(), it2 = p2.myMail.begin();
    vector<string> v1, v2;

    for (; it1 != this->myMail.end(); it1++)
        v1.push_back((*it1)->getZipCode());
    for (; it2 != p2.myMail.end(); it2++)
        v2.push_back((*it2)->getZipCode());

    if (numberDifferent(v1) < numberDifferent(v2))
        return true;
    else
        return false;
}




