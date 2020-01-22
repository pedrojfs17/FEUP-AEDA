/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) const {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		cout<<"Added "<<book->getTitle()<<endl;
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
        cout<<"Added "<<book->getTitle()<<endl;
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
    vector<Book *> temp = books;
    books.clear();

    for (auto x : temp)
        addCatalogItem(x);
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
	//TODO:
	//...
    BookCatalogItem b = getCatalogItem(book->getTitle(),book->getAuthor());

    for (auto x : b.getItems()) {
        if (x->getReader() == NULL)
            temp.push_back(x);
    }

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	//TODO:
	//...

	vector<Book*> available = getAvailableItems(book);

	if (available.empty())
	    return false;

	available[0]->setReader(reader);
	reader->addReading(book->getTitle(),book->getAuthor());

	return true;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	//TODO:
	//...
    userRecords.insert(user);
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	//TODO:
	//...
    user->setEMail(newEMail);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	//TODO:
	//...
	int num = 0;

    for(auto x : candidates) {
        num = x.getReadings().size();
        if (x.getReading().first != "" && x.getReading().second != "")
            num++;
        if (num >= min)
            readerCandidates.push(x);
    }
}

int ReadingClub::awardReaderChampion(User& champion) {
	//TODO:
	//...

	if (readerCandidates.empty())
	    return 0;

	else if (readerCandidates.size() == 1) {
	    champion = readerCandidates.top();
	    return 1;
	}

	User first = readerCandidates.top();
	readerCandidates.pop();
	User second = readerCandidates.top();
	readerCandidates.push(first);

	if(first.numReadings() > second.numReadings()) {
        champion = first;
        return readerCandidates.size();
	}

	return 0;
}
























