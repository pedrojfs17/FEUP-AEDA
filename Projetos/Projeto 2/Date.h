#ifndef PROJECT_DATE_H
#define PROJECT_DATE_H

#include <string>

using namespace std;

/**
 * @defgroup date date
 * @{
 *
 *  Class necessary to handle a date
 */

/**
 *  @brief A class used to represent a date.
 *
 *  Each Date object has a year, a month and a day
 *
 */
class Date {
    /**
     * @brief Year
     */
    int year;
    /**
     * @brief Month
     */
    int month;
    /**
     * @brief Day
     */
    int day;
public:
    /**
     * @brief Default constructor
     *
     * Year, month and day are initialized at 0.
     */
    Date();
    /**
     * @brief Constructor
     *
     * This constructor is called when given a string of the type DD/MM/YYYY or DD-MM-YYYY
     *
     * @param date Date
     */
    Date(string date);
    /**
     * @brief Constructor
     *
     * This constructor is called when given three integers.
     *
     * @param year Year
     * @param month Month
     * @param day Day
     */
    Date(int year, int month, int day);
    /**
     * @brief Checks if the date is valid
     * @return True if valid or False otherwise.
     */
    bool validDate() const;

    /*** GET METHODS ***/
    string getDate() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    /*** SET METHODS ***/
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
};
/**@}*/

#endif //PROJECT_DATE_H
