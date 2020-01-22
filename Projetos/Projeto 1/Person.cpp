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

Client::Client() {/*this->num_id=next_id;next_id++;*/}

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
    if(gold_card=="yes"){
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
    if(an_sub=="yes"){
        this->annual_subscription=true;
    }
    else{
        this->annual_subscription= false;
    }
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

Teacher::Teacher() {}

Teacher::Teacher(string name, string gender, string nif, Date birth, Address address, string email, string phone):Person(name,gender,nif,birth,address,email,phone) {

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
    out += this->getPhone();
    return out;
}

vector<Activity *> Teacher::getActivity() const {
    return activity;
}


//----------------------------------------------------------------------------------------------------------------------


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

/*--------CREATE AND MODIFY CLIENT FUNCTIONS---------*/

void CreateClient(vector<Client *> &vec){
    Client *c = new Client();

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Create New Client" << endl;
    cout << "__________________________________________________\n" << endl;

    CreatePerson(c);

    string gld_crd ;
    do{
        gld_crd= toUpper(readStringNoSpecial("Gold Card (yes or no): "));
        if (gld_crd!="YES"&&gld_crd!="NO")
            cout<<"Invalid Input! Try again.\n";
    }while (gld_crd!="YES"&&gld_crd!="NO");
    string an_sub ;
    do{
        an_sub= toUpper(readStringNoSpecial("Annual Subscription (yes or no): "));
        if (an_sub!="YES"&&an_sub!="NO")
            cout<<"Invalid Input! Try again.\n";
    }while (an_sub!="YES"&&an_sub!="NO");
    c->setGoldCard(gld_crd);
    c->setAnnualSubscription(an_sub);
    addN(vec,c);

}

void ModifyClient(vector<Client *> &vec){
    Client *c;

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Modify Client" << endl;
    cout << "__________________________________________________\n" << endl;

    bool read = false;

    do {
        try {
            c = ModifyPerson(vec);
            read = true;
        }
        catch (...) {
            cout << "Invalid NIF. Try Again." << endl;
        }
    } while(!read);

    if (c == NULL) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }

    string gld_crd ;
    do{
        gld_crd= toUpper(readStringNoSpecial("Gold Card (yes or no): "));
        if (gld_crd!="YES"&&gld_crd!="NO")
            cout<<"Invalid Input! Try again.\n";
    }while (gld_crd!="YES"&&gld_crd!="NO");
    string an_sub ;
    do{
        an_sub= toUpper(readStringNoSpecial("Annual Subscription (yes or no): "));
        if (an_sub!="YES"&&an_sub!="NO")
            cout<<"Invalid Input! Try again.\n";
    }while (an_sub!="YES"&&an_sub!="NO");
    c->setGoldCard(gld_crd);
    c->setAnnualSubscription(an_sub);

}

void RemoveClient(vector <Client *> &vec){
    Client *c;

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Client" << endl;
    cout << "__________________________________________________\n" << endl;

    bool read = false;

    do {
        try {
            c = ModifyPerson(vec);
            read = true;
        }
        catch (...) {
            cout << "Invalid NIF. Try Again." << endl;
        }
    } while(!read);

    if (c == NULL) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }
    removeN(vec,c);

}

void ClientActivity(vector <Client *> &vec_cl, vector <Activity *> &vec_ac, vector <Classes *> &vec_cla, vector <Trip *> &vec_tr){
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
            cout<<(*(*it));
        }
        it++;
    }
    cout<<"\nTrips Available:\n";
    while(it_2!=vec_tr.end()){
        cout<<(*(*it_2));
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

void MaterialRent(vector <Client *> &clients, vector<Material *> materials, vector<Classes *> classes, vector<Loan *> &loans, vector<Course *> courses) {
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

/*--------CREATE AND MODIFY TEACHER FUNCTIONS---------*/

void CreateTeacher(vector<Teacher *> &vec){
    Teacher *t = new Teacher();
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Create New Teacher" << endl;
    cout << "__________________________________________________\n" << endl;
    CreatePerson(t);

    string id;
    id= (char)toupper(t->getName()[0]);
    for (int i = 1; i < t->getName().length() - 1; i++){
        if (t->getName()[i] == ' ')
            id+=(char)toupper(t->getName()[i + 1]);
    }

    t->setId(id);

    addN(vec,t);
}

void ModifyTeacher(vector<Teacher *> &vec){
    Teacher *t;

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Modify Teacher" << endl;
    cout << "__________________________________________________\n" << endl;

    bool read = false;

    do {
        try {
            t = ModifyPerson(vec);
            read = true;
        }
        catch (...) {
            cout << "Invalid NIF. Try Again." << endl;
        }
    } while(!read);

    if (t == NULL) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }

    string id;
    id= (char)toupper(t->getName()[0]);
    for (int i = 1; i < t->getName().length() - 1; i++){
        if (t->getName()[i] == ' ')
            id+=(char)toupper(t->getName()[i + 1]);
    }

    t->setId(id);

}

void RemoveTeacher(vector <Teacher *> &vec){
    Teacher *t;

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Teacher" << endl;
    cout << "__________________________________________________\n" << endl;

    bool read = false;

    do {
        try {
            t = ModifyPerson(vec);
            read = true;
        }
        catch (...) {
            cout << "Invalid NIF. Try Again." << endl;
        }
    } while(!read);

    if (t == NULL) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }

    removeN(vec,t);

}
