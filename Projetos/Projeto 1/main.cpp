#include <iostream>
#include "Menus.h"

using namespace std;
class Material;
class Activity;
class Client;
class Teacher;
class Trip;
class Classes;

int main() {
    ifstream client_file,teacher_file,material_file, classes_file, courses_file, trips_file, loans_file;

    client_file.open("..\\clients.txt");
    teacher_file.open("..\\teachers.txt");
    classes_file.open("..\\Activities\\classes.txt");
    courses_file.open("..\\Activities\\courses.txt");
    trips_file.open("..\\Activities\\trips.txt");
    loans_file.open("..\\Activities\\loans.txt");
    material_file.open("..\\materials.txt");

    School s(client_file,teacher_file,classes_file, courses_file, trips_file, material_file, loans_file);

    vector<Material *> schoolMaterials = s.getMaterials();
    vector<Activity *> schoolActivities = s.getActivities();
    vector<Client *> schoolClients = s.getClients();
    vector<Teacher *> schoolTeachers= s.getTeachers();
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
                                CreateClient(schoolClients);
                                system("pause");
                                break;
                            case 2: //MODIFY CLIENT
                                ModifyClient(schoolClients);
                                system("pause");
                                break;
                            case 3: //REMOVE CLIENT
                                RemoveClient(schoolClients);
                                system("pause");
                                break;
                            case 4:
                                ClientActivity(schoolClients,schoolActivities,schoolClasses,schoolTrips);
                                system("pause");
                                break;
                            case 5:
                                MaterialRent(schoolClients, schoolMaterials, schoolClasses, schoolLoans, schoolCourses); //FALTA FAZER
                                s.setLoans(schoolLoans);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        s.setClients(schoolClients);
                        s.setClasses(schoolClasses);
                    }
                    else if(temp == 2){ //TEACHERS MENU
                        temp2 = TeachersMenu();
                        switch(temp2) {
                            case 1: //CREATE MATERIAL
                                CreateTeacher(schoolTeachers);
                                system("pause");
                                break;
                            case 2: //MODIFY MATERIAL
                                ModifyTeacher(schoolTeachers);
                                system("pause");
                                break;
                            case 3: //REMOVE MATERIAL
                                RemoveTeacher(schoolTeachers);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        s.setTeachers(schoolTeachers);
                        s.AssignTeachers(schoolClasses,schoolTeachers);
                    }
                    else if(temp == 3){ //ACTIVITIES MENU
                        temp2 = ActivityMenu();
                        switch(temp2) {
                            case 1: //CREATE ACTIVITY
                                CreateActivity(schoolClasses, schoolCourses, schoolTrips, schoolMaterials, schoolLoans); //FALTA TRIP
                                system("pause");
                                break;
                            case 2: //MODIFY ACTIVITY
                                ModifyActivity(schoolClasses,schoolCourses,schoolTrips,schoolMaterials, schoolLoans);
                                system("pause");
                                break;
                            case 3: //REMOVE ACTIVITY
                                RemoveActivity(schoolClasses,schoolCourses,schoolTrips);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        s.setClasses(schoolClasses);
                        s.setCourses(schoolCourses);
                        s.setTrips(schoolTrips);
                        s.AssignTeachers(schoolClasses,schoolTeachers);
                    }
                    else if(temp == 4) { //MATERIALS MENU
                        temp2 = MaterialsMenu();
                        switch(temp2) {
                            case 1: //CREATE MATERIAL
                                CreateMaterial(schoolMaterials);
                                system("pause");
                                break;
                            case 2: //MODIFY MATERIAL
                                ModifyMaterial(schoolMaterials);
                                system("pause");
                                break;
                            case 3: //REMOVE MATERIAL
                                RemoveMaterial(schoolMaterials);
                                system("pause");
                                break;
                            default:
                                break;
                        }
                        s.setMaterials(schoolMaterials);
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
                }
                else if(temp==3){
                }
                else
                    continue;
            }
        } while (temp != 0);
    } while (op != 0);

    s.setClients(schoolClients);
    s.setTeachers(schoolTeachers);
    s.setMaterials(schoolMaterials);
    s.setCourses(schoolCourses);

    s.sortClassesByID();
    return 0;
}