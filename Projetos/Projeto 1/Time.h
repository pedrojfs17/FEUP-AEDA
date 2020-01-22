#ifndef AEDAPROJECT_HOUR_H
#define AEDAPROJECT_HOUR_H

#include <string>

using namespace std;

/**
 * @defgroup time time
 * @{
 *
 *  Class necessary to handle time
 */

/**
 *  @brief A class used to represent time.
 *
 *  Each time object has an hour and a minute
 */
class Time {
    /**
     * @brief Hour
     */
    int hour;
    /**
     * @brief Minute
     */
    int minute;
public:
    /**
     * @brief Default constructor
     * Hour and Minute are initialized at 0.
     */
    Time();

    /**
     * @brief Constructor
     * This constructor is called when given a string of the type HH:MM or HH"h"MM"m"
     * @param time Time
     */
    Time(string time);

    /**
     * @brief Constructor
     * @param hour Hour
     * @param minute Minute
     */
    Time(int hour, int minute);

    /**
     * @brief Checks if the time is valid
     * @return True if valid or False otherwise.
     */
    bool validTime() const;

    /*** GET METHODS ***/
    string getTime() const;
    int getHour() const;
    int getMinute() const;

    /*** SET METHODS ***/
    void setHour(int hr);
    void setMinutes(int min);

    /*** OPERATOR OVERLOADING ***/
    Time operator+(Time const &t2);
    Time operator-(Time const &t2);
    bool operator<(Time const &t2);
};
/**@}*/
#endif //AEDAPROJECT_HOUR_H
