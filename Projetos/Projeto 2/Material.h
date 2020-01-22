#ifndef PROJECT_MATERIAL_H
#define PROJECT_MATERIAL_H

#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Utils.h"
#include "Manager.h"
//#include "School.h"
class Classes;
class Course;
class Loan;

using namespace std;


/**
 * @defgroup material material
 * @{
 *
 *  Class necessary to handle a material
 */

/**
 *  @brief A class used to represent a material.
 *
 *  Each Material object has a type, a price, a total amount, a used amount and an id
 *
 */
class Material {
    /**
     * @brief Type of material
     */
    string type;
    /**
     * @brief Price per 45 minutes of use.
     */
    const double price;
    /**
     * @brief amount of this type of objects in the inventory
     */
    int totalAmount;
     /**
      * @brief amount of this type of objects being used in activities
      */
     int usedAmount;
     /**
      * @brief ID of the material
      */
    const int ID;
    /**
     * @brief ID of the next material
     */
    static int nextID;
    /**
     * @brief Checks if the material exists or not
     */
     bool existing;
public:
    /**
     * @brief Default Constructor
     */
    Material();
    /**
     * @brief Contructor
     * @param type Type of material
     * @param price Price
     * @param amount Amount of materials
     * @param used Amount materials being used
     * @param existing Checks if the material exists/previously existed
     */
    Material(string type, double price, int amount, int used, bool existing);

    /*** GET METHODS ***/
    string getType() const;
    double getPrice() const;
    int getTotal() const;
    int getUsed() const;
    int getID() const;
    bool getExisting() const;

    /*** SET METHODS ***/
    void setType(string type);
    void setTotal(int total);
    void setUsed(int used);
    void setExisting(bool existing);

    /**
     * @brief Function to write to the classes file
     * @return String with the line to write to the file
     */
    string WriteToFile() const;
};

/**
 * @brief Collision function for materials
 */
struct eqmtrl{
    bool operator() (const Material *m1, const Material *m2) const{
        return m1->getType()==m2->getType();
    }
};
/**
 * @brief Hash function for materials
 */
struct hashmtrl{
    int operator() (const Material *m1) const{
        return m1->getID()%10;
    }

};

typedef unordered_set<Material*,hashmtrl,eqmtrl> MaterialHashTable;

//----------------------------------------------------------------------------------------------------------------------

/**@}*/
#endif //PROJECT_MATERIAL_H
