#ifndef PROJECT_SCHOOL_H
#define PROJECT_SCHOOL_H

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <string.h>
#include "Activity.h"
#include "Material.h"
#include "Time.h"
#include "Date.h"
#include "Address.h"
#include "Person.h"
class Person;
class Client;
class Teacher;
class Activity;
class Classes;
class Course;
class Trip;
using namespace std;
/**
 * @defgroup school school
 * @{
 *
 *  Class necessary to handle a school
 */

/**
 *  @brief A class used to represent a school.
 *
 *  Each school has a clients vector, a teachers vector, an activities vector, a classes vector, a courses vector, a trips vector, a loans vector and a materials vector
 *
 *  @see Person Activity Material
 */
class School{
    /**
     * @brief client's registered in the school
     */
    vector<Client*> clients;
    /**
     * @brief teachers that work in the school
     */
    vector<Teacher*> teachers;
    /**
     * @brief the school's activities
     */
    vector <Activity*> activities;
    /**
     *@brief the school's classes
     */
     vector <Classes *> classes;
    /**
    *@brief the school's courses
    */
     vector <Course *> courses;
    /**
    *@brief the school's trips
    */
     vector <Trip *> trips;
    /**
    *@brief the school's loans
    */
     vector <Loan *> loans;
    /**
     * @brief the school's material
     */
    vector<Material*> materials;
public:
    /**
     * @brief Default constructor
     */
    School()= default;
    /**
     * @brief Constructor
     *
     * The constructor creates a school with the data passed as an argument
     *
     * @param clients_file The file that contains the clients
     * @param teachers_file The file that contains the teachers
     * @param classes_file The file that contains the classes
     * @param courses_file The file that contains the courses
     * @param trips_file The file that contains the trips
     * @param material_file The file that contains the materials
     * @param loans_file The file that contains the loans
     */
    School(istream &clients_file, istream &teachers_file, istream &classes_file, istream &courses_file, istream &trips_file, istream &material_file, istream &loans_file);
    /**
     * @brief Default destructor
     */
    ~School();

     /*** PRINT METHODS ***/
     void PrintAllClients();
     void PrintClient();
     void PrintAllTeachers();
     void PrintTeacher();
     void PrintAllActivities();
     void PrintAllLoans();
     void PrintTrips();
     void PrintClientTimeTable();
     void PrintTeacherTimeTable();
     void PrintAllClassesTimeTable();

     /**
      * @brief Function to simulate the monthly email made for the client
      */
     void sendEmail();

     /*** ADD METHODS ***/
     void addClient(Client * client);
     void addTeacher(Teacher * teacher);
     void addActivity(Activity * activity);
     void addClass(Classes * classes);
     void addCourse(Course * course);
     void addTrip(Trip * trip);
     void addMaterial(Material * material);

     /*** GET METHODS ***/
     vector<Client*> getClients() const;
     vector<Teacher*> getTeachers() const;
     vector<Activity*> getActivities() const;
     vector<Material*> getMaterials() const;
     vector<Classes *> getClasses() const;
     vector<Course *> getCourses() const;
     vector<Trip *> getTrips() const;
     vector<Loan *> getLoans() const;

     /*** SET METHODS ***/
     void setClients(vector<Client *> clients);
     void setTeachers(vector<Teacher *> teachers);
     void setClasses(vector<Classes *> classes);
     void setCourses(vector<Course *> courses);
     void setTrips(vector<Trip *> trips);
     void setMaterials(vector<Material *> materials);
     void setLoans(vector<Loan *> loans);

     /**
      * @brief function that assigns all the teachers to the classes in a balanced way
      * @param classes Vector of classes
      * @param teachers Vector of teachers
      */
    void AssignTeachers(vector<Classes *> classes, vector<Teacher *> teachers);
    /**
     * @brief function to assign the loans, read from the loans file, to their respective clients
     */
    void AssignLoans();
    /**
     * @brief sorts classes by hour
     */
    void sortClassesByHour();
    /**
     * @brief sorts classes by id
     */
    void sortClassesByID();
};
/**@}*/

#endif //PROJECT_SCHOOL_H
