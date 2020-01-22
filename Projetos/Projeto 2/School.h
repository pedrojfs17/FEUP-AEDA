#ifndef PROJECT_SCHOOL_H
#define PROJECT_SCHOOL_H

#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <string>
#include <process.h>
#include <dir.h>
#include <filesystem>
#include <unordered_set>
#include <queue>
#include <random>
#include "Activity.h"
#include "Material.h"
#include "Time.h"
#include "Date.h"
#include "Address.h"
#include "Person.h"
#include "bst.h"
#include "HashTable.h"
class Person;
class Technician;
class Client;
class Teacher;
class Activity;
class Classes;
class Course;
class Trip;
//class TeacherHashTable;
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
protected:
    /**
     * @brief the location of a school
     */
    string place;
    /**
     * @brief the name of the director  of a school
     */
    string directorName;
    /**
     * @brief the number of clients of a school
     */
    unsigned int numClients;

    //unordered_set<Teacher*, TeacherHash, TeacherHash> schoolTeachers;
    /**
     * @brief the school's technicians
     */
    priority_queue<Technician *> technicians;
    /**
     * @brief the school's current and previous teachers
     */
    TeacherHashTable schoolTeachers;
    /**
     * @brief the school's current and previous materials
     */
    MaterialHashTable schoolMaterials;

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
     * @param place The school's location
     * @param directorName The name of the school's director
     * @param numClients The number of clients of the school
     */
    School(string place, string directorName, unsigned int numClients);

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
     * @param tech_file The file tahat contains the technicians
     */
    School(istream &clients_file, istream &teachers_file, istream &classes_file, istream &courses_file, istream &trips_file, istream &material_file, istream &loans_file, istream &tech_file);
    /**
     * @brief Default destructor
     */
    void exitSchool();

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
     void PrintTechnician();
     void PrintAllTechnicians();
     void PrintPastTeachers();

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
     void addTechnician(Technician * technician);

     /*** GET METHODS ***/
     vector<Client*> getClients() const;
     vector<Teacher*> getTeachers() const;
     TeacherHashTable getHashTable() const;
     vector<Activity*> getActivities() const;
     vector<Material*> getMaterials() const;
     vector<Classes *> getClasses() const;
     vector<Course *> getCourses() const;
     vector<Trip *> getTrips() const;
     vector<Loan *> getLoans() const;
     priority_queue<Technician *> getTechnicians() const;
    string getPlace() const;
    string getDirector() const;
    unsigned int getNumClients() const;
    vector<Teacher *> getHiredTeachers() const;
    vector<Teacher *> getFiredTeachers() const;
    vector<Material *> getExistingMaterials() const;
    vector<Material *> getPastMaterials() const;


     /*** SET METHODS ***/
     void setDirector(string name);
     void setLocation(string location);
     void setnumClients(int numClients);
     void setClients(vector<Client *> clients);
     void setTeachers(vector<Teacher *> teachers);
     void setClasses(vector<Classes *> classes);
     void setCourses(vector<Course *> courses);
     void setTrips(vector<Trip *> trips);
     void setMaterials(vector<Material *> materials);
     void setLoans(vector<Loan *> loans);
     void setTechnicians(priority_queue<Technician *> technicians);

    bool operator < (const School &school1) const;

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
    /**
     * @brief Function that simulates a repair of a material
     * @return The material that was repaired
     */
    Material * repairMaterial();
};
/**@}*/

/**
 * @brief Function that loads a school, based on it's location
 * @param location location of the school
 * @return school of said location
 */
School loadSchool(string location);
/**
 * @brief Function that creates a new school, based on it's location, director's name and number of clients (creates the several txt files for clients, teachers, ...)
 * @param schoolTree Binary Tree of schools
 */
void createSchool(BST<School> * schoolTree);
/**
 * @brief Function that deletes a school (deleting the files and the directory of said school)
 * @param schoolTree Binary Tree of schools
 */
void deleteSchool(BST<School> * schoolTree);
/**
 * @brief Function that writes the schools' names to the schools.txt file
 * @param schools Binary Tree of schools
 */
void writeSchoolsFile(BST<School> * schools);

/**
 * @brief Function to create a teacher
 * @param school The school in which the teacher will be registered
 */
void CreateTeacher(School * school);
/**
 * @brief Function to modify a teacher
 * @param school The school in which the teacher will be modified
 */
void ModifyTeacher(School * school);
/**
 * @brief Function to remove a teacher
 * @param school The school in which the teacher will be removed
 */
void RemoveTeacher(School * school);

/**
 * @brief Function to create a client
 * @param vec Vector of clients
 */
void CreateClient(School * school);
/**
 * @brief Function to modify a client
 * @param vec Vector of clients
 */
void ModifyClient(School * school);
/**
 * @brief Function to remove a client
 * @param vec Vector of clients
 */
void RemoveClient(School * school);

/**
 * @brief Function to create an activity
 * @param classes Vector with the Classes
 * @param courses Vector with the Courses
 * @param trips Vector with the Trips
 * @param materials Vector with the Materials
 */
void CreateActivity(School * school);

/**
 * @brief Function to modify an activity
 * @param classes Vector with the Classes
 * @param courses Vector with the Courses
 * @param trips Vector with the Trips
 * @param materials Vector with the Materials
 */
void ModifyActivity(School * school);

/**
 * @brief Function to remove an activity
 * @param classes Vector with the Classes
 * @param courses Vector with the Courses
 * @param trips Vector with the Trips
 */
void RemoveActivity(School * school);

/**
 * @brief Function to create a technician
 * @param school The school in which the technician will be registered
 */
void CreateTechnician(School * school);
/**
 * @brief Function to modify a technician
 * @param school The school in which the technician will be modified
 */
void ModifyTechnician(School * school);
/**
 * @brief Function to remove a technician
 * @param school The school in which the technician will be removed
 */
void RemoveTechnician(School * school);


/**
 * @brief Function to search a material
 * @param vec Vector with all the materials
 * @return The position of the wanted material
 */
Material * searchMaterial(vector<Material *> &vec);

/**
 * @brief Function to create a material
 * @param school The school in which the material will be registered
 */
void CreateMaterial(School *school);

/**
 * @brief Function to modify a material
 * @param school The school in which the material will be modified
 */
void ModifyMaterial(School *school);

/**
 * @brief Function to remove a material
 * @param school The school in which the material will be removed
 */
void RemoveMaterial(School *school);



#endif //PROJECT_SCHOOL_H
