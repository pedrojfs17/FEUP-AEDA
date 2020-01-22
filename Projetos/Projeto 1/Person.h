#ifndef PROJECT_PERSON_H
#define PROJECT_PERSON_H

#include <iostream>
#include <string>
#include "Manager.h"
#include "Date.h"
#include "Address.h"
#include "Utils.h"
#include "Activity.h"
class Activity;
class Classes;
class Course;
class Trip;
class Material;
class Loan;

using namespace std;
/**
 * @defgroup person person
 * @{
 *
 *  Group of classes necessary to handle a person
 */

/**
 *  @brief A class used to represent a person.
 *
 *  Each person object has a name, a gender, a nif, a birth date, an age, an address, an e-mail and a phone
 *
 *  @see Client Teacher
 */
class Person {
//protected:
    /**
     * @brief Name
     */
    string name;
    /**
     * @brief Gender (M - male | F - female | U - undefined)
     */
    string gender;
    /**
     * @brief nif number
    */
    int nif;
    /**
     * @brief Birth Date
     */
    Date birthDate;
    /**
     * @brief Age
     */
    int age;
    /**
     * @brief Address
     *
     * The address has street, door number, floor, postal-code and location.
     */
    Address address;
    /**
     * @brief Email
     */
    string email;
    /**
     * @brief Telephone Number
     */
    string phone;
public:
    /**
     * @brief Default Constructor
     */
    Person()= default;
    /**
     * @brief Constructor
     *
     * @param name Name
     * @param gender Gender
     * @param birth Birth Date
     * @param address Address
     * @param email Email
     * @param phone Telephone Number
     */
    Person(string name, string gender, string nif, Date birth, Address address, string email, string phone);

    /*** SET Methods ***/
    void setName(string name);
    void setGender(string gender);
    void setNIF(int nif);
    void setBirth(Date birth);
    void setAddress(Address address);
    void setEmail(string email);
    void setPhone(string phone);

    /*** GET Methods ***/
    string getName() const ;
    string getGender() const ;
    int getNIF() const ;
    Date getBirth() const ;
    Address getAddress() const ;
    string getEmail() const ;
    string getPhone() const ;
};
/**@}*/


//----------------------------------------------------------------------------------------------------------------------

/**
 * @addtogroup person
 * @{
 *
 *  Class necessary to handle client
 */

/**
 *  @brief A class used to represent a client.
 *
 *  Each client object has, aside from the inherited attributes, a number_id, a gold_card, an annual subscription, an activities vector, a loans vector and expenses
 *
 *  @see Activity Loan
 */

class Client : public Person {
    /**
     * @brief num_id, the client's number_id
     */
    int num_id;
    /**
     * @brief gold_card, the client's gold card
     */
    bool gold_card;
    /**
     * @brief annual_subscription, the client's activities
     */
    bool annual_subscription;
    /**
   * @brief log, the client's log (classes, activities, courses and rentals)
   */
    vector<Activity*> log;
    /**
	 * @brief next_id, the next client's id.
	 */
    static int next_id;
    /**
     * @brief loans, vector with client's loans
     */
    vector<Loan *> loans;
    /**
     * @brief expenses, all the client's expenses
     */
    double expenses;
public:
    /**
	 * @brief Default constructor.
	 */
    Client();
    /**
     * @brief Constructor
     *
     * The constructor creates a Client object with the data passed as an argument
     * @param name The client's name
     * @param gender The client's gender
     * @param birth The client's birth date
     * @param address The client's address
     * @param email The client's email
     * @param phone The client's telephone number
     * @param gold_card The client's gold card
     * @param annual_subscription The client's activities
     */
    Client(string name, string gender, string nif, Date birth, Address address, string email, string phone, bool gold_card, bool annual_subscription);
    /**
     * @brief Default destructor
     */
    ~Client()= default;

    /*** GET Methods ***/
    int getId() const;
    bool getGoldCard() const;
    bool getAnnualSubscription() const;
    vector<Activity*> getActivity() const;

    /*** SET Methods ***/
    void setId(int id);
    void setName(string name);
    void setGoldCard(string gold_card);
    void setAnnualSubscription(string an_sub);

    /**
     * @brief Function to add a new activity
     *
     * All the activities are pointer to the activities vector in the School class
     *
     * @param a Pointer to client's new activity
     */
    void addActivities(Activity *a);

    /**
     * @brief Function that prints a client's information
     *
     * @return ostream
     */
    friend ostream & operator<< (ostream &out,Client const &c);

    /**
     * @brief Function to write to the clients file
     * @return String with the line to write to the file
     */
    string WriteToFile () const;
    /**
     * @brief Adds loan to the loan vector of the client
     * @param loan Loan made
     */
    void addLoan(Loan * loan);
};
/*! @} */


//----------------------------------------------------------------------------------------------------------------------

/**
 * @addtogroup person
 * @{
 *
 *  Class necessary to handle teacher
 */

/**
 *  @brief A class used to represent a teacher.
 *
 *  Each teacher object has a name, an initials_id and a classes vector
 *
 *  @see Activities Class
 */
class Teacher: public Person {
    /**
     * @brief initials_id, the teacher's id (using his initials)
     */
    string initials_id;
    /**
     * @brief classes, the classes that the teacher lectures
     */
    vector<Activity*> activity;
public:
    /**
    * @brief Default constructor.
    */
    Teacher();
    /**
     * @brief Constructor
     *
     * The constructor creates a teacher object with the data passed as an argument
     *
     * @param name The teacher's name
     * @param gender The teacher's gender
     * @param birth The teacher's birth date
     * @param address The teacher's address
     * @param email The teacher's email
     * @param phone The teacher's telephone number
     */
    Teacher(string name, string gender, string nif,Date birth, Address address, string email, string phone);
    /**
     * @brief Default destructor
     */
    ~Teacher();

    /*** GET Methods ***/
    string getId() const;
    vector<Activity*> getActivity() const;

    /*** SET Methods ***/
    void setId(string id);

    /**
     * @brief Function to add a new class
     *
     * All the classes are pointer to the classes vector in the School class
     *
     * @param c Pointer to teacher's new class
     */
    void addActivity(Activity *c);

    /**
     * @brief Function that prints a teacher's information
     *
     * @return ostream
     */
    friend ostream& operator<<(ostream &out, Teacher const &c);

    /**
     * @brief Function to write to the clients file
     * @return String with the line to write to the file
     */
    string WriteToFile() const;

};
/*! @} */


//----------------------------------------------------------------------------------------------------------------------

string readString(string msg);
int readNumber(string msg);
Date readDate();
Address readAddress();
void CreatePerson(Person *person);
string readStringNoSpecial(string msg);
string toUpper(string msg);
/**
 * @addtogroup person
 * @{
 *
 *  Functions to handle a person
 */
/**
 * @brief Function to modify attributes of a person
 * @tparam P
 * @param vec Vector of type of person
 * @return Pointer to the person
 */
template <class P>
P * ModifyPerson(vector<P *> &vec){
    bool found=false;

    int search_nif = readNumber("Person's NIF (0 - Back): ");

    if (search_nif == 0)
        return NULL;

    typename vector<P *> ::const_iterator it=vec.begin();

    for(it;it!=vec.end();it++){
        if((*it)->getNIF()==search_nif){
            found=true;
            break;
        }
    }

    if(!found){
        throw NotFound<P>();
    }

    string new_name = readStringNoSpecial("Name: ");
    string new_gender;
    do{
        new_gender=toUpper(readStringNoSpecial("Gender (M or F): "));
        if (new_gender!="M"&&new_gender!="F")
            cout<<"Invalid Gender! Try again.";
    }while (new_gender!="M"&&new_gender!="F");

    int new_nif;
    do{
        new_nif = readNumber("NIF: ");
        if (new_nif<100000000 || new_nif>999999999)
            cout<<"Invalid Phone Number! Try again.";
    }while(new_nif<100000000 || new_nif>999999999);

    cout<<"Date of Birth: ";
    Date new_birth = readDate();
    cout<<"Address: ";
    Address new_address = readAddress();
    string new_email = readString("E-mail: ");
    int new_phone;
    do{
        new_phone=readNumber("Phone Number: ");
        if (new_phone<900000000 || new_phone>999999999)
            cout<<"Invalid Phone Number! Try again.";
    }while(new_phone<900000000 || new_phone>999999999);

    (*it)->setName(new_name);
    (*it)->setGender(new_gender);
    (*it)->setNIF(new_nif);
    (*it)->setBirth(new_birth);
    (*it)->setAddress(new_address);
    (*it)->setEmail(new_email);
    (*it)->setPhone(to_string(new_phone));

    return *it;
}

/**
 * @brief function to remove a person
 * @tparam P
 * @param vec Vector of type of person
 * @return Pointer to the person
 */
template <class P>
P * RemovePerson(vector<P *> &vec){
    bool found=false;

    int search_nif = readNumber("Person's NIF (0 - Back): ");

    if (search_nif == 0)
        return NULL;

    typename vector<P *> ::const_iterator it=vec.begin();

    for(it;it!=vec.end();it++){
        if((*it)->getNIF()==search_nif){
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
 * @brief Function to create a client
 * @param vec Vector of clients
 */
void CreateClient(vector<Client *> &vec);
/**
 * @brief Function to modify a client
 * @param vec Vector of clients
 */
void ModifyClient(vector<Client *> &vec);
/**
 * @brief Function to remove a client
 * @param vec Vector of clients
 */
void RemoveClient(vector <Client *> &vec);
/**
 * @brief Function to add a client to an activity
 * @param vec_cl Vector of clients
 * @param vec_ac Vector of activities
 * @param vec_cla Vectors of classes
 * @param vec_tr Vectors of trips
 */
void ClientActivity(vector <Client *> &vec_cl, vector <Activity *> &vec_ac, vector <Classes *> &vec_cla, vector <Trip *> &vec_tr);
/**
 * @brief Function to add a loan to a client
 * @param clients Vector of clients
 * @param materials Vector of materials
 * @param classes Vector of classes
 * @param loans Vector of loans
 * @param courses Vector of courses
 */
void MaterialRent(vector <Client *> &clients, vector<Material *> materials, vector<Classes *> classes, vector<Loan *> &loans, vector<Course *> courses);
/**
 * @brief Vunction to create a teacher
 * @param vec Vector of teachers
 */
void CreateTeacher(vector<Teacher *> &vec);
/**
 * @brief Function to modify a teacher
 * @param vec Vector of teachers
 */
void ModifyTeacher(vector<Teacher *> &vec);
/**
 * @brief Function to remove a teacher
 * @param vec Vector of teachers
 */
void RemoveTeacher(vector <Teacher *> &vec);
/*! @} */

#endif //PROJECT_PERSON_H
