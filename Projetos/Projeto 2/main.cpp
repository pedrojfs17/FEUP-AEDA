#include <iostream>
#include <fstream>
#include "School.h"
#include "Menus.h"
#include "bst.h"

using namespace std;
class Material;
class Activity;
class Client;
class Teacher;
class Technician;
class Trip;
class Classes;

int sortingSchoolsMethod;

/**
 * @brief Function to write to schools file
 * @param schoolsTree BinaryTree of schools
 * @param s School chosen in the main menu
 */
void writeSchoolsFile(BST<School> schoolsTree, School s) {
    BSTItrIn<School> it(schoolsTree);

    ofstream schools_file;

    schools_file.open("..\\schools.txt");

    while (!it.isAtEnd()) {
        if (it.retrieve().getPlace() != s.getPlace())
            schools_file << it.retrieve().getPlace() << ";" << it.retrieve().getDirector() << ";" << to_string(it.retrieve().getNumClients());
        else
            schools_file << s.getPlace() << ";" << s.getDirector() << ";" << to_string(s.getClients().size());
        it.advance();
        if (!it.isAtEnd())
            schools_file << endl;
    }

    schools_file.close();
}

int showSchools(BST<School> schoolsTree, int sortingSchoolsMethod) {
    unsigned int i = 0;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Schools" << endl;
    cout << "__________________________________________________\n" << endl;
    BSTItrIn<School> it(schoolsTree);
    switch (sortingSchoolsMethod) {
        case 1:
            cout << "Sorted by: Location\n";
            break;
        case 2:
            cout << "Sorted by: Director\n";
            break;
        case 3:
            cout << "Sorted by: Number of Clients (Ascending)\n";
            break;
        case 4:
            cout << "Sorted by: Number of Clients (Descending)\n";
            break;
        default:
            break;
    }
    while(!it.isAtEnd()) {
        switch (sortingSchoolsMethod) {
            case 1:
                cout << i + 1 << " - " << it.retrieve().getPlace() << " ( Director: " << it.retrieve().getDirector() << " | Number of clients: " << it.retrieve().getNumClients() << ")" << endl;
                break;
            case 2:
                cout << i + 1 << " - " << it.retrieve().getDirector() << " ( Location: " << it.retrieve().getPlace() << " | Number of clients: " << it.retrieve().getNumClients() << ")" << endl;
                break;
            case 3:
            case 4:
                cout << i + 1 << " - " << it.retrieve().getNumClients() << " ( Location: " << it.retrieve().getPlace() << " | Director: " << it.retrieve().getDirector() << ")" << endl;
                break;
            default:
                break;
        }
        i++;
        it.advance();
    }
    cout<<endl<<i+1<<" - Create School\n";
    cout<<i+2<<" - Remove School\n";
    cout << "0 - Change Sort\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(i+2);
}

int main() {
    int schoolNum, numberOfSchools;

    ifstream schools_file;
    string name, director, numClients, file = "..\\Schools\\";

    schools_file.open("..\\schools.txt");

    BST<School> schoolsTree(School("", "", 0));

    do {
        schoolsTree.makeEmpty();
        sortingSchoolsMethod = sortingSchoolsMenu();
        numberOfSchools = 0;

        if (sortingSchoolsMethod == 0)
            return 0;

        schools_file.clear();
        schools_file.seekg(0, ios::beg);

        while (!schools_file.eof()) {
            getline(schools_file, name, ';');
            getline(schools_file, director, ';');
            getline(schools_file, numClients);
            schoolsTree.insert(School(name, director, stoi(numClients)));
            numberOfSchools++;
        }

        schoolNum = showSchools(schoolsTree, sortingSchoolsMethod);

        if (schoolNum == numberOfSchools + 1) {
            createSchool(&schoolsTree);
            writeSchoolsFile(&schoolsTree);
        }
        else if (schoolNum == numberOfSchools + 2) {
            deleteSchool(&schoolsTree);
            writeSchoolsFile(&schoolsTree);
        }

    } while (schoolNum == 0 || schoolNum == numberOfSchools + 1 || schoolNum == numberOfSchools + 2);

    BSTItrIn<School> it(schoolsTree);

    for (int i = 0; i < schoolNum - 1; i++)
        it.advance();

    School s = loadSchool(it.retrieve().getPlace());

    vector<Material *> schoolMaterials = s.getMaterials();
    vector<Activity *> schoolActivities = s.getActivities();
    vector<Client *> schoolClients = s.getClients();
    vector<Teacher *> schoolTeachers= s.getTeachers();
    TeacherHashTable allTeachers = s.getHashTable();
    priority_queue<Technician *> schoolTechnicians = s.getTechnicians();
    vector<Classes *> schoolClasses =s.getClasses();
    vector<Course *> schoolCourses = s.getCourses();
    vector<Trip *> schoolTrips = s.getTrips();
    vector<Loan *> schoolLoans = s.getLoans();

    int op;

    do {
        op = mainMenu();
        int temp;
        if (op == 0)
            break;
        do {
            if(op == 1){ //MANAGEMENT MENU
                temp = ManagementMenu();
                int temp2;
                if (temp == 0)
                    break;
                do {
                    if(temp == 1){ //CLIENTS MENU
                        temp2 = ClientsMenu();
                        switch(temp2) {
                            case 1: //CREATE CLIENT
                                CreateClient(&s);
                                system("pause");
                                break;
                            case 2: //MODIFY CLIENT
                                ModifyClient(&s);
                                system("pause");
                                break;
                            case 3: //REMOVE CLIENT
                                RemoveClient(&s);
                                system("pause");
                                break;
                            case 4:
                                ClientActivity(s.getClients(),s.getActivities(),s.getClasses(),s.getTrips());
                                system("pause");
                                break;
                            case 5:
                                MaterialRent(s.getClients(), s.getMaterials(), s.getClasses(), schoolLoans, s.getCourses()); //FALTA FAZER
                                s.setLoans(schoolLoans);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        //s.setClients(schoolClients);
                        //s.setClasses(schoolClasses);
                    }
                    else if(temp == 2){ //TEACHERS MENU
                        temp2 = TeachersMenu();
                        switch(temp2) {
                            case 1: //CREATE MATERIAL
                                CreateTeacher(&s);
                                system("pause");
                                break;
                            case 2: //MODIFY MATERIAL
                                ModifyTeacher(&s);
                                system("pause");
                                break;
                            case 3: //REMOVE MATERIAL
                                RemoveTeacher(&s);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        s.AssignTeachers(s.getClasses(),s.getHiredTeachers());
                    }
                    else if(temp == 3){ //ACTIVITIES MENU
                        temp2 = ActivityMenu();
                        switch(temp2) {
                            case 1: //CREATE ACTIVITY
                                CreateActivity(&s); //FALTA TRIP
                                system("pause");
                                break;
                            case 2: //MODIFY ACTIVITY
                                ModifyActivity(&s);
                                system("pause");
                                break;
                            case 3: //REMOVE ACTIVITY
                                RemoveActivity(&s);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        //s.setClasses(schoolClasses);
                        //s.setCourses(schoolCourses);
                        //s.setTrips(schoolTrips);
                        cout<<"A\n";
                        s.AssignTeachers(s.getClasses(),s.getHiredTeachers());
                        cout<<"B\n";
                    }
                    else if(temp == 4) { //MATERIALS MENU
                        temp2 = MaterialsMenu();
                        switch(temp2) {
                            case 1: //CREATE MATERIAL
                                CreateMaterial(&s);
                                system("pause");
                                break;
                            case 2: //MODIFY MATERIAL
                                ModifyMaterial(&s);
                                system("pause");
                                break;
                            case 3: //REMOVE MATERIAL
                                RemoveMaterial(&s);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        //s.setMaterials(schoolMaterials);
                    }
                    else if(temp== 5){ //TECHNICIANS MENU
                        temp2=TechniciansMenu();
                        switch(temp2){
                            case 1: //CREATE TECHNICIAN
                                CreateTechnician(&s);
                                system("pause");
                                break;
                            case 2: //MODIFY TECHNICIAN
                                ModifyTechnician(&s);
                                system("pause");
                                break;
                            case 3: //REMOVE TECHNICIAN
                                RemoveTechnician(&s);
                                system("pause");
                            default:
                                break;
                        }
                    }
                    else
                        continue;
                } while(temp2 != 0);
            }
            else if(op == 2){ //DATA VIEW
                temp = InfoMenu();
                if(temp==1){
                    while (1) {
                        try {
                            s.PrintClient();
                            system("pause");
                            break;
                        }
                        catch (...) {
                            cout << "Client not found! Try another NIF.\n";
                        }
                    }
                }
                else if(temp==2){
                    s.PrintAllClients();
                    system("pause");
                }
                else if(temp==3){
                    while (1) {
                        try {
                            s.PrintTeacher();
                            system("pause");
                            break;
                        }
                        catch (...) {
                            cout << "Teacher not found! Try other initials.\n";
                        }
                    }
                }
                else if(temp==4){
                    s.PrintAllTeachers();
                    system("pause");
                }
                else if(temp==5){
                    s.PrintAllActivities();
                    system("pause");
                }
                else if(temp==6){
                    s.PrintTrips();
                    system("pause");
                }
                else if (temp == 7) {
                    s.PrintAllLoans();
                    system("pause");
                }
                else if(temp==8){
                    int temp2 = timeTableMenu();
                    s.sortClassesByHour();
                    switch(temp2) {
                        case 1: //VIEW CLIENT TIME TABLE
                            while (1) {
                                try {
                                    s.PrintClientTimeTable();
                                    system("pause");
                                    break;
                                }
                                catch(...) {
                                    cout << "Client not found! Try another NIF.\n";
                                }
                            }
                            break;
                        case 2: //VIEW TEACHER TIME TABLE
                            while (1) {
                                try {
                                    s.PrintTeacherTimeTable();
                                    system("pause");
                                    break;
                                }
                                catch (...) {
                                    cout << "Teacher not found! Try other initials.\n";
                                }
                            }
                            break;
                        case 3: //VIEW ALL CLASSES
                            s.PrintAllClassesTimeTable();
                            system("pause");
                            break;
                        default:
                            break;
                    }
                }
                else if(temp==9){
                    s.PrintTechnician();
                    system("pause");
                }
                else if(temp==10){
                    s.PrintAllTechnicians();
                    system("pause");
                }
                else if(temp==11){
                    s.PrintPastTeachers();
                    system("pause");
                }
                else
                    continue;
            }
            else if(op==3){ //OTHER
                temp = otherMenu();

                if(temp==1){
                    s.sendEmail();
                    system("pause");
                }
                else if(temp==2){
                    s.repairMaterial();
                    system("pause");
                }
                else if(temp==3){
                }
                else
                    continue;
            }
        } while (temp != 0);
    } while (op != 0);

    //s.setClients(schoolClients);
    //s.setMaterials(schoolMaterials);
    //s.setCourses(schoolCourses);
    s.sortClassesByID();
    s.exitSchool();

    schools_file.close();
    writeSchoolsFile(schoolsTree, s);

    return 0;
}