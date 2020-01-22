//
// Created by pedro on 14/10/2019.
//

#include "Material.h"

int Material::nextID = 1;

Material::Material() : price(15), ID(nextID) {} //ex: 15 euro por 45 minutos

Material::Material(string type, double price, int amount, int used) : price(price), ID(nextID){
    this->type = type;
    this->totalAmount = amount;
    this->usedAmount = used;
    nextID++;
}

string Material::getType() const {
    return type;
}

double Material::getPrice() const {
    return price;
}

int Material::getTotal() const {
    return totalAmount;
}

int Material::getUsed() const {
    return usedAmount;
}

int Material::getID() const {
    return this->ID;
}

void Material::setType(string type) {
    this->type = type;
}

void Material::setTotal(int total) {
    this->totalAmount = total;
}

void Material::setUsed(int used) {
    this->usedAmount = used;
}

string Material::WriteToFile() const {
    string out = "", price = to_string(this->price);
    out += this->type + ";";
    out += price.substr(0, price.find_first_of(".") + 3) + ";";
    out += to_string(this->totalAmount) + ";";
    out += to_string(this->usedAmount);
    return out;
}

//----------------------------------------------------------------------------------------------------------------------

vector<Material *>::const_iterator searchMaterial(vector<Material *> &vec) {
    string search_type;
    bool found = false;

    search_type = readString("Type of material (\"back\" - Back): ");

    if (toUpper(search_type) == "BACK")
        return vec.end();

    vector<Material *> ::const_iterator it=vec.begin();

    for(; it != vec.end(); it++){
        if((*it)->getType() == search_type){
            found = true;
            break;
        }
    }

    if(!found){
        throw NotFound<Material>();
    }

    return it;
}

void CreateMaterial(vector<Material *> &vec) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Create New Material" << endl;
    cout << "__________________________________________________\n" << endl;
    string type = readString("Type of Material: ");
    double price = readDouble("Price per 45 minutes: ");
    int amount = readNumber("Number of materials of this type: ");

    Material * m = new Material(type, price, amount, 0);
    vec.push_back(m);
}

void ModifyMaterial(vector<Material *> &vec) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Modify Material" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "Can not change the price of the materials!" << endl;
    cout << "__________________________________________________\n" << endl;

    vector<Material *>::const_iterator p;
    bool read = false;

    do {
        try {
            p = searchMaterial(vec);
            read = true;
        }
        catch (...) {
            cout << "Invalid Name. Try Again." << endl;
        }
    } while(!read);

    if (p == vec.end()) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }

    string type = readString("Type of Material: ");
    int totalAmount = readNumber("Number of materials of this type: ");
    int usedAmount = readNumber("Number of materials of this type being used: ");

    (*p)->setType(type);
    (*p)->setTotal(totalAmount);
    (*p)->setUsed(usedAmount);
}

void RemoveMaterial(vector<Material *> &vec) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Material" << endl;
    cout << "__________________________________________________\n" << endl;

    vector<Material *>::const_iterator p;
    bool read = false;

    do {
        try {
            p = searchMaterial(vec);
            read = true;
        }
        catch (...) {
            cout << "Invalid Name. Try Again." << endl;
        }
    } while(!read);

    if (p == vec.end()) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }

    vec.erase(p);
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