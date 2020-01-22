//
// Created by pedro on 24/12/2019.
//

#include "HashTable.h"
/*
bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i*i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

int nextPrime(int num) {
    // Base case
    if (num <= 1)
        return 2;

    int prime = num;
    bool found = false;

    // Loop continuously until isPrime returns
    // true for a number greater than n
    while (!found) {
        prime++;

        if (isPrime(prime))
            found = true;
    }

    return prime;
}

int teacherHash(const Teacher x, int tableSize) {
    return x.getNIF() % tableSize;
}

TeacherHashTable::TeacherHashTable(Teacher *notFound, int size): ITEM_NOT_FOUND(notFound), array(nextPrime(size)), currentSize(0) {}

TeacherHashTable::TeacherHashTable(const TeacherHashTable &ht): ITEM_NOT_FOUND(ht.ITEM_NOT_FOUND),array(ht.array),currentSize(ht.currentSize){}

Teacher *TeacherHashTable::find(const Teacher &x) const {
    int currentPos = findPos(x);
    if ( isActive(currentPos) )
        return array[currentPos].element;
    else return ITEM_NOT_FOUND;
}

void TeacherHashTable::makeEmpty() {
    currentSize = 0;
    for ( int i = 0; i < array.size(); i++ )
        array[i].info = EMPTY;
}

void TeacherHashTable::insert(Teacher *x) {
    int currentPos = findPos((*x));
    if ( isActive(currentPos) ) return;
    array[currentPos] = HashEntry(x, ACTIVE);
    if ( ++currentSize > array.size()/2 ) rehash();
}

void TeacherHashTable::remove(const Teacher &x) {
    int currentPos = findPos(x);
    if ( isActive(currentPos) )
        array[currentPos].info = DELETED;
}

bool TeacherHashTable::isActive(int currentPos) const {
    return ( array[currentPos].info == ACTIVE );
}

int TeacherHashTable::findPos(const Teacher &x) const {
    int collisionNum = 0;
    int currentPos = teacherHash(x, array.size());
    while( array[currentPos].info != EMPTY && array[currentPos].element->getNIF() != x.getNIF() ) {
        currentPos += 2 * ++collisionNum - 1;
        if ( currentPos >= array.size() )
            currentPos -= array.size();
    }
    return currentPos;
}

void TeacherHashTable::rehash() {
    vector<HashEntry> oldArray = array;
    array.resize(nextPrime(2 * oldArray.size()));
    for( int j = 0; j < array.size(); j++ )
        array[j].info = EMPTY;
    currentSize = 0;
    for( int i = 0; i < oldArray.size(); i++ )
        if ( oldArray[i].info == ACTIVE )
            insert(oldArray[i].element);
}

vector<Teacher> TeacherHashTable::getDeleted() const {
    vector<Teacher> temp;
    for(auto x :array){
        if(x.info==DELETED){
            temp.push_back((*x.element));
        }
    }
    return temp;
}
*/






