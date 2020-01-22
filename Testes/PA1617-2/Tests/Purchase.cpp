/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article * a = new Article(this->client,barCode);

    (*a).setPresent(present);
    (*a).setDeliverHome(deliverHome);

	return a;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	list<stack<Article *>>::iterator itB = this->bags.end();
	itB--;

	if ((*itB).size() < BAG_SIZE)
        (*itB).push(article);
	else {
	    stack<Article *> newBag;
	    newBag.push(article);
	    bags.push_back(newBag);
	}

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;
	vector<Article*> temp;
	list<stack<Article *>>::iterator itB = bags.begin();

	for (; itB != bags.end(); itB++) {
        while (!(*itB).empty()) {
            if ((*itB).top()->getPresent())
                presents.push_back((*itB).top());
            else
                temp.push_back((*itB).top());
            (*itB).pop();
        }

        for (int i = temp.size(); i > 0; i--) {
            (*itB).push(temp[i-1]);
        }

        temp.clear();
	}

	return presents;

}

