#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H

#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <regex>
#include "Date.h"
#include "Address.h"
#include "Time.h"
//#include "School.h"

using namespace std;

/***
 * @brief Function to read a number from the console
 * @param msg Message to display on the screen
 * @return Number
 */
int readNumber(string msg);

/***
 * @brief Function to read a double number from the console
 * @param msg Message to display on the screen
 * @return Number
 */
double readDouble(string msg);

/***
 * @brief Function to read a string with special characters from the console
 * @param msg Message to display on the screen
 * @return String
 */
string readString(string msg);

/***
 * @brief Function to read a string without special characters from the console
 * @param msg Message to display on screen
 * @return String
 */
string readStringNoSpecial(string msg);

/***
 * @brief Function to read a date
 * @return Date
 */
Date readDate();

/***
 * @brief Function to read an hour
 * @return Time
 */
Time readTime();

/***
 * @brief Function to read an address
 * @return Address
 */
 Address readAddress();

 /***
  * @briefFunction to read a postal code
  * @return Postal code
  */
 string readPostalCode(string msg);

 string readEmail();

/***
 * @brief Check for Input Errors in Menus
 *
 * @return Menu Option
 */
int ieMenu(int maxOption);

/***
 * Check if it is a leap year.
 *
 * @param year Year
 * @return True if it is a leapYear, False otherwise
 */
bool leapYear(int year);

/***
 * @brief Check the age of a person
 *
 * @param birthDate Birth Date
 * @return Age (in years)
 */
int findAge(Date birthDate);

/***
 * @brief Function to convert a string to Uppercase
 * @param msg String to be converted
 * @return Uppercase string
 */
string toUpper(string msg);

#endif //PROJECT_UTILS_H
