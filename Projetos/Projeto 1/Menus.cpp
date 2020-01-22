#include "Menus.h"

#include <utility>

int mainMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "School" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Management\n";
    cout << "2 - Data View\n";
    cout << "3 - Other\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(3);
}

int ManagementMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Management" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Clients Management\n";
    cout << "2 - Teachers Management\n";
    cout << "3 - Activity Management\n";
    cout << "4 - Materials Management\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(4);
}

int ClientsMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Clients" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Add Client\n";
    cout << "2 - Modify Client\n";
    cout << "3 - Delete Client\n";
    cout << "4 - Sign Up For An Activity\n";
    cout << "5 - Rent Materials\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(5);
}

int TeachersMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Teachers" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Add Teacher\n";
    cout << "2 - Modify Teacher\n";
    cout << "3 - Delete Teacher\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(3);
}

int ActivityMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Activities" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Add Activity\n";
    cout << "2 - Modify Activity\n";
    cout << "3 - Delete Activity\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(3);
}

int MaterialsMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Materials" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Add Material\n";
    cout << "2 - Modify Material\n";
    cout << "3 - Delete Material\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(3);
}

int InfoMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Information" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - View Client Information\n";
    cout << "2 - View All Clients\n";
    cout << "3 - View Teacher Information\n";
    cout << "4 - View All Teachers\n";
    cout << "5 - View All Activities\n";
    cout << "6 - View Trips\n";
    cout << "7 - View Loans\n";
    cout << "8 - View Time Table\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(8);
}

int timeTableMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Time Table" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - View Client Time Table\n";
    cout << "2 - View Teacher Time Table\n";
    cout << "3 - View All Classes Time Table\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(3);
}

int otherMenu() {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Other Functions" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Send E-mail\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    return ieMenu(1);
}

vector<Classes *> chooseClasses(vector<Classes *> classes) {
    vector<Classes *> available;
    vector<Classes *> choose;
    SHOWCLASSES:
    cout << setw(23) << right << "Which classes belong to the course:" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Classes" << endl;
    cout << "__________________________________________________\n" << endl;

    available.clear();

    for (int i = 0; i < classes.size(); i++)
        if (!classes[i]->getAnnual() && find(choose.begin(), choose.end(), classes[i]) == choose.end())
            available.push_back(classes[i]);

    int i;

    for (i = 1; i < available.size() + 1; i++) {
        cout << i << " - " << available[i-1]->getName() << endl;
    }

    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    cout << "Your List = [";
    for (int x = 0; x < choose.size(); x++)
        cout << choose[x]->getName() << ", ";
    cout << " ]" << endl;
    cout << "__________________________________________________\n" << endl;

    int id = ieMenu(i);
    if (id == 0)
        return choose;
    if (find(choose.begin(), choose.end(), available[id-1]) == choose.end())
        choose.push_back(available[id-1]);
    goto SHOWCLASSES;
}

vector<Material *> chooseMaterials(vector<Classes *> classes, vector<Material *> materials, Time startTime, string day, vector<Loan *> loans, int week, vector<Course *> courses) {
    vector<Material *> available, updated_materials = move(materials);
    vector<Material *> choose;

    updateMaterialsUsed(move(classes), updated_materials, startTime, move(day), move(loans), week, move(courses));
    SHOWMATERIALS:
    cout << setw(23) << right << "Which materials to choose:" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Materials" << endl;
    cout << "__________________________________________________\n" << endl;

    available.clear();

    for (int i = 0; i < updated_materials.size(); i++)
        if (updated_materials[i]->getTotal() - updated_materials[i]->getUsed() > 0)
            available.push_back(updated_materials[i]);

    int i;

    for (i = 1; i < available.size() + 1; i++) {
        cout << i << " - " << available[i-1]->getType() << "(" << available[i-1]->getTotal() - available[i-1]->getUsed() << ")" << endl;
    }

    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    cout << "Your List = [";
    for (int x = 0; x < choose.size(); x++)
        cout << choose[x]->getType() << ", ";
    cout << " ]" << endl;
    cout << "__________________________________________________\n" << endl;

    int id = ieMenu(i-1);
    if (id == 0 || id > i)
        return choose;

    choose.push_back(available[id-1]);
    available[id-1]->setUsed(available[id-1]->getUsed() + 1);

    goto SHOWMATERIALS;
}