#ifndef PROJECT_MENUS_H
#define PROJECT_MENUS_H

#include <iostream>
#include <iomanip>
#include "Person.h"
#include "Utils.h"
//#include "School.h"
#include "bst.h"
class School;
class Classes;
class Course;
class Material;
class Loan;

/**
 * @brief School Sorting Menu
 * @return Option of the menu
 */
int sortingSchoolsMenu();

int schoolMenu(vector<string> schools);

/**
 * @brief Main menu
 * @return Option of the menu
 */
int mainMenu();
/**
 * @brief Management Menu
 * @return Option of the menu
 */
int ManagementMenu();
/**
 * @brief Clients Menu
 * @return Option of the menu
 */
int ClientsMenu();
/**
 * @brief Teachers Menu
 * @return Option of the menu
 */
int TeachersMenu();
/**
 * @brief Activities Menu
 * @return Option of the menu
 */
int ActivityMenu();
/**
 * @brief Materials Menu
 * @return Option of the menu
 */
int MaterialsMenu();
/**
 * @brief Info Menu
 * @return Option of the menu
 */
int InfoMenu();
/**
 * @brief Time Table Menu
 * @return Option of the menu
 */
int timeTableMenu();
/**
 * @brief Other Menu
 * @return Option of the Menu
 */
int otherMenu();
/**
 * @brief Technicians Menu
 * @return Option of the Menu
 */
int TechniciansMenu();

/**
 * @brief Function that checks if the option selected exists
 * @return Option of the Menu
 */
int ieMenu(int);

/**
 * @brief Function to choose a Person from a vector
 * @tparam N Type of Person (Client or Teacher)
 * @param vec Vector with Persons of type N
 * @return The chosen person
 */
template <class N>
int choosePerson(vector<N*> vec) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "List" << endl;
    cout << "__________________________________________________\n" << endl;

    typename vector<N *>::const_iterator it = vec.begin();
    int i = 1;

    for (; it != vec.end(); it++, i++)
        cout << i << " - " <<  (*it)->getName() << endl;

    cout << "\n0 - Back\n";
    cout << "__________________________________________________\n" << endl;

    return ieMenu(i);
}

/**
 * @brief Function to choose a list of classes
 * @param classes Vector with all the classes
 * @return The chosen classes
 */
vector<Classes *> chooseClasses(vector<Classes *> classes);

/**
 * @brief Function to choose a list of materials
 * @param classes Vector with all the classes
 * @param materials Vector with all the materials
 * @param startTime Time to rent
 * @param day Day of the week
 * @return The choosen Materials
 */
vector<Material *> chooseMaterials(vector<Classes *> classes, vector<Material *> materials, Time startTime, string day, vector<Loan *> loans, int week, vector<Course *> courses);

#endif //PROJECT_MENUS_H
