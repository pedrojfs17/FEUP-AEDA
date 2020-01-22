//
// Created by pedro on 14/10/2019.
//

#include <iomanip>
#include "Activity.h"


int Classes::next_id = 1;
int Trip::next_id = 1;

Activity::Activity():price(15) {max_attendees = 10;}

Activity::Activity(string name, double price): price(price){
    this->name = name;
    max_attendees = 10;
}

Activity::Activity(string name, string price): price(stod(price)) {
    this->name=name;
    max_attendees = 10;
}

string Activity::getActivity() const {
    return "Name: " + name+ "\nMax attendees: "+to_string(max_attendees)+"\nCurrent attendees: "+to_string(attendees.size());
}

string Activity::getName() const {
    return name;
}

vector <Client *> Activity::getAttendees() const {
    return attendees;
}

int Activity::getMaxAttendees() const {
    return max_attendees;
}

vector<Material *> Activity::getMaterials() const {
    return this->materials;
}

double Activity::getPrice() const {
    return price;
}

void Activity::setName(string name) {
    this->name=name;
}

void Activity::addAttendee(Client *c){
    attendees.push_back(c);
}

//----------------------------------------------------------------------------------------------------------------------

Classes::Classes(string name) {
    this->name = name;
    this->annual = false;
    this->id = next_id;
    next_id++;
}

Classes::Classes(string name, string annual, string time, string day, string doubleClass, string price, string id, vector<Material *> materialsNeeded):Activity(name, price) {
    this->id = stoi(id);
    next_id++;
    this->startTime = Time(time);
    this->day = day;
    if (doubleClass == "Y")
        this->doubleClass = true;
    else
        this->doubleClass = false;
    if(annual == "Y")
        this->annual=true;
    else
        this->annual=false;
    this->materials = materialsNeeded;
}

Classes::Classes(string name, Time time, string day, bool doubleClass, double price, vector<Material *> materialsNeeded):Activity(name, price) {
    this->startTime = time;
    this->day = day;
    this->doubleClass = doubleClass;
    this->annual = false;
    this->materials=materialsNeeded;
    this->id = next_id;
    next_id++;
}

int Classes::getID() const {
    return this->id;
}

string Classes::getActivity() const {
    return Activity::getActivity() + "\nAnnual: " + to_string(annual) + "\n";
}

bool Classes::getAnnual() const {
    return annual;
}

string Classes::getDay() const{
    return day;
}

Time Classes::getStartTime() const{
    return startTime;
}

bool Classes::getDoubleClass() const {
    return doubleClass;
}

Teacher *Classes::getTeacher() const {
    return this->teacher;
}

void Classes::setMaterial(vector<Material *> material) {
    this->materials=material;
}

void Classes::setTeacher(Teacher *teacher) {
    this->teacher = teacher;
}

void Classes::setTime(Time time) {
    this->startTime=time;
}

void Classes::setDay(string day) {
    this->day=day;
}

void Classes::setDoubleClass(bool db) {
    this->doubleClass=db;
}

void Classes::setAnnual(bool annual) {
    this->annual = annual;
}

string Classes::WriteToFile() {
    string out = "";
    out += this->name + ";";
    if (this->annual)
        out += "Y;";
    else
        out += "N;";
    out += this->startTime.getTime() + ";";
    out += this->day + ";";
    if (this->doubleClass)
        out += "Y;";
    else
        out += "N;";
    string price = to_string(this->price);
    out += price.substr(0, price.find_first_of(".") + 3) + ";";
    //out+=materials.size();
    vector<Material *> v =materials;
    if(v.empty()){
        out+="0";
    }
    else{
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for (int i = 0; i < v.size(); i++) {
            if (i == v.size() - 1)
                out += to_string(v[i]->getID());
            else
                out += to_string(v[i]->getID()) + ",";
        }
    }

    out += ";"+to_string(this->id);
    //out +=to_string(materials.size());

    return out;
}

ostream& operator<<(ostream &out, Classes const &c) {
    out<<"\nName: "<<c.getName();
    out<<"\nDay: "<<c.getDay();
    out<<"\nTime: "<<c.getStartTime().getTime();
    out<<"\nTeacher: "<<c.getTeacher()->getName();
    out<<"\nPrice: "<<to_string(c.getPrice()).substr(0, to_string(c.getPrice()).find_first_of(".") + 3);
    out<<"\nMax Attendees: "<<to_string(c.getMaxAttendees());
    out<<"\nCurrent Attendees: "<<to_string(c.getAttendees().size());
    out<<"\nPart of Course: "<<boolalpha<<c.getAnnual()<<endl;
    return out;
}

bool CompareTwoClassesByTime(Classes * class1, Classes * class2) {
    vector<string> days = {"Mon", "Tue", "Wed", "Thu", "Fri"};
    if (find(days.begin(), days.end(), class1->getDay()) < find(days.begin(), days.end(), class2->getDay()))
        return true;
    else if (find(days.begin(), days.end(), class1->getDay()) > find(days.begin(), days.end(), class2->getDay()))
        return false;
    else
        return (class1->getStartTime() < class2->getStartTime());
}

//----------------------------------------------------------------------------------------------------------------------

Course::Course(vector<Classes *> classes, string numWeeks) {
    this->classes = classes;
    this->numWeeks = stoi(numWeeks);
}

Course::Course(string name, double price, vector<Classes *> classes, int numWeeks): Activity(name, price){
    this->classes = classes;
    this->numWeeks = numWeeks;
}

Course::Course(string name, string price, vector<Classes *> classes, string numWeeks): Activity(name, stod(price)){
    this->classes = classes;
    this->numWeeks = stoi(numWeeks);
}

string Course::getActivity() const {
    string info;
    info = "Curso com as aulas:\n";
    for (int i = 0; i < classes.size(); i++)
        info += classes[i]->getActivity();
    return info;
}

vector<Classes *> Course::getClasses() const {
    return this->classes;
}

int Course::getNumWeeks() const {
    return numWeeks;
}

void Course::setClasses(vector<Classes *> classes) {
    this->classes=classes;
}

void Course::setNumWeeks(int nw) {
    this->numWeeks=nw;
}

string Course::WriteToFile() {
    string out = "";
    out += this->name + ";";
    string price = to_string(this->price);
    out += price.substr(0, price.find_first_of(".") + 3) + ";";
    for (int i = 0; i < classes.size(); i++) {
        out += to_string(classes[i]->getID());
        if (i < classes.size() - 1)
            out += ",";
    }
    out += ";" + to_string(this->numWeeks);
    return out;
}

ostream& operator<<(ostream &out, Course const &c) {
    out<<"\nName: "<<c.getName();
    string info;
    info = "\nClasses:\n";
    vector<Classes *> cl=c.getClasses();
    for (int i = 0; i < cl.size(); i++){
        if(i==cl.size()-1){
            out << cl[i]->getName();
        }
        else
            out << cl[i]->getName()<<", ";
    }
    out<<"\nPrice: "<<to_string(c.getPrice()).substr(0, to_string(c.getPrice()).find_first_of(".") + 3);
    out<<"\nMax Attendees: "<<to_string(c.getMaxAttendees());
    out<<"\nCurrent Attendees: "<<to_string(c.getAttendees().size());
    out<<"\nDuration: "<<c.getNumWeeks()<<" weeks";
    return out;
}



//----------------------------------------------------------------------------------------------------------------------

Trip::Trip(string name, string location, Date beginDate, Date endDate, double price, int maxAttendees):Activity(name, price) {
    this->location = location;
    this->price = price;
    this->name = name;
    this->beginDate = beginDate;
    this->endDate = endDate;
    this->id = next_id;
    next_id++;
    this->max_attendees = maxAttendees;
}

int Trip::getID() const {
    return this->id;
}

string Trip::getActivity() const {
    string out = "";
    out += "Trip #" + to_string(id) + "\n";
    out += "Name: " + name + "\n";
    out += "Max attendees: " + to_string(max_attendees) + "\n";
    out += "Current attendees: " + to_string(attendees.size()) + "\n";
    out += "Price: " + to_string(price).substr(0, to_string(price).find_first_of(".") + 3) + "\n";
    out += "Location: " + location + "\n";
    out += "Dates: from " + beginDate.getDate() + " to " + endDate.getDate() + "\n";
    return out;
}

void Trip::setLocation(string location) {
    this->location=location;
}

void Trip::setBeginDate(Date begin) {
    this->beginDate=begin;
}

void Trip::setEndDate(Date end){
    this->endDate=end;
}

void Trip::setMaxAttendees(int max) {
    this->max_attendees=max;
}

Date Trip::getBeginDate() const {
    return beginDate;
}

Date Trip::getEndDate() const {
    return endDate;
}

string Trip::getLocation() const {
    return location;
}

string Trip::WriteToFile() {
    string out = "";
    out += this->name + ";";
    string price = to_string(this->price);
    out += price.substr(0, price.find_first_of(".") + 3) + ";";
    out += this->location + ";";
    out += this->beginDate.getDate() + ";" + this->endDate.getDate() + ";";
    out += to_string(this->max_attendees);
    return out;
}

ostream& operator<<(ostream &out, Trip const &t) {
    out<<"\nName: "<<t.getName();
    out<<"\nStarting Date: "<<t.getBeginDate().getDate();
    out<<"\nEnding Date: "<<t.getEndDate().getDate();
    out<<"\nPrice: "<<to_string(t.getPrice()).substr(0, to_string(t.getPrice()).find_first_of(".") + 3);
    out<<"\nMax Attendees: "<<to_string(t.getMaxAttendees());
    out<<"\nCurrent Attendees: "<<to_string(t.getAttendees().size())<<endl;
    return out;
}

//----------------------------------------------------------------------------------------------------------------------

Loan::Loan(string name, string day, Time time, vector<Material *> rent_mat, int clientsNIF, double price, int week): Activity(name, price){
    this->name = name;
    this->day = day;
    this->time = time;
    this->rented_material = rent_mat;
    this->clientsNIF = clientsNIF;
    this->week = week;
}

string Loan::getDay() const {
    return this->day;
}

Time Loan::getTime() const {
    return this->time;
}

int Loan::getWeek() const {
    return this->week;
}

string Loan::getActivity() const {
    return Activity::getActivity();
}

int Loan::getClientsNIF() const {
    return this->clientsNIF;
}

string Loan::showLoan() const {
    string out = "";
    out += "Week " + to_string(week) + " on ";
    out += day;
    out += " at " + time.getTime();
    out += "\t Client NIF: " + to_string(clientsNIF);
    out += "\t Materials: ";
    for (int i = 0; i < rented_material.size(); i++) {
        out += rented_material[i]->getType();
        if (i < rented_material.size() - 1)
            out += ", ";
    }
    return out;
}

string Loan::WriteToFile() {
    string out = "";
    out += this->day+";";
    out += this->time.getTime()+";";
    vector<Material *> v =rented_material;
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        if (i == v.size() - 1)
            out += to_string(v[i]->getID())+";";
        else
            out += to_string(v[i]->getID()) + ",";
    }
    out += to_string(this->clientsNIF)+";";
    string price = to_string(this->price);
    out += price.substr(0, price.find_first_of(".") + 3) + ";";
    out += to_string(week);
    return out;

}

vector<Classes *> getWeekClasses(int week, vector<Classes *> classes, vector<Course *> courses) {
    if (week == 0)
        return classes;

    vector<Classes *> weekClasses, tempClasses;

    bool found;

    typename vector<Classes *> ::const_iterator it;
    typename vector<Course *> ::const_iterator it2;

    for (it = classes.begin(); it != classes.end(); it++) {
        found = false;
        for (it2 = courses.begin(); it2 != courses.end(); it2++) {
            tempClasses = (*it2)->getClasses();
            for (int i = 0; i < tempClasses.size(); i++) {
                if (tempClasses[i]->getID() == (*it)->getID() && (*it2)->getNumWeeks() < week) {
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
        if (!found)
            weekClasses.push_back(*it);
    }

    return weekClasses;
}

void updateMaterialsUsed(vector<Classes *> classes, vector<Material *> &materials, Time startTime, string day, vector<Loan *> loans, int week, vector<Course *> courses) {
    classes = getWeekClasses(week, classes, move(courses));

    typename vector<Classes *>::const_iterator it = classes.begin();
    vector<Material *> materialClass;

    for (; it != classes.end(); it++) {
        if (day == (*it)->getDay()) {
            if ((!(*it)->getDoubleClass() && ((startTime < (*it)->getStartTime() && (*it)->getStartTime() < startTime + Time(0,45)) || ((*it)->getStartTime() < startTime && startTime < (*it)->getStartTime() + Time(0,45)))) || ((*it)->getDoubleClass() && ((startTime < (*it)->getStartTime() && (*it)->getStartTime() < startTime + Time(0,45))||((*it)->getStartTime() < startTime && startTime < (*it)->getStartTime() + Time(1,30))))) {
                materialClass = (*it)->getMaterials();
                for (int i = 0; i < materialClass.size(); i++) {
                    for (int j = 0; j < materials.size(); j++) {
                        if (materialClass[i]->getType() == materials[j]->getType()) {
                            materials[j]->setUsed(materials[j]->getUsed() + 10);
                        }
                    }
                }
            }
        }
    }

    typename vector<Loan *>::const_iterator it_2 = loans.begin();
    vector<Material *> loanClass;
    for (; it_2 != loans.end(); it_2++) {
        if (day == (*it_2)->getDay() && week == (*it_2)->getWeek()) {
            if ((startTime < (*it_2)->getTime() && (*it_2)->getTime() < startTime + Time(0,45)) || ((*it_2)->getTime() < startTime && startTime < (*it_2)->getTime() + Time(0,45))) {
                loanClass = (*it_2)->getMaterials();
                for (int i = 0; i < loanClass.size(); i++) {
                    for (int j = 0; j < materials.size(); j++) {
                        if (materialClass[i]->getType() == materials[j]->getType()) {
                            materials[j]->setUsed(materials[j]->getUsed() + 1);
                        }
                    }
                }
            }
        }
    }
}
// IF ((*it)->getDoubleClass())
// startTime < (*it)->getStartTime() && (*it)->getStartTime() < startTime + 0:45
// startTime > (*it)->getStartTime() && startTime < (*it)->getStartTime() + 0:45
// ELSE
// startTime < (*it)->getStartTime() && (*it)->getStartTime() < startTime + 0:45
// startTime > (*it)->getStartTime() && startTime < (*it)->getStartTime() + 1:30
