#ifndef AEDAPROJECT_MANAGER_H
#define AEDAPROJECT_MANAGER_H

#include <vector>

using namespace std;

/**
 * @brief Exception Not Found
 * @tparam N Type of object not found
 */
template <class N>
class NotFound{
public:
    NotFound(){"Object not found!";}
};

/**
 * @brief Template function to add an element to a vector
 * @tparam N Type of elements
 * @param ele_vec Vector
 * @param element Element to add
 */
template <class N>
void addN(vector<N*> &ele_vec, N *element ){
    ele_vec.push_back(element);
}

/**
 * @brief Template function to remove an element of a vector
 * @tparam N Type of elements
 * @param ele_vec Vector
 * @param element Element to be removed
 */
template <class N>
void removeN(vector<N*> &ele_vec, N *element ){
    typename vector<N*> ::iterator x =ele_vec.begin();

    for(;x!=ele_vec.end();x++){
        if((*x)==(element)){
            ele_vec.erase(x);
            return;
        }
    }
    throw NotFound<N>();
}

#endif //AEDAPROJECT_MANAGER_H
