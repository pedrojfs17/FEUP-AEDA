#ifndef PROJECT_ACTIVITY_H
#define PROJECT_ACTIVITY_H

#include "Date.h"
#include "Time.h"
#include "Utils.h"
#include "Menus.h"
#include "Material.h"
#include "Person.h"

class School;
class Material;
class Client;
class Teacher;


/**
 * @defgroup activity activity
 * @{
 *
 *  Group of classes necessary to handle an activity
 */

/**
 *  @brief A class used to represent an activity.
 *
 *  Each activity object has a name, a date and an hour
 *
 *  @see Classes Course Trip Loan
 */
class Activity {
protected:
    /**
     * @brief name, the activity's name
     */
    string name;
    /**
     * @brief materials, vector with all the materials needed for the activity
     */
    vector <Material *> materials;
    /**
     * @brief attendees, vector with all the clients that will attend this activity
     */
    vector <Client *> attendees;
    /**
     * @brief price, the cost to attend this activity
     */
     const double price;
     /**
      *@brief max_attendees, the max attendance for the activity
      */
     int max_attendees;
public:
    /**
     *@brief Default constructor
     */
    Activity();
    /**
     * @brief Constructor
     * @param name Name of the activity
     * @param price Price of the activity
     */
    Activity(string name, double price);
    /**
     * @brief Constructor
     * @param name Name of the activity
     * @param price Price of the activity
     */
    Activity(string name, string price);

    /*** GET METHODS ***/
    string getName() const;
    virtual string getActivity() const;
    vector <Client *> getAttendees() const;
    int getMaxAttendees() const;
    vector<Material *> getMaterials() const;
    double getPrice() const;

    /*** SET METHODS ***/
    void setName(string name);

    /**
     * @brief pure virtual method
     */
    virtual string WriteToFile() = 0;
     /**
      * @brief member that adds a client to this activity
      */
     void addAttendee(Client *c);
};
/**@}*/

//----------------------------------------------------------------------------------------------------------------------

/**
 * @addtogroup activity
 * @{
 *
 *  Class necessary to handle classes
 */
/**
*  @brief A class used to represent classes.
*
*  Each classes object has an id, a teacher, an annual boolean, a day, a tarting time and a double class boolean
*
*/
class Classes : public Activity {
    /**
    * @brief id, the class's number id
    **/
    int id;
    /**
	 * @brief next_id, the next activity's id, not used for classes
	 **/
    static int next_id;
    /**
     * @brief Teacher assigned to this class
     */
    Teacher *teacher;
    /**
      * @brief annual, if the activity is part of an annual course
      */
    bool annual;
    /**
     * @brief day of the week of this class
     */
    string day;
    /**
     * @brief Hour that the class starts
     */
    Time startTime;
    /**
     * @brief True if the class duration is 1h30m or false if it is 45m
     */
    bool doubleClass;
public:
    /**
     * @brief Default Constructor
     */
    Classes();
    /**
     * @brief Constructor
     * @param name Name of the class
     */
    Classes(string name);
    /**
     * @brief Constructor
     * @param name Name of the class
     * @param annual True if the class is part of the annual plan
     * @param time Hour that this class starts
     * @param day Day of the week
     * @param doubleClass True if the class is 90min, False if it is only 45min
     * @param price Price of this class
     * @param id ID of the class
     * @param materialsNeeded List of the materials needed for this class
     */
    Classes(string name, string annual, string time, string day, string doubleClass, string price, string id, vector<Material *> materialsNeeded);
    /**
     * @brief Constructor
     * @param name Name of the class
     * @param time Hour that the class starts
     * @param day Day of the week
     * @param doubleClass True if the class is 90min, False if it is only 45min
     * @param price Price of this class
     * @param materialsNeeded List of the materials needed for this class
     */
     Classes(string name, Time time, string day, bool doubleClass, double price, vector<Material *> materialsNeeded);

    /*** GET METHODS ***/
    int getID() const;
    string getActivity() const;
    bool getAnnual() const;
    string getDay() const;
    Time getStartTime() const;
    bool getDoubleClass() const;
    Teacher * getTeacher() const;

    /*** SET METHODS ***/
    void setMaterial(vector<Material *> material);
    void setTeacher(Teacher * teacher);
    void setTime(Time time);
    void setDay(string day);
    void setDoubleClass(bool db);
    void setAnnual(bool annual);

    /**
     * @brief overload of operator<<
     * @param out Ostream
     * @param c Class to be written to file
     * @return ostream
     */
    friend ostream& operator<<(ostream &out, Classes const &c);

    /**
     * @brief Function to write to the classes file
     * @return String with the line to write to the file
     */
    string WriteToFile();
};
/*! @} */
//----------------------------------------------------------------------------------------------------------------------

/**
 * @addtogroup activity
 * @{
 *
 *  Class necessary to handle a course
 */
/**
*  @brief A class used to represent a course.
*
*  Each course object has a vector of classes and a number of weeks
*
*/
class Course : public Activity {
    /**
     * @brief Vector with the classes that belong to this course
     */
    vector<Classes *> classes;
    /**
     * @brief Number of weeks this course lasts
     */
    int numWeeks;
public:
    /**
     * @brief Constructor
     * @param classes Vector with the classes that belong to this course
     * @param numWeeks Number of weeks this course lasts
     */
    Course(vector<Classes *> classes, string numWeeks);
    /**
     * @brief Constructor
     * @param name Name of this course
     * @param price Price of this course
     * @param classes Vector with the classes that belong to this course
     * @param numWeeks Number of weeks this course lasts
     */
    Course(string name, double price, vector<Classes *> classes, int numWeeks);
    /**
     * @brief Constructor
     * @param name Name of this course
     * @param price Price of this course
     * @param classes Vector with the classes that belong to this course
     * @param numWeeks Number of weeks this course lasts
     */
    Course(string name, string price, vector<Classes *> classes, string numWeeks);

    /*** GET METHODS ***/
    string getActivity() const;
    vector<Classes *> getClasses() const;
    int getNumWeeks() const;

    /*** SET METHODS ***/
    void setClasses(vector<Classes *> classes);
    void setNumWeeks(int nw);

    /**
     * @brief overload of operator<<
     * @param out Ostream
     * @param c Course to be written to file
     * @return ostream
     */
    friend ostream& operator<<(ostream &out, Course const &c);

    /**
     * @brief Function to write to the classes file
     * @return String with the line to write to the file
     */
    string WriteToFile();
};
/*! @} */
//----------------------------------------------------------------------------------------------------------------------
/**
 * @addtogroup activity
 * @{
 *
 *  Class necessary to handle a trip
 */
/**
*  @brief A class used to represent a trip.
*
*  Each trip object has an id, a location, a begin date,an end date, a number of days and a price
*
*/
class Trip : public Activity {
    /**
     * @brief ID of this trip
     */
    int id;
    /**
     * @brief IF of the next trip to be created
     */
    static int next_id;
    /**
     * @brief Location of this trip
     */
    string location;
    /**
     * @brief Begin Date
     */
    Date beginDate;
    /**
     * @brief End Date
     */
    Date endDate;
    /**
     * @brief Number of days this trip lasts
     */
    int numDays;
    /**
     * @brief Price of this trip
     */
    double price;
public:
    /**
     * @brief Constructor
     * @param name Name of the trip
     * @param location Location of the trip
     * @param beginDate Begin Date of the trip
     * @param endDate End Date of the trip
     * @param price Price of the trip
     * @param maxAttendees Maximum number of attendees of the trip
     */
    Trip(string name, string location, Date beginDate, Date endDate, double price, int maxAttendees);

    /*** GET METHODS ***/
    int getID() const;
    string getActivity() const;
    Date getBeginDate() const;
    Date getEndDate() const;
    string getLocation() const;

    /*** SET METHODS ***/
    void setLocation(string location);
    void setBeginDate(Date begin);
    void setEndDate(Date end);
    void setMaxAttendees(int max);

    /**
     * @brief overload of operator<<
     * @param out Ostream
     * @param t Trip to be written to file
     * @return ostream
     */
    friend ostream& operator<<(ostream &out, Trip const &t);

    /**
     * @brief Function to write to the classes file
     * @return String with the line to write to the file
     */
    string WriteToFile();
};
/*! @} */
//----------------------------------------------------------------------------------------------------------------------
/**
 * @addtogroup activity
 * @{
 *
 *  Class necessary to handle a loan
 */
/**
*  @brief A class used to represent a loan.
*
*  Each loan object has a vector of rented materials, a day, a time, a client's nif and a week
*
*/
class Loan : public Activity {
    /**
     * @brief material to be rented
     */
    vector<Material *> rented_material;
    /**
     * @brief day in which the materials will be rented
     */
    string day;
    /**
     * @brief the time of the day the materials will be rented
     */
    Time time;
    /**
     * @brief the nif of the client that wants to rent the material
     */
    int clientsNIF;
    /**
     * @brief the week in which the materials will be rented
     */
    int week;
public:
    /**
     * @brief Constructor
     * @param name Name of the loan
     * @param day Day of the loan
     * @param time Time of the loan
     * @param rent_mat  Materials rented
     * @param clientsNIF NIF of the client that wants to make the loan
     * @param price Price of the loan
     * @param week Week of the loan
     */
    Loan(string name, string day, Time time, vector<Material *> rent_mat, int clientsNIF, double price, int week);

    /*** GET METHODS ***/
    string getDay() const;
    Time getTime() const;
    int getWeek() const;
    int getClientsNIF() const;
    string getActivity() const;

    /**
     * @brief Prints loan in a formatted manner
     *
     * @return String with loan information
     */
    string showLoan() const;

    /**
     * @brief Function to write to the classes file
     * @return String with the line to write to the file
     */
    string WriteToFile();
};
/*! @} */
//----------------------------------------------------------------------------------------------------------------------

string readString(string);
string toUpper(string);
/**
 * @addtogroup activity
 * @{
 *
 *  Functions to handle an activity
 */
/**
 * @brief Template function to find an activity in a vector
 * @tparam P Type of the activity
 * @param vec Vector with activities of type P
 * @return The activity to find
 */
template <class P>
P * FindActivity(vector<P *> &vec){
    string search_name;
    bool found=false;

    search_name = readString("Activity's name (\"back\" - Back): ");

    if (toUpper(search_name) == "BACK")
        return NULL;

    typename vector<P *> ::const_iterator it=vec.begin();

    for(it;it!=vec.end();it++){
        if((*it)->getName()==search_name){
            found=true;
            break;
        }
    }

    if(!found){
        throw NotFound<P>();
    }

    return *it;
}



/**
 * @brief Function to filter the classes for a certain week
 * @param week week to filter
 * @param classes Vector of classes in said week
 * @param courses Vector of courses in said week
 * @return Vector of classes of said week
 */
vector<Classes *> getWeekClasses(int week, vector<Classes *> classes, vector<Course *> courses);

/**
 * @brief Function to compare two classes by time
 * @param class1 First Class
 * @param class2 Second Class
 * @return True if First Class is before Second Class
 */
bool CompareTwoClassesByTime(Classes * class1, Classes * class2);

/**
 * @brief Function to update the materials that are being used at a certain time
 * @param classes Vector with all the classes
 * @param materials Vector with all the materials
 * @param startTime Time
 * @param day Day of the week
 */
void updateMaterialsUsed(vector<Classes *> classes, vector<Material *> &materials, Time startTime, string day, vector<Loan *> loans, int week, vector<Course *> courses);

/*! @} */
#endif //PROJECT_ACTIVITY_H
