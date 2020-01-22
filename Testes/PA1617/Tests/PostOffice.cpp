/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name) {
    vector<Mail *> ret;
    vector<Postman>::iterator it = postmen.begin();
    bool found = false;

    for(; it != postmen.end(); it++) {
        if ((*it).getName() == name) {
            found = true;
            break;
        }
    }

    if (found) {
        ret = (*it).getMail();
        postmen.erase(it);
    }

    return ret;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
    typename vector<Mail *>::iterator it = mailToSend.begin();
    balance = 0;
    vector<Mail *> ret;

    for (; it != mailToSend.end(); it++) {
        balance += (*it)->getPrice();
        if ((*it)->getZipCode() > firstZipCode && (*it)->getZipCode() < lastZipCode)
            addMailToDeliver(*it);
        else
            ret.push_back(*it);
    }

    mailToSend.clear();
    return ret;
}

Postman PostOffice::addMailToPostman(Mail *m, string name) {
    vector<Postman>::iterator it;
    bool found = false;

    for (it = postmen.begin(); it != postmen.end(); it++) {
        if ((*it).getName() == name) {
            found = true;
            break;
        }
    }

    if (!found)
        throw NoPostmanException(name);

    (*it).addMail(m);
    return (*it);
}


