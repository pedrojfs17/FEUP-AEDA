#ifndef PROJECT_ADDRESS_H
#define PROJECT_ADDRESS_H

#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;
/**
 * @defgroup address address
 * @{
 *
 *  Class necessary to handle an address
 */

/**
 * @brief A class use to represent an address
 *
 * Every address has a street, a door number, a floor, a postal-code and a location.
 */
class Address {
    /**
     * @brief Street
     */
    string street;
    /**
     * @brief Door Number
     */
    string door;
    /**
     * @brief Floor
     *
     * The floor is set to '-' if it is a house.
     */
    string floor;
    /**
     * @brief Postal-code
     */
    string postalCode;
    /**
     * @brief City / Location
     */
    string location;
public:
    /**
     * @brief Default Constructor
     */
    Address();
    /**
     * @brief Constructor
     * @param street Street
     * @param door Door Number
     * @param floor Floor
     * @param postal Postal-code
     * @param location City / Location
     */
    Address(string street, string door, string floor, string postal, string location);
    /**
     * @brief Constructor
     *
     * @param line Line on the form: Street, Door, Floor, Postal-code, Location
     */
    Address(string line);

    /*** GET METHODS ***/
    string getStreet() const;
    string getDoor() const;
    string getFloor() const;
    string getPostalCode() const;
    string getLocation() const;
    string getFullAddress() const;

    /*** SET METHODS ***/
    void setStreet(string street);
    void setDoor(string door);
    void setFloor(string floor);
    void setPostalCode(string postalCode);
    void setLocation(string  location);

    /**
     * @brief Function to get the string to write to the file
     * @return String
     */
    string WriteToFile() const;

    /**
     * @brief Function to check if the address is valid.
     * @return True if it is, false otherwise
     */
    bool validAddress() const;

    /**
     * @brief Function to check if the postal code is valid.
     * @return True if it is, false otherwise
     */
    bool validPostcode() const;
};
/**@}*/

#endif //PROJECT_ADDRESS_H
