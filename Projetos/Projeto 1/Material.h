#ifndef PROJECT_MATERIAL_H
#define PROJECT_MATERIAL_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Utils.h"
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
     */
    Material(string type, double price, int amount, int used);

    /*** GET METHODS ***/
    string getType() const;
    double getPrice() const;
    int getTotal() const;
    int getUsed() const;
    int getID() const;

    /*** SET METHODS ***/
    void setType(string type);
    void setTotal(int total);
    void setUsed(int used);

    /**
     * @brief Function to write to the classes file
     * @return String with the line to write to the file
     */
    string WriteToFile() const;
};

//----------------------------------------------------------------------------------------------------------------------

/**
 * @brief Function to search a material
 * @param vec Vector with all the materials
 * @return The position of the wanted material
 */
vector<Material *>::const_iterator searchMaterial(vector<Material *> &vec);

/**
 * @brief Function to create a material
 * @param vec Vector with all the materials
 */
void CreateMaterial(vector<Material *> &vec);

/**
 * @brief Function to modify a material
 * @param vec Vector with all the materials
 */
void ModifyMaterial(vector<Material *> &vec);

/**
 * @brief Function to remove a material
 * @param vec Vector with all the materials
 */
void RemoveMaterial(vector<Material *> &vec);

/**
 * @brief Function to update the materials that are being used at a certain time
 * @param classes Vector with all the classes
 * @param materials Vector with all the materials
 * @param startTime Time
 * @param day Day of the week
 */
void updateMaterialsUsed(vector<Classes *> classes, vector<Material *> &materials, Time startTime, string day, vector<Loan *> loans, int week, vector<Course *> courses);
/**@}*/
#endif //PROJECT_MATERIAL_H
