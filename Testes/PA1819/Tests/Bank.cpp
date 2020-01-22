/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

double Bank::getWithdraw(string cod1) const{
	double ret = 0;
	typename vector<Account *>::const_iterator it;

	for(it = accounts.begin(); it != accounts.end(); it++) {
	    if ((*it)->getCodH() == cod1)
            ret += (*it)->getWithdraw();
	}

	return ret;
}


vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	res.clear();

	typename vector<BankOfficer>::const_iterator it = bankOfficers.begin();

	for (; it != bankOfficers.end(); it++) {
	    if ((*it).getName() == name) {
	        res = (*it).getAccounts();
	        break;
	    }
	}
    if (it == bankOfficers.end())
        return res;

	bankOfficers.erase(it);
	return res;
}


const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *bo= new BankOfficer();
    bool found = false;

    for (int i = 0; i < bankOfficers.size(); i++) {
        if (name == bankOfficers[i].getName()) {
            found = true;
            bankOfficers[i].addAccount(ac);
            *bo = bankOfficers[i];
        }
    }

    if (!found)
        throw NoBankOfficerException(name);

    return *bo;
}


void Bank::sortAccounts() {
    for(int i = 1; i < accounts.size(); i++) {
        Account* tmp = accounts[i];
        int j;
        for (j = i; j > 0 && tmp->getBalance() <= accounts[j-1]->getBalance(); j--) {
            if (tmp->getBalance() < accounts[j]->getBalance())
                accounts[j] = accounts[j-1];
            else if (tmp->getBalance() == accounts[j]->getBalance() && tmp->getCodIBAN() < accounts[j]->getCodIBAN())
                accounts[j] = accounts[j-1];
        }
        accounts[j] = tmp;
    }
}



