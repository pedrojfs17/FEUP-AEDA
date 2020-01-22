//
// Created by pedro on 14/10/2019.
//

#include "Person.h"


Person::Person(string name, string gender, string nif, Date birth, Address address, string email, string phone) { //removi int ID -> acho que faz mais sentido ser o programa a atribuir o id
    this->name = name;                                                                              //ver client e teacher para o metodo de criacao de id
    this->gender = gender;
    this->nif = stoi(nif);
    this->birthDate = birth;
    this->age = findAge(birthDate);
    this->address = address;
    this->email = email;
    this->phone = phone;
}

void Person::setName(string name) {
    this->name = name;
}

void Person::setGender(string gender) {
    gender = toupper(gender[0]);
    if (gender == "M" || gender == "F" || gender == "U")
        this->gender = gender;
    else
        this->gender = "U";
}

void Person::setNIF(int nif) {
    this->nif = nif;
}

void Person::setBirth(Date birth) {
    this->birthDate = birth;
    this->age = findAge(birthDate);
}

void Person::setAddress(Address address) {
    this->address = address;
}

void Person::setEmail(string email) {
    this->email = email;
}

void Person::setPhone(string phone) {
    this->phone = phone;
}

string Person::getName() const {
    return name;
}

string Person::getGender() const {
    return gender;
};

int Person::getNIF() const {
    return nif;
};

Date Person::getBirth() const {
    return birthDate;
};

Address Person::getAddress() const {
    return address;
};

string Person::getEmail() const {
    return email;
};

string Person::getPhone() const {
    return phone;
};

//----------------------------------------------------------------------------------------------------------------------

int Client::next_id=1;

Client::Client(string name, string gender, string nif, Date birth, Address address, string email, string phone, bool gold_card, bool annual_subscription):Person(name,gender,nif,birth,address,email,phone) {
    this->gold_card=gold_card;
    this->annual_subscription=annual_subscription;
    this->num_id=next_id;
    next_id++;

    expenses = 0.0;

    typename vector<Activity *> ::const_iterator it=this->log.begin();
    while(it!=log.end()){
        if(gold_card){
            expenses+=((*it)->getPrice()*0.85);
        }
        else{
            expenses+=(*it)->getPrice();
        }
        it++;
    }
    typename vector<Loan *>::const_iterator itL = this->loans.begin();
    for (; itL != loans.end(); itL++) {
        expenses += (*itL)->getPrice();
    }
}

int Client::getId() const {
    return num_id;
}

void Client::setId(int id) {
    num_id=id;
}

void Client::setName(string name) {
    Person::setName(name);
}

bool Client::getGoldCard() const {
    return gold_card;
}

void Client::setGoldCard(string gold_card) {
    if(gold_card=="YES"){
        this->gold_card=true;
    }
    else{
        this->gold_card= false;
    }
}

bool Client::getAnnualSubscription() const {
    return annual_subscription;
}

void Client::setAnnualSubscription(string an_sub) {
    if(an_sub=="YES"){
        this->annual_subscription=true;
    }
    else{
        this->annual_subscription= false;
    }
}

void Client::setExpenses(double amount) {
    this->expenses=amount;
}

ostream& operator<<(ostream &out, Client const &c) {
    out<<"\nName: "<<c.getName();
    out<<"\nGender: "<<c.getGender();
    out<<"\nNIF: "<<c.getNIF();
    out<<"\nDate of Birth: "<<c.getBirth().getDate();
    out<<"\nAddress: "<<c.getAddress().getFullAddress();
    out<<"\nE-mail: "<<c.getEmail();
    out<<"\nPhone: "<<c.getPhone();
    out<<"\nGold Card: "<<boolalpha<<c.getGoldCard();
    out<<"\nAnnual Subscription: "<<boolalpha<<c.getAnnualSubscription();
    out<<"\nActivity: ";
    out<<"The Client has participated in "<<c.getActivity().size()<<" activities and has made "<<c.loans.size()<<" rentals";
    out<<"\nExpenses: "<<to_string(c.expenses).substr(0, to_string(c.expenses).find_first_of(".") + 3)<<endl;

    return out;
}

string Client::WriteToFile() const {
    string out = "";
    out += this->getName() + ";";
    out += this->getGender() + ";";
    out += to_string(this->getNIF()) + ";";
    out += this->getBirth().getDate() + ";";
    out += this->getAddress().WriteToFile() + ";";
    out += this->getEmail() + ";";
    out += this->getPhone() + ";";
    if (this->getGoldCard())
        out += "Y;";
    else
        out += "N;";
    if (this->getAnnualSubscription())
        out += "Y;";
    else
        out += "N;";

    vector<Activity *> ac = this->getActivity();

    if (gold_card || annual_subscription) {
        for (int i = 0; i < ac.size(); i++) {
            if (dynamic_cast<Trip *>(ac[i]))
                out += to_string(dynamic_cast<Trip *>(ac[i])->getID()) + ",";
        }
        if (out[out.size()-1] == ',') {
            out = out.substr(0, out.size()-1);
        }
        return out;
    }

    if (!this->getGoldCard() && !this->getAnnualSubscription()) {
        for (int i = 0; i < ac.size(); i++) {
            if (dynamic_cast<Classes *>(ac[i]))
                out += to_string(dynamic_cast<Classes *>(ac[i])->getID()) + ",";
        }
        if (out[out.size()-1] == ',') {
            out = out.substr(0, out.size()-1) + ";";
        }
        for (int i = 0; i < ac.size(); i++) {
            if (dynamic_cast<Trip *>(ac[i]))
                out += to_string(dynamic_cast<Trip *>(ac[i])->getID()) + ",";
        }
        if (out[out.size()-1] == ',') {
            out = out.substr(0, out.size()-1);
        }
    }

    return out;
}

void Client::addActivities(Activity *a) {
    log.push_back(a);
    expenses += a->getPrice();
}

vector<Activity *> Client::getActivity() const {
    return log;
}

void Client::addLoan(Loan * loan) {
    this->loans.push_back(loan);
    expenses += loan->getPrice();
}


//----------------------------------------------------------------------------------------------------------------------

Teacher::Teacher(string name, string gender, string nif, Date birth, Address address, string email, string phone, bool hired):Person(name,gender,nif,birth,address,email,phone) {
    this->hired=hired;
    string id;
    id= (char)toupper(name[0]);
    for (int i = 1; i < name.length() - 1; i++){
        if (name[i] == ' ')
            id+=(char)toupper(name[i + 1]);
    }
    this->initials_id=id;

    vector<Activity*> activity;

    this->activity=activity;

}

string Teacher::getId() const {
    return initials_id;
}

void Teacher::setId(string id) {
    initials_id=id;
}

void Teacher::addActivity(Activity *c){
   activity.push_back(c);
}

ostream& operator<<(ostream &out, Teacher const &c) {
    out<<"\nName: "<<c.getName();
    out<<"\nGender: "<<c.getGender();
    out<<"\nNIF: "<<c.getNIF();
    out<<"\nDate of Birth: "<<c.getBirth().getDate();
    out<<"\nAddress: "<<c.getAddress().getFullAddress();
    out<<"\nE-mail: "<<c.getEmail();
    out<<"\nPhone: "<<c.getPhone();
    out<<"\nID: "<<c.getId();
    out<<"\nClasses: ";
    for(int x=0;x<c.getActivity().size();x++){
        if(x!=c.getActivity().size()-1){
            out<<c.getActivity()[x]->getName()<<", ";
        }
        else
            out<<c.getActivity()[x]->getName()<<endl;

    }

    return out;
}

string Teacher::WriteToFile() const {
    string out = "";
    out += this->getName() + ";";
    out += this->getGender() + ";";
    out += to_string(this->getNIF()) + ";";
    out += this->getBirth().getDate() + ";";
    out += this->getAddress().WriteToFile() + ";";
    out += this->getEmail() + ";";
    out += this->getPhone() + ";";
    if (this->hired == 1) {
        out += "H";
    }
    else {
        out += "D";
    }
    return out;
}

vector<Activity *> Teacher::getActivity() const {
    return activity;
}

bool Teacher::getHired() const {
    return this->hired;
}

void Teacher::setHired(bool hired) {
    this->hired = hired;
}


//----------------------------------------------------------------------------------------------------------------------

Technician::Technician(string name, string gender, string nif, Date birth, Address address, string email, string phone, int availability, map<Material*,int> material_repaired):
        Person(name,gender,nif,birth,address,email,phone) {
    this->availability = availability;
    this->material_repaired=material_repaired;
    int sum=0;
    for(auto x: this->material_repaired){
        sum+=x.second;
    }
    this->numRepairs = sum;
}

int Technician::getAvailability() const {
    return this->availability;
}

int Technician::getNumRepairs() const {
    return this->numRepairs;
}

void Technician::setAvailability(int availability) {
    this->availability = availability;
}

void Technician::setNumRepairs(int numRepairs) {
    this->numRepairs = numRepairs;
}

void Technician::setMaterialsRepaired(map<Material*, int> materials) {
    this->material_repaired=materials;
}

bool Technician::operator<(const Technician &t1) const {
    if(this->availability < t1.availability){
        return true;
    }
    else if(this->availability == t1.availability){
        if(this->getNumRepairs()<t1.getNumRepairs()){
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

void Technician::repairMaterial(Material *material) {
    numRepairs++;
    availability += 2;
    if(material_repaired.find(material)!=material_repaired.end()){
        material_repaired.find(material)->second++;
    }
    else{
        material_repaired.insert(pair<Material*,int>(material,1));
    }
}

map<Material *,int> Technician::getMaterialsRepaired() const {
    return material_repaired;
}

string Technician::WriteToFile() const {
    string out = "";
    out += this->getName() + ";";
    out += this->getGender() + ";";
    out += to_string(this->getNIF()) + ";";
    out += this->getBirth().getDate() + ";";
    out += this->getAddress().WriteToFile() + ";";
    out += this->getEmail() + ";";
    out += this->getPhone()+";";
    out += to_string(this->getAvailability())+";";
    for(auto x: this->material_repaired){
        out+=to_string(x.first->getID())+"/"+to_string(x.second)+",";
    }
    if (out.back() == ',')
        out.pop_back();
    return out;
}

ostream& operator<<(ostream &out, Technician const &t) {
    out<<"\nName: "<<t.getName();
    out<<"\nGender: "<<t.getGender();
    out<<"\nNIF: "<<t.getNIF();
    out<<"\nDate of Birth: "<<t.getBirth().getDate();
    out<<"\nAddress: "<<t.getAddress().getFullAddress();
    out<<"\nE-mail: "<<t.getEmail();
    out<<"\nPhone: "<<t.getPhone();
    out<<"\nMaterials Repaired: "<<endl;
    if(t.material_repaired.empty()){
        out<<"No repairs made\n";
        return out;
    }
    for(auto x = t.material_repaired.begin();x!=t.material_repaired.end();x++){
        out<<x->first->getType()<<" - repaired "<<x->second<< " times"<<endl;
    }
    return out;
}

/*-------------CREATE AND MODIFY FUNCTIONS-------------------*/

void CreatePerson(Person *person) {
    //string  new_email, new_phone,new_nif, new_gender,new_birth, new_address;

    string new_name = readStringNoSpecial("Name: ");
    string new_gender;
    do{
        new_gender=toUpper(readStringNoSpecial("Gender (M or F): "));
        if (new_gender!="M"&&new_gender!="F")
            cout<<"Invalid Gender! Try again.\n";
    }while (new_gender!="M"&&new_gender!="F");

    int new_nif;
    do{
        new_nif = readNumber("NIF: ");
        if (new_nif<100000000 || new_nif>999999999)
            cout<<"Invalid NIF! Try again.\n";
    }while(new_nif<100000000 || new_nif>999999999);

    cout<<"Date of Birth\n";
    Date new_birth = readDate();
    cout<<"Address\n";
    Address new_address = readAddress();
    string new_email = readEmail();
    int new_phone;
    do{
        new_phone=readNumber("Phone Number: ");
        if (new_phone<900000000 || new_phone>999999999)
            cout<<"Invalid Phone Number! Try again.\n";
    }while(new_phone<900000000 || new_phone>999999999);

    person->setName(new_name);
    person->setGender(new_gender);
    person->setNIF(new_nif);
    person->setBirth(new_birth);
    person->setAddress(new_address);
    person->setEmail(new_email);
    person->setPhone(to_string(new_phone));

}


void ClientActivity(vector <Client *> vec_cl, vector <Activity *> vec_ac, vector <Classes *> vec_cla, vector <Trip *> vec_tr){
    Client *c;
    Activity *a;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Sign Up For An Activity" << endl;
    cout << "__________________________________________________\n" << endl;
    c = RemovePerson(vec_cl);

    typename vector<Classes *> ::const_iterator it=vec_cla.begin();
    typename vector<Trip *> ::const_iterator it_2=vec_tr.begin();

    cout<<"\nClasses Available:\n";
    while(it!=vec_cla.end()){
        if(!(*it)->getAnnual()){
            cout<<(*it)->getActivity();
        }
        it++;
    }
    cout<<"\nTrips Available:\n";
    while(it_2!=vec_tr.end()){
        cout<<(*it_2)->getActivity();
        it_2++;
    }

    do{
        bool read = false;

        do {
            try {
                a = FindActivity(vec_ac);
                read = true;
            }
            catch (...) {
                cout << "Invalid Name. Try Again." << endl;
            }
        } while(!read);

        if (a == NULL) {
            cout << "__________________________________________________\n" << endl;
            cout << setw(23) << right << "Operation Canceled" << endl;
            cout << "__________________________________________________\n" << endl;
            return;
        }

        if(a->getAttendees().size()<a->getMaxAttendees()){
            c->addActivities(a);
            a->addAttendee(c);
            break;
        }
        else{
            cout<<"\nThis activity has reached maximum attendance! Please choose another";
        }
    }while(true);


}

void MaterialRent(vector <Client *> clients, vector<Material *> materials, vector<Classes *> classes, vector<Loan *> &loans, vector<Course *> courses) {
    int search_nif=readNumber("Person's NIF ('0' to Exit): ");

    typename vector<Client *> ::const_iterator it=clients.begin();

    if (search_nif == 0)
        return;

    for(;it!=clients.end();it++)
        if((*it)->getNIF() == search_nif)
            goto FOUND;

    throw NotFound<Client>();

    FOUND:
    int week;
    do {
        week = readNumber("Number of the week (0 - Back): ");
        if (week < 0 || week > 100)
            cout << "Week number must be between 1 and 100" << endl;
    } while (week < 0 || week > 100);

    if (week == 0) {
        cout << "--------------- Material rental canceled ---------------";
        return;
    }

    string day;
    do {
        day = readStringNoSpecial("Day (mon/tue/wed/thu/fri): ");
        if (toUpper(day)!="MON" && toUpper(day)!="TUE" && toUpper(day)!="WED" && toUpper(day)!="THU" && toUpper(day)!="FRI")
            cout << "Invalid Input. Try again." << endl;
    } while (toUpper(day)!="MON" && toUpper(day)!="TUE" && toUpper(day)!="WED" && toUpper(day)!="THU" && toUpper(day)!="FRI");

    Time startTime;
    do {
        startTime = readTime();
        if (startTime.getHour() < 8 || startTime.getHour() > 18)
            cout << "The school is only open between 8h and 18h" << endl;
    } while (startTime.getHour() < 8 || startTime.getHour() > 18);


    vector<Material *> materialsToRent = chooseMaterials(move(classes), move(materials), startTime, day, loans, week, move(courses));

    if (materialsToRent.empty()) {
        cout << "--------------- Material rental canceled ---------------";
        return;
    }

    double price = 0;
    for (int i = 0; i < materialsToRent.size(); i++)
        price += materialsToRent[i]->getPrice();

    Loan * newloan = new Loan("Rental", toUpper(day), startTime, materialsToRent, (*it)->getNIF(), price, week);

    loans.push_back(newloan);
    (*it)->addLoan(newloan);

}


