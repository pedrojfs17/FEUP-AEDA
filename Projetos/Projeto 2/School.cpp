#include "School.h"
using namespace std;


School::School(string place, string directorName, unsigned int numClients) {
    this->place = place;
    this->directorName = directorName;
    this->numClients = numClients;
}

School::School(istream &clients_file, istream &teachers_file, istream &classes_file, istream &courses_file, istream &trips_file, istream &material_file, istream &loans_file, istream &tech_file) {
    string material_name, amount, price, used,existing;
    bool e;


    if (material_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto CLASSESFILE;

    while(!material_file.eof()){
        getline(material_file,material_name,';');
        getline(material_file,price,';');
        getline(material_file,amount, ';');
        getline(material_file,used,';');
        getline(material_file,existing);
        if(existing=="E"){
            e=1;
        }
        else{
            e=0;
        }
        Material *new_material = new Material(material_name,stod(price),stoi(amount), stoi(used),e);
        schoolMaterials.insert(new_material);
        if(e){
            materials.push_back(new_material);
        }

    }

    CLASSESFILE:

    string type_activity,name_activity,time, day, annual,doubleClass,act_id, materials_needed, idmaterial;
    vector<Material *> materialsNeeded;
    vector<int> ids;

    if (classes_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto COURSESFILE;

    while(!classes_file.eof()) {
        getline(classes_file, name_activity, ';');
        getline(classes_file, annual, ';');
        getline(classes_file, time,';');
        getline(classes_file, day, ';');
        getline(classes_file, doubleClass, ';');
        getline(classes_file, price, ';');
        getline(classes_file, materials_needed,';');
        getline(classes_file, act_id);
        stringstream mat(materials_needed);
        while( getline(mat, idmaterial, ',') )
            ids.push_back(stoi(idmaterial));
        for (int i = 0; i < ids.size(); i++)
            materialsNeeded.push_back(materials[ids[i] - 1]);
        Classes *new_activity = new Classes(name_activity, annual, time, day, doubleClass, price, act_id, materialsNeeded);
        activities.push_back(new_activity);
        classes.push_back(new_activity);
        materialsNeeded.clear();
        ids.clear();
    }

    COURSESFILE:

    string classesid, numWeeks, id;
    vector<Classes *> course_classes;
    ids.clear();

    if (courses_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto TRIPSFILE;

    while(!courses_file.eof()) {
        getline(courses_file, name_activity, ';');
        getline(courses_file, price, ';');
        getline(courses_file, classesid, ';');
        getline(courses_file, numWeeks);
        stringstream stream(classesid);
        while( getline(stream, id, ',') )
            ids.push_back(stoi(id));
        for (int i = 0; i < ids.size(); i++) {
            classes[ids[i] - 1]->setAnnual(true);
            course_classes.push_back(classes[ids[i] - 1]);
        }
        Course * new_course = new Course(name_activity, price, course_classes, numWeeks);
        activities.push_back(new_course);
        courses.push_back(new_course);
        ids.clear();
        course_classes.clear();
    }

    TRIPSFILE:

    string location, beginDate, endDate, maxAtt;

    if (trips_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto CLIENTSFILE;

    while(!trips_file.eof()) {
        getline(trips_file, name_activity, ';');
        getline(trips_file, price, ';');
        getline(trips_file, location, ';');
        getline(trips_file, beginDate, ';');
        getline(trips_file, endDate, ';');
        getline(trips_file, maxAtt);
        Trip * new_trip = new Trip(name_activity, location, Date(beginDate), Date(endDate), stod(price), stoi(maxAtt));
        activities.push_back(new_trip);
        trips.push_back(new_trip);
    }

    CLIENTSFILE:

    string name_person, gender, birth_date, address, email, phone, gold_card, annual_subscription, nif;
    bool gld_crd=0, an_subs=0;

    if (clients_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto TEACHERSFILE;

    while(!clients_file.eof()){                                       //Provavelmente será preciso alterar isto para ter 1 cliente por linha e caracteres separadores de clientes
        getline(clients_file,name_person,';');                            // ver clients.txt
        getline(clients_file,gender,';');
        getline(clients_file,nif,';');
        getline(clients_file,birth_date,';');
        getline(clients_file,address,';');
        getline(clients_file,email,';');
        getline(clients_file,phone,';');
        getline(clients_file,gold_card,';');
        if(gold_card=="Y")
            gld_crd = 1;
        else
            gld_crd = 0;
        getline(clients_file,annual_subscription, ';');
        if(annual_subscription=="Y")
            an_subs = 1;
        else
            an_subs = 0;
        Client *new_client = new Client(name_person,gender, nif,Date(birth_date),Address(address),email,phone,gld_crd,an_subs);
        if (an_subs || gld_crd)
            for (int i = 0; i < classes.size(); i++) {
                new_client->addActivities(classes[i]);
                classes[i]->addAttendee(new_client);
            }
        if (!gld_crd && !an_subs) {
            getline(clients_file, classesid, ';');
            stringstream stream(classesid);
            while (getline(stream, id, ','))
                ids.push_back(stoi(id));
            for (int i = 0; i < ids.size(); i++) {
                if (ids[i] < classes.size()) {
                    new_client->addActivities(classes[ids[i] - 1]);
                    classes[ids[i] - 1]->addAttendee(new_client);
                }
            }
        }
        ids.clear();
        getline(clients_file, classesid);
        stringstream stream2(classesid);
        while (getline(stream2, id, ','))
            ids.push_back(stoi(id));
        for (int i = 0; i < ids.size(); i++) {
            if (ids[i] < trips.size()) {
                new_client->addActivities(trips[ids[i] - 1]);
                trips[ids[i] - 1]->addAttendee(new_client);
            }
        }
        ids.clear();
        clients.push_back(new_client);
    }

    TEACHERSFILE:

    /* Precisamos de meter mais uma variavel nos professores para saber se eles estao ativos ou nao
     * Os que nao estiverem ativos, adicionamos à HashTable e logo a seguir removemos para ele ficar "DELETED"
     * Assim ficamos com todos os professores na HashTable.
     * Quando formos a criar um novo professor vamos ter que ir buscar todos os que estão "DELETED" e mostrar. A pessoa
     * Pode escolher se quer escolher um daqueles professores para torna-lo ativo ou escolher "adicionar um novo" e só ai
     * É que chamamos a funcao de createTeacher e adicionamo-lo à HashTable.
     * Para remover é so fazer schoolTeacher.remove(x) em que x é o prof a remover.
     * */
    string hired;
    bool active;

    if (teachers_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto LOANSFILE;

    while(!teachers_file.eof()){
        getline(teachers_file,name_person,';');
        getline(teachers_file,gender,';');
        getline(teachers_file,nif,';');
        getline(teachers_file,birth_date,';');
        getline(teachers_file,address,';');
        getline(teachers_file,email,';');
        getline(teachers_file,phone,';');
        getline(teachers_file,hired);
        if(hired=="H")
            active=1;
        else
            active=0;
        Teacher *new_teacher = new Teacher(name_person,gender,nif,Date(birth_date),Address(address),email,phone,active);

        schoolTeachers.insert(new_teacher);
        if(active==1){
            teachers.push_back(new_teacher);
        }
    }

    sortClassesByHour();
    AssignTeachers(classes,teachers);

    LOANSFILE:

    string idmaterial_need;

    if (loans_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto TECHFILE;

    while(!loans_file.eof()) {
        getline(loans_file,day,';');
        getline(loans_file,time,';');
        getline(loans_file,materials_needed,';');
        stringstream mat(materials_needed);
        while(getline(mat, idmaterial_need, ',') )
            ids.push_back(stoi(idmaterial_need));
        for (int i = 0; i < ids.size(); i++){
            for(auto x:schoolMaterials){
                if(ids[i]==x->getID()){
                    materialsNeeded.push_back(x);
                    break;
                }
            }
        }
        getline(loans_file,nif,';');
        getline(loans_file,price, ';');
        getline(loans_file, numWeeks);
        Loan * new_loan = new Loan("Rental",day, Time(time), materialsNeeded, stoi(nif), stod(price), stoi(numWeeks));
        loans.push_back(new_loan);
        ids.clear();
        materialsNeeded.clear();
    }

    AssignLoans();

    TECHFILE:

    string availability,material,material_amount;
    vector<string> mater;
    map<Material*,int> material_repaired;

    if (tech_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        return;

    while(!tech_file.eof()){
        getline(tech_file,name_person,';');
        getline(tech_file,gender,';');
        getline(tech_file,nif,';');
        getline(tech_file,birth_date,';');
        getline(tech_file,address,';');
        getline(tech_file,email,';');
        getline(tech_file,phone,';');
        getline(tech_file,availability,';');
        getline(tech_file,material);
        stringstream mat(material);
        while(getline(mat, material_amount, ',') )
            //cout<<material_amount<<endl;
            mater.push_back(material_amount);
        for (int i = 0; i < mater.size(); i++){
            //cout<<stoi(mater[i].substr(0,mater[i].find('/')))-1<<endl;
            //cout<<stoi(mater[i].substr(mater[i].find('/') + 1))<<endl;
            material_repaired.insert(pair<Material*,int>(materials[stoi(mater[i].substr(0,mater[i].find('/')))-1],stoi(mater[i].substr(mater[i].find('/') + 1))));
        }
        mater.clear();
        cout<<material_repaired.size()<<endl;
        Technician *new_technician = new Technician(name_person,gender,nif,Date(birth_date),Address(address),email,phone,stoi(availability),material_repaired);
        technicians.push(new_technician);
        cout<<material_repaired.size()<<endl;
        material_repaired.clear();
        cout<<"Next tech\n";
    }
}

string School::getPlace() const {
    return this->place;
}

void School::PrintAllClients() {
    vector<Client*> ::const_iterator it=clients.begin();
    while(it!=clients.end()){
        cout<<(*(*it));
        it++;
    }
}

void School::PrintClient() {
    int search_nif=readNumber("Person's NIF ('0' to Exit): ");

    typename vector<Client *> ::const_iterator it=clients.begin();

    if (search_nif == 0)
        return;

    for(;it!=clients.end();it++){
        if((*it)->getNIF()==search_nif){
            cout<<(*(*it));
            return;
        }
    }

    throw NotFound<Client>();
}

void School::PrintAllTeachers() {
    for(auto x:getHiredTeachers()){
        cout<<(*x);
    }
}

void School::PrintTeacher() {
    string search_init = readString("Teacher's initials ('0' to Exit): ");

    typename vector<Teacher *> ::const_iterator it=getHiredTeachers().begin();

    if (search_init == "0")
        return;

    search_init = toUpper(search_init);

    for(;it!=getHiredTeachers().end();it++)
        if((*it)->getId() == search_init) {
            cout << (*(*it));
            return;
        }

    throw NotFound<Teacher>();
}

void School::PrintAllActivities(){
    typename vector<Classes *> ::const_iterator it=classes.begin();
    typename vector<Trip *> ::const_iterator it_2=trips.begin();
    typename vector<Course *> ::const_iterator it_3=courses.begin();

    cout << "__________________________________________________" << endl;
    cout << "\t\tClasses Available:\n";
    cout << "__________________________________________________" << endl;
    while(it!=classes.end()){
        if(!(*it)->getAnnual()){
            cout<<(*it)->getActivity();
            cout << "__________________________________________________" << endl;
        }
        it++;
    }

    cout << "__________________________________________________" << endl;
    cout << "\t\tCourses Available:\n";
    cout << "__________________________________________________" << endl;
    while(it_3!=courses.end()){
        cout<<(*it_3)->getActivity();
        cout << "__________________________________________________" << endl;
        it_3++;
    }

    cout << "__________________________________________________" << endl;
    cout << "\t\tTrips Available:\n";
    cout << "__________________________________________________" << endl;
    while(it_2!=trips.end()){
        cout<<(*it_2)->getActivity();
        cout << "__________________________________________________" << endl;
        it_2++;
    }
}

void School::PrintAllLoans(){
    cout << "Loans Made: \n";
    for (int i = 0; i < loans.size(); i++)
        cout << i + 1 << " -> " << loans[i]->showLoan() << endl;
}

void School::PrintTrips() {
    typename vector<Trip *> ::const_iterator it_2=trips.begin();

    cout << "__________________________________________________" << endl;
    cout << "\t\tTrips Available:\n";
    cout << "__________________________________________________" << endl;
    while(it_2!=trips.end()){
        cout<<(*it_2)->getActivity();
        cout << "__________________________________________________" << endl;
        it_2++;
    }
}

void School::PrintTechnician() {
    int search_nif=readNumber("Person's NIF ('0' to Exit): ");
    if (search_nif == 0)
        return;

    vector<Technician *> temp;

    while(!technicians.empty()){
        temp.push_back(technicians.top());
        technicians.pop();
    }
    for(auto x:temp){
        technicians.push(x);
    }

    for(auto it : temp){
        if(it->getNIF()==search_nif){
            cout<<(*it);
            return;
        }
    }

    throw NotFound<Technician>();
}

void School::PrintAllTechnicians(){
    vector<Technician *> temp;
    if(technicians.empty()){
        cout<<"No hired technicians!\n";
        return;
    }
    while(!technicians.empty()){
        temp.push_back(technicians.top());
        cout<<(*technicians.top());
        technicians.pop();
    }
    for(auto x:temp){
        technicians.push(x);
    }

}


void School::addClient(Client *client) {
    this->clients.push_back(client);
    this->numClients = clients.size();
}

void School::addTeacher(Teacher *teacher) {
    teacher->setHired(true);
    this->teachers.push_back(teacher);
    this->schoolTeachers.insert(teacher);
}

void School::addActivity(Activity *activity) {
    this->activities.push_back(activity);
}

void School::addClass(Classes *classes) {
    this->classes.push_back(classes);
    cout<<this->classes.size();
    this->activities.push_back(classes);

}

void School::addCourse(Course *course) {
    this->courses.push_back(course);
    this->activities.push_back(course);
}

void School::addTrip(Trip *trip) {
    this->trips.push_back(trip);
    this->activities.push_back(trip);
}

void School::addMaterial(Material *material) {
    this->materials.push_back(material);
    this->schoolMaterials.insert(material);
}

vector<Client *> School::getClients() const {
    return this->clients;
}

vector<Teacher *> School::getTeachers() const {
    return this->teachers;
}

TeacherHashTable School::getHashTable() const {
    return schoolTeachers;
}

vector<Activity *> School::getActivities() const {
    return this->activities;
}

vector<Material *> School::getMaterials() const {
    return this->materials;
}

vector<Classes *> School::getClasses() const{
    return this->classes;
}

vector<Course *> School::getCourses() const {
    return this->courses;
}

vector<Trip *> School::getTrips() const{
    return this->trips;
}

vector<Loan *> School::getLoans() const {
    return this->loans;
}

void School::exitSchool() {

    ofstream clientsFile, teacherFile, classesFile, coursesFile, tripsFile, loansFile, materialsFile, techniciansFile;

    //WRITE ON CLIENTS FILE
    clientsFile.open("..\\Schools\\"+getPlace()+"\\clients.txt");
    for (int i = 0; i < clients.size(); i++) {
        if (i != 0)
            clientsFile << endl;
        clientsFile << clients[i]->WriteToFile();
    }
    clientsFile.close();


    //WRITE TO TEACHERS FILE
    teacherFile.open("..\\Schools\\"+getPlace()+"\\teachers.txt");
    int count = 0;
    for (auto x : schoolTeachers) {
        teacherFile << x->WriteToFile();
        count++;
        if (count < schoolTeachers.size())
            teacherFile << endl;
    }
    teacherFile.close();


    //WRITE TO CLASSES FILE
    classesFile.open("..\\Schools\\"+getPlace()+"\\classes.txt");
    for (int i = 0; i < classes.size(); i++) {
        if (i != 0)
            classesFile << endl;
        classesFile << classes[i]->WriteToFile();
    }
    classesFile.close();


    //WRITE TO COURSES FILE
    coursesFile.open("..\\Schools\\"+getPlace()+"\\courses.txt");
    for (int i = 0; i < courses.size(); i++) {
        if (i != 0)
            coursesFile << endl;
        coursesFile << courses[i]->WriteToFile();
    }
    coursesFile.close();


    //WRITE TO TRIPS FILE
    tripsFile.open("..\\Schools\\"+getPlace()+"\\trips.txt");
    for (int i = 0; i < trips.size(); i++) {
        if (i != 0)
            tripsFile << endl;
        tripsFile << trips[i]->WriteToFile();
    }
    tripsFile.close();

    //WRITE TO LOANS FILE
    loansFile.open("..\\Schools\\"+getPlace()+"\\loans.txt");
    for (int i = 0; i < loans.size(); i++) {
        if (i != 0)
            loansFile << endl;
        loansFile << loans[i]->WriteToFile();
    }
    loansFile.close();


    //WRITE TO MATERIALS FILE
    materialsFile.open("..\\Schools\\"+getPlace()+"\\materials.txt");
    count=0;
    for (auto x: schoolMaterials) {
        materialsFile << x->WriteToFile();
        count++;
        if (count < schoolMaterials.size())
            materialsFile << endl;
    }
    materialsFile.close();

    //WRITE TO TECHNICIANS FILE
    techniciansFile.open("..\\Schools\\"+getPlace()+"\\technicians.txt");
    while(!technicians.empty()){
        techniciansFile << technicians.top()->WriteToFile();
        technicians.pop();
        if (!technicians.empty())
            techniciansFile << endl;
    }
    techniciansFile.close();

    ofstream schoolfile;

    //WRITE TO SCHOOL FILE
    schoolfile.open("..\\Schools\\"+getPlace()+"\\" + getPlace()+"School.txt");
    schoolfile << getPlace() << endl;
    schoolfile << getDirector() << endl;
    schoolfile << getClients().size() << endl;
    schoolfile << "clients.txt" << endl;
    schoolfile << "teachers.txt" << endl;
    schoolfile << "classes.txt" << endl;
    schoolfile << "courses.txt" << endl;
    schoolfile << "trips.txt" << endl;
    schoolfile << "materials.txt" << endl;
    schoolfile << "loans.txt" << endl;
    schoolfile << "technicians.txt";

}

void School::setDirector(string name) {
    directorName=name;
}

void School::setLocation(string location) {
    place=location;
}

void School::setnumClients(int numClients) {
    this->numClients=numClients;
}

void School::setClients(vector<Client *> clients) {
    this->clients = clients;
}

void School::setTeachers(vector<Teacher *> teachers) {
    this->teachers = teachers;
}

void School::setClasses(vector<Classes *> classes) {
    this->classes = classes;
}

void School::setCourses(vector<Course *> courses) {
    this->courses = courses;
}

void School::setTrips(vector<Trip *> trips) {
    this->trips = trips;
}

void School::setMaterials(vector<Material *> materials) {
    this->materials = materials;
}

void School::setLoans(vector<Loan *> loans) {
    this->loans = loans;
}

void School::PrintClientTimeTable() {
    int search_nif = readNumber("Client's NIF ('0' to Exit): ");

    typename vector<Client *> ::const_iterator it=clients.begin();

    if (search_nif == 0)
        return;

    for(;it!=clients.end();it++)
        if((*it)->getNIF() == search_nif)
            goto FOUND;

    throw NotFound<Client>();

    FOUND:

    vector<Classes *> clientClasses;
    vector<Activity *> clientAcitivities = (*it)->getActivity();

    for (int i = 0; i < classes.size(); i++) {
        if ((*it)->getAnnualSubscription() && classes[i]->getAnnual())
            clientClasses.push_back(classes[i]);
        if (find(clientAcitivities.begin(), clientAcitivities.end(), classes[i]) != clientAcitivities.end())
            clientClasses.push_back(classes[i]);
    }

    int week;
    do {
        week = readNumber("Time table of the week (0 - Back): ");
        if (week < 0 || week > 100)
            cout << "Week number must be between 1 and 100" << endl;
    } while (week < 0 || week > 100);

    if (week == 0)
        return;

    vector<Classes *> weekClasses = getWeekClasses(week, clientClasses, courses);

    typename vector<Classes *> ::const_iterator itC=weekClasses.begin();
    Time classTime(0,45);
    Time finishTime;

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "TIME TABLE" << endl;
    cout << "__________________________________________________" << endl;
    cout << endl << "Monday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "MON") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << " (" << (*itC)->getTeacher()->getId() << ")" << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Tuesday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "TUE") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << " (" << (*itC)->getTeacher()->getId() << ")" << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Wednesday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "WED") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << " (" << (*itC)->getTeacher()->getId() << ")" << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Thursday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "THU") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << " (" << (*itC)->getTeacher()->getId() << ")" << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Friday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "FRI") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << " (" << (*itC)->getTeacher()->getId() << ")" << endl;
        }
        itC++;
    }
    cout << "__________________________________________________\n";
}

void School::PrintTeacherTimeTable() {
    string search_init = readStringNoSpecial("Teacher's initials ('0' to Exit): ");

    typename vector<Teacher *> ::const_iterator it=teachers.begin();

    if (search_init == "0")
        return;

    search_init = toUpper(search_init);

    for(;it!=teachers.end();it++)
        if((*it)->getId() == search_init)
            goto FOUND;

    throw NotFound<Teacher>();

    FOUND:

    vector<Classes *> teacherClasses;

    for (int i = 0; i < classes.size(); i++) {
        if (classes[i]->getTeacher()->getId() == search_init) {
            teacherClasses.push_back(classes[i]);
        }
    }

    int week;
    do {
        week = readNumber("Time table of the week (0 - Back): ");
        if (week < 0 || week > 100)
            cout << "Week number must be between 1 and 100" << endl;
    } while (week < 0 || week > 100);

    if (week == 0)
        return;

    vector<Classes *> weekClasses = getWeekClasses(week, teacherClasses, courses);

    typename vector<Classes *> ::const_iterator itC=weekClasses.begin();
    Time classTime(0,45);
    Time finishTime;

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "TIME TABLE" << endl;
    cout << "__________________________________________________" << endl;
    cout << endl << "Monday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "MON") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Tuesday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "TUE") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Wednesday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "WED") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Thursday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "THU") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << endl;
        }
        itC++;
    }
    cout << "__________________________________________________";
    itC=weekClasses.begin();
    cout << endl << "Friday:" << endl;
    while(itC!=weekClasses.end()) {
        if ((*itC)->getDay() == "FRI") {
            if ((*itC)->getDoubleClass())
                finishTime = (*itC)->getStartTime() + classTime + classTime;
            else
                finishTime = (*itC)->getStartTime() + classTime;
            cout << (*itC)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*itC)->getName() << endl;
        }
        itC++;
    }
    cout << "__________________________________________________\n";
}

void School::PrintAllClassesTimeTable() {
    int week;
    do {
        week = readNumber("Time table of the week (0 - Back): ");
        if (week < 0 || week > 100)
            cout << "Week number must be between 1 and 100" << endl;
    } while (week < 0 || week > 100);

    if (week == 0)
        return;

    vector<Classes *> weekClasses = getWeekClasses(week, classes, courses);

    Time classTime(0,45);
    Time finishTime;

    typename vector<Classes *>::const_iterator it = weekClasses.begin();

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "TIME TABLE" << endl;
    cout << "__________________________________________________";
    cout << endl << "Monday:" << endl;
    while(it!=weekClasses.end()) {
        if ((*it)->getDay() == "MON") {
            if ((*it)->getDoubleClass())
                finishTime = (*it)->getStartTime() + classTime + classTime;
            else
                finishTime = (*it)->getStartTime() + classTime;
            cout << (*it)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*it)->getName() << " (" << (*it)->getTeacher()->getId() << ")" << endl;
        }
        it++;
    }
    cout << "__________________________________________________";
    it=weekClasses.begin();
    cout << endl << "Tuesday:" << endl;
    while(it!=weekClasses.end()) {
        if ((*it)->getDay() == "TUE") {
            if ((*it)->getDoubleClass())
                finishTime = (*it)->getStartTime() + classTime + classTime;
            else
                finishTime = (*it)->getStartTime() + classTime;
            cout << (*it)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*it)->getName() << " (" << (*it)->getTeacher()->getId() << ")" << endl;
        }
        it++;
    }
    cout << "__________________________________________________";
    it=weekClasses.begin();
    cout << endl << "Wednesday:" << endl;
    while(it!=weekClasses.end()) {
        if ((*it)->getDay() == "WED") {
            if ((*it)->getDoubleClass())
                finishTime = (*it)->getStartTime() + classTime + classTime;
            else
                finishTime = (*it)->getStartTime() + classTime;
            cout << (*it)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*it)->getName() << " (" << (*it)->getTeacher()->getId() << ")" << endl;
        }
        it++;
    }
    cout << "__________________________________________________";
    it=weekClasses.begin();
    cout << endl << "Thursday:" << endl;
    while(it!=weekClasses.end()) {
        if ((*it)->getDay() == "THU") {
            if ((*it)->getDoubleClass())
                finishTime = (*it)->getStartTime() + classTime + classTime;
            else
                finishTime = (*it)->getStartTime() + classTime;
            cout << (*it)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*it)->getName() << " (" << (*it)->getTeacher()->getId() << ")" << endl;
        }
        it++;
    }
    cout << "__________________________________________________";
    it=weekClasses.begin();
    cout << endl << "Friday:" << endl;
    while(it!=weekClasses.end()) {
        if ((*it)->getDay() == "FRI") {
            if ((*it)->getDoubleClass())
                finishTime = (*it)->getStartTime() + classTime + classTime;
            else
                finishTime = (*it)->getStartTime() + classTime;
            cout << (*it)->getStartTime().getTime() << " - " << finishTime.getTime() << " -> " << (*it)->getName() << " (" << (*it)->getTeacher()->getId() << ")" << endl;
        }
        it++;
    }
    cout << "__________________________________________________\n";
}

void School::AssignTeachers(vector<Classes *> classes, vector<Teacher *> teachers){
    if(teachers.empty()){
        return;
    }
    for (int i = 0; i < classes.size(); i++) {
        teachers[i % teachers.size()]->addActivity(classes[i]);
        classes[i]->setTeacher(teachers[i % teachers.size()]);
    }
}

void School::sortClassesByHour() {
    sort(classes.begin(), classes.end(), CompareTwoClassesByTime);
}

bool CompareTwoClassesID(Classes * class1, Classes * class2) {
    return class1->getID() < class2->getID();
}

void School::sortClassesByID() {
    sort(classes.begin(), classes.end(), CompareTwoClassesID);
}

void School::sendEmail() {
    cout << "Simulation of an E-mail sent to a client\n\n";

    int op = choosePerson(clients);

    if (op == 0)
        return;

    Client *c = clients[op-1];

    if(!c->getAnnualSubscription() && !c->getGoldCard()){
        cout<<"This Client is not eligible for a report.\n";
        return;
    }

    cout << "------------------------------ MONTHLY REPORT ------------------------------";
    cout << "\n     CLIENT: " << c->getName() ;
    cout << "\n     NIF: " << c->getNIF();
    cout << "\n     BIRTH DATE: " << c->getBirth().getDate();
    cout << "\n     EMAIL: " << c->getEmail();
    cout << "\n     PHONE: " << c->getPhone() << endl;

    vector<Activity *> ac = c->getActivity();

    if (!c->getGoldCard())
        goto REPORT;
    else
        goto ACTIVITIES;

    ACTIVITIES:

    cout << "-------------------------------- ACTIVITIES --------------------------------" << endl;

    for (int x = 0; x < ac.size(); x++)
        cout << "  " << x + 1 << " - " << ac[x]->getName() << endl;

    REPORT:

    cout << "---------------------------------- REPORT ----------------------------------";
    cout << "\n     The client had a great evolution in the "
            "" << ac.size() << " activities he attended. \n"
                               "     If he continues to attend those classes, he will improve his techniques \n"
                               "  a lot and will become more qualified for those activities. The key is the \n"
                               "  attendance. \n"
                               "     We are hoping to see " << c->getName() << " in the future classes that will happen\n"
                               "  to help him reach his goals.\n";

    cout << "----------------------------------------------------------------------------" << endl;
}

void School::AssignLoans() {
    typename vector<Loan *>::const_iterator itL = loans.begin();
    typename vector<Client *>::const_iterator itC;
    int search_nif;

    for (; itL != loans.end(); itL++) {
        search_nif = (*itL)->getClientsNIF();
        for (itC = clients.begin(); itC != clients.end(); itC++) {
            if ((*itC)->getNIF() == search_nif) {
                (*itC)->addLoan(*itL);
                break;
            }
        }
    }
}

extern int sortingSchoolsMethod;

bool School::operator < (const School &school1) const {
    switch(sortingSchoolsMethod) {
        case 1: // LOCATION
            if (this->place < school1.place)
                return true;
            else if (this->place == school1.place)
                return this->numClients < school1.numClients;
            else
                return false;
        case 2: // DIRECTOR'S NAME
            if (this->directorName < school1.directorName)
                return true;
            else if (this->directorName == school1.directorName)
                return this->place < school1.place;
            else
                return false;
        case 3: // NUMBER OF CLIENTS, ASCENDING ORDER
            if (this->numClients < school1.numClients)
                return true;
            else if (this->numClients == school1.numClients)
                return this->place < school1.place;
            else
                return false;
        case 4: // NUMBER OF CLIENTS, DESCENDING ORDER
            if (this->numClients > school1.numClients)
                return true;
            else if (this->numClients == school1.numClients)
                return this->place < school1.place;
            else
                return false;
        default:
            return true;
    }
}

School loadSchool(string location) {
    string filePath, schoolFilePath;

    filePath = "..\\Schools\\" + location + "\\";
    schoolFilePath = "..\\Schools\\" + location + "\\" + location + "School.txt";

    ifstream schoolFile;
    schoolFile.open(schoolFilePath);

    string place, director, numClients;
    string clientsFileName, teachersFileName, classesFileName, coursesFileName, tripsFileName, loansFileName, materialsFileName,techniciansFileName;
    while (!schoolFile.eof()) {
        getline(schoolFile, place);
        getline(schoolFile, director);
        getline(schoolFile, numClients);
        getline(schoolFile, clientsFileName);
        getline(schoolFile, teachersFileName);
        getline(schoolFile, classesFileName);
        getline(schoolFile, coursesFileName);
        getline(schoolFile, tripsFileName);
        getline(schoolFile, materialsFileName);
        getline(schoolFile, loansFileName);
        getline(schoolFile, techniciansFileName);
    }

    ifstream client_file,teacher_file,material_file, classes_file, courses_file, trips_file, loans_file, tech_file;

    client_file.open(filePath + clientsFileName);
    teacher_file.open(filePath + teachersFileName);
    classes_file.open(filePath + classesFileName);
    courses_file.open(filePath + coursesFileName);
    trips_file.open(filePath + tripsFileName);
    loans_file.open(filePath + loansFileName);
    material_file.open(filePath + materialsFileName);
    tech_file.open(filePath+techniciansFileName);

    schoolFile.close();
    School s(client_file,teacher_file,classes_file, courses_file, trips_file, material_file, loans_file,tech_file);
    s.setLocation(place);
    s.setDirector(director);
    s.setnumClients(stoi(numClients));

    return s;
}

void createSchool(BST<School> * schoolTree){
    bool existing=false;
    string location, directorName; unsigned int numClients;

    BSTItrIn<School> it(*schoolTree);

    BSTItrIn<School> it2(*schoolTree);

    do{
        existing = false;
        it=it2;
        location = readStringNoSpecial("Location of the school ('BACK' - Back): ");
        if (toUpper(location) == "BACK")
            return;
        while(!it.isAtEnd()) {
            if (toUpper(it.retrieve().getPlace()) == toUpper(location)) {
                existing = true;
                cout<<"School already exists!\n";
                break;
            }
            it.advance();
        }
    } while(existing);

    directorName = readStringNoSpecial("Name of the director of the school: ");
    //numClients=readNumber("Number of clients of the client: ");
    numClients = 0;

    schoolTree->insert(School(location, directorName, numClients));

    string filePath, schoolFilePath, clients,teachers,classes,courses,trips,loans,materials,technicians;

    filePath = "..\\Schools\\"+ location+ "\\";
    if(!mkdir(filePath.c_str())){
        schoolFilePath = "..\\Schools\\" + location + "\\" + location + "School.txt";
        clients=filePath+"clients.txt";
        teachers=filePath+"teachers.txt";
        classes=filePath+"classes.txt";
        courses=filePath+"courses.txt";
        trips=filePath+"trips.txt";
        loans=filePath+"loans.txt";
        materials=filePath+"materials.txt";
        technicians=filePath+"technicians.txt";

        ofstream newFile;
        newFile.open(schoolFilePath);
        newFile<< location<<endl;
        newFile<< directorName<<endl;
        newFile<< numClients<<endl;
        newFile<<"clients.txt"<<endl;
        newFile<<"teachers.txt"<<endl;
        newFile<<"classes.txt"<<endl;
        newFile<<"courses.txt"<<endl;
        newFile<<"trips.txt"<<endl;
        newFile<<"materials.txt"<<endl;
        newFile<<"loans.txt"<<endl;
        newFile<<"technicians.txt";
        newFile.close();
        newFile.open(clients);
        newFile.close();
        newFile.open(teachers);
        newFile.close();
        newFile.open(classes);
        newFile.close();
        newFile.open(courses);
        newFile.close();
        newFile.open(trips);
        newFile.close();
        newFile.open(loans);
        newFile.close();
        newFile.open(materials);
        newFile.close();
        newFile.open(technicians);
        newFile.close();
    }
    else{
        cout<<"Couldn't create directory\n";
    }

}

void deleteSchool(BST<School> * schoolTree){

    bool existing=true;
    string location, directorName; unsigned int numClients;

    BSTItrIn<School> it(*schoolTree);
    BSTItrIn<School> it2(*schoolTree);

    do{
        existing = true;
        it=it2;
        location = readStringNoSpecial("Location of the school ('BACK' - Back): ");
        if (toUpper(location) == "BACK")
            return;

        while(!it.isAtEnd()) {
            if (toUpper(it.retrieve().getPlace()) == toUpper(location)) {
                break;
            }
            it.advance();
        }

        if (it.isAtEnd()) {
            existing = false;
            cout<<"School does not exist!\n";
        }
    } while(!existing);

    schoolTree->remove(it.retrieve());

    string filePath, schoolFilePath, clients,teachers,classes,courses,trips,loans,materials,technicians;
    filePath = "..\\Schools\\"+ location+ "\\";
    clients=filePath+"clients.txt";
    teachers=filePath+"teachers.txt";
    classes=filePath+"classes.txt";
    courses=filePath+"courses.txt";
    trips=filePath+"trips.txt";
    loans=filePath+"loans.txt";
    materials=filePath+"materials.txt";
    technicians=filePath + "technicians.txt";
    schoolFilePath = "..\\Schools\\" + location + "\\" + location + "School.txt";
    if(!remove(schoolFilePath.c_str()) && !remove(clients.c_str()) && !remove(teachers.c_str()) && !remove(classes.c_str()) && !remove(courses.c_str()) && !remove(trips.c_str()) && !remove(loans.c_str()) && !remove(materials.c_str()) && !remove(technicians.c_str())){
        cout<<"Removed txt files!\n";
    }
    else{
        cout<<"Couldn't remove files\n";
    }
    filePath = "..\\Schools\\"+ location+ "\\";
    if(!rmdir(filePath.c_str())){
        cout<<"Removed School!\n";
    }
    else{
        cout<<"Couldn't remove directory\n";
    }

}

/*
int School::TeacherHash::operator()(const Teacher *t1, const Teacher *t2) const {
    return t1->getId() == t2->getId();
}*/

Material * School::repairMaterial() {
    srand(time(NULL));

    Material * m = materials[(rand() % materials.size())];
    vector<Technician *> copy;
    Technician * t;
    bool found=false;
    while(!technicians.empty() && !found){
        t = technicians.top();
        copy.push_back(t);
        for(auto x:t->getMaterialsRepaired()){
            if(x.first->getID()==m->getID() && x.second>2){
                x.second++;
                found=true;
                break;
            }
        }
        technicians.pop();
    }
    for(auto x:copy){
        technicians.push(x);
    }
    if(!found){
        t=technicians.top();
        cout<<"There are no technicians with enough experience to repair: "<<m->getType()<<"\nWill assign to first technician ("<<t->getName()<<")\n";
    }
    else{
        cout<<"Technician "<<t->getName()<<" has been assigned to repair: "<<m->getType()<<endl;
    }
    t->repairMaterial(m);

    return m;
}

string School::getDirector() const {
    return this->directorName;
}

unsigned int School::getNumClients() const {
    return this->numClients;
}

vector<Teacher *> School::getHiredTeachers() const {
    vector<Teacher *> temp;

    for (auto x : schoolTeachers) {
        if (x->getHired())
            temp.push_back(x);
    }

    return temp;
}

vector<Teacher *> School::getFiredTeachers() const {
    vector<Teacher *> temp;

    for (auto x : schoolTeachers) {
        if (!x->getHired())
            temp.push_back(x);
    }

    return temp;
}

priority_queue<Technician *> School::getTechnicians() const {
    return this->technicians;
}

void School::setTechnicians(priority_queue<Technician *> technicians) {
    this->technicians=technicians;

}

void School::addTechnician(Technician *technician) {
    this->technicians.push(technician);
}

void School::PrintPastTeachers() {
    vector<Teacher *> temp=getFiredTeachers();
    if(temp.empty()){
        cout<<"No previously hired teachers!\n";
        return;
    }
    for(auto x:temp){
        cout<<(*x);
    }
}

vector<Material *> School::getExistingMaterials() const {
    vector<Material *> temp;

    for(auto x:schoolMaterials){
        if(x->getExisting()){
            temp.push_back(x);
        }
    }
    return temp;
}

vector<Material *> School::getPastMaterials() const {
    vector<Material *> temp;

    for(auto x:schoolMaterials){
        if(!x->getExisting()){
            temp.push_back(x);
        }
    }
    return temp;
}

void writeSchoolsFile(BST<School> * schools) {
    ofstream schools_file;

    schools_file.open("..\\schools.txt");

    BSTItrIn<School> it(*schools);

    while (!it.isAtEnd()) {
        schools_file << it.retrieve().getPlace() << ";" << it.retrieve().getDirector() << ";" << to_string(it.retrieve().getNumClients());
        it.advance();
        if (!it.isAtEnd())
            schools_file << endl;
    }
}

/*--------CREATE AND MODIFY CLIENT FUNCTIONS---------*/

void CreateClient(School * school){
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
    c->setExpenses(0.0);
    school->addClient(c);

}

void ModifyClient(School * school){
    Client *c;
    vector<Client *> vec = school->getClients();
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

void RemoveClient(School * school){
    Client *c;
    vector<Client *> vec = school->getClients();
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Client" << endl;
    cout << "__________________________________________________\n" << endl;

    bool read = false;

    do {
        try {
            c = RemovePerson(vec);
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

/*--------CREATE AND MODIFY TEACHER FUNCTIONS---------*/

void CreateTeacher(School * school){
    Teacher *t = new Teacher();

    vector<Teacher*> temp = school->getFiredTeachers();

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Create New Teacher" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Previously Employed Teachers" << endl;
    cout << "__________________________________________________\n" << endl;
    if (temp.size() == 0)
        cout << "The school has 0 fired teachers.\n";
    for(int x=0;x<temp.size();x++){
        cout<<x+1<<" - "<<temp[x]->getName()<<endl;
    }
    cout << temp.size() + 1 << " - Create New" << endl;
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;

    int n = ieMenu(temp.size() + 1);
    /*
    do{
        n=readNumber("Please choose a teacher\n");
        if(n<0 || n>(temp.size()-1)){
            cout<<"Invalid option!\nPlease try again\n";
        }
    }while(n<0 || n>(temp.size()-1));
     */
    if (n == 0)
        return;

    if (n == temp.size() + 1){
        CreatePerson(t);

        string id;
        id= (char)toupper(t->getName()[0]);
        for (int i = 1; i < t->getName().length() - 1; i++){
            if (t->getName()[i] == ' ')
                id+=(char)toupper(t->getName()[i + 1]);
        }

        t->setId(id);
        school->addTeacher(t);
    }
    else{
        temp[n-1]->setHired(true);
    }

    //addN(vec,t);
}

void ModifyTeacher(School * school){
    Teacher *t;
    vector<Teacher *> vec = school->getHiredTeachers();
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

void RemoveTeacher(School * school){
    Teacher *t;
    vector<Teacher *> vec = school->getHiredTeachers();
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Teacher" << endl;
    cout << "__________________________________________________\n" << endl;

    bool read = false;

    do {
        try {
            t = RemovePerson(vec);
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

    //removeN(vec,t);
    t->setHired(false);


}

/*--------CREATE AND MODIFY TECHNICIAN FUNCTIONS---------*/

void CreateTechnician(School * school) {
    Technician *t = new Technician();

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Create New Technician" << endl;
    cout << "__________________________________________________\n" << endl;

    CreatePerson(t);
    vector<Material *> available = school->getMaterials();
    vector<Material *> choose;
    map<Material*, int> materials;

    SHOWMATERIALS:
    cout << setw(23) << right << "Choose the materials already repaired and the amount:" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Materials" << endl;
    cout << "__________________________________________________\n" << endl;

    for (int i = 0; i < available.size(); i++){
        cout << i+1 << " - " << available[i]->getType() << endl;
    }
    int i=available.size();

    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;

    cout << "Your List = [";
    for (int x = 0; x < choose.size(); x++)
        cout << choose[x]->getType() << ", ";
    cout << " ]" << endl;
    cout << "__________________________________________________\n" << endl;
    int id = ieMenu(i);
    if (id == 0 || id > i){
        t->setMaterialsRepaired(materials);
        school->addTechnician(t);
        cout<<school->getTechnicians().size();
        return;
    }

    int amount =readNumber("Number of times the technician has repaired this material:\n");
    choose.push_back(available[id-1]);
    materials.insert(pair<Material*,int>(available[id-1],amount));

    goto SHOWMATERIALS;

}

void ModifyTechnician(School * school){
    Technician *t;
    priority_queue<Technician *> temp = school->getTechnicians();
    vector<Technician *> vec;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Modify Technician" << endl;
    cout << "__________________________________________________\n" << endl;

    while(!temp.empty()){
        vec.push_back(temp.top());
        temp.pop();
    }

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

    vector<Material *> available = school->getMaterials();
    vector<Material *> choose;
    map<Material*, int> materials;

    SHOWMATERIALS:
    cout << setw(23) << right << "Choose the materials already repaired and the amount:" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Materials" << endl;
    cout << "__________________________________________________\n" << endl;

    for (int i = 0; i < available.size(); i++){
        cout << i+1 << " - " << available[i]->getType() << endl;
    }
    int i=available.size();

    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;

    int id = ieMenu(i); cout << "Your List = [";
    for (int x = 0; x < choose.size(); x++)
        cout << choose[x]->getType() << ", ";
    cout << " ]" << endl;
    cout << "__________________________________________________\n" << endl;

    if (id == 0 || id > i){
        t->setMaterialsRepaired(materials);
        for(auto x: vec){
            temp.push(x);
        }
        school->setTechnicians(temp);
        return;
    }

    int amount =readNumber("Number of times the technician has repaired this material:\n");
    choose.push_back(available[id-1]);
    materials.insert(pair<Material*,int>(available[id-1],amount));

    goto SHOWMATERIALS;

}

void RemoveTechnician(School * school){
    Technician *t;
    priority_queue<Technician *> temp = school->getTechnicians();
    vector<Technician *> vec;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Technician" << endl;
    cout << "__________________________________________________\n" << endl;

    bool read = false;

    do {
        try {
            t = RemovePerson(vec);
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

    for(auto x:vec){
        if(x->getNIF()!=t->getNIF()){
            temp.push(x);
        }
    }
    school->setTechnicians(temp);

}

/*--------CREATE AND MODIFY MATERIAL FUNCTIONS-----------*/

Material * searchMaterial(vector<Material *> &vec) {
    string search_type;
    bool found = false;

    search_type = readString("Type of material (\"back\" - Back): ");

    if (toUpper(search_type) == "BACK")
        return NULL;

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

    return (*it);
}

void CreateMaterial(School * school) {

    vector<Material *> temp=school->getPastMaterials();

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Create New Material" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Previously Owned Materials" << endl;
    cout << "__________________________________________________\n" << endl;
    if (temp.size() == 0)
        cout << "The school has 0 previous materials.\n";
    for(int x=0;x<temp.size();x++){
        cout<<x+1<<" - "<<temp[x]->getType()<<endl;
    }
    cout << temp.size() + 1 << " - Create New" << endl;
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;

    int n = ieMenu(temp.size() + 1);
    if (n == 0)
        return;

    if (n == temp.size() + 1){
        string type = readString("Type of Material: ");
        double price = readDouble("Price per 45 minutes: ");
        int amount = readNumber("Number of materials of this type: ");
        Material * m = new Material(type, price, amount, 0,true);
        school->addMaterial(m);
    }
    else{
        temp[n-1]->setExisting(true);
    }
}

void ModifyMaterial(School *school) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Modify Material" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "Can not change the price of the materials!" << endl;
    cout << "__________________________________________________\n" << endl;

    Material * p;
    vector<Material *> temp = school->getExistingMaterials();
    bool read = false;

    do {
        try {
            p = searchMaterial(temp);
            read = true;
        }
        catch (...) {
            cout << "Invalid Name. Try Again." << endl;
        }
    } while(!read);

    if (p == NULL) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }

    string type = readString("Type of Material: ");
    int totalAmount = readNumber("Number of materials of this type: ");
    int usedAmount = readNumber("Number of materials of this type being used: ");

    p->setType(type);
    p->setTotal(totalAmount);
    p->setUsed(usedAmount);
}

void RemoveMaterial(School *school) {
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Material" << endl;
    cout << "__________________________________________________\n" << endl;

    Material * p;
    vector<Material *> temp = school->getExistingMaterials();
    bool read = false;

    do {
        try {
            p = searchMaterial(temp);
            read = true;
        }
        catch (...) {
            cout << "Invalid Name. Try Again." << endl;
        }
    } while(!read);

    if (p == NULL) {
        cout << "__________________________________________________\n" << endl;
        cout << setw(23) << right << "Operation Canceled" << endl;
        cout << "__________________________________________________\n" << endl;
        return;
    }

    p->setExisting(false);
}

/*--------CREATE AND MODIFY ACTIVITY FUNCTIONS-----------*/

void CreateActivity(School * school) {
    /* ESCOLHER TIPO DE ATIVIDADE */
    int op;
    vector<Classes *> classes=school->getClasses();
    vector<Course *> courses=school->getCourses();
    vector<Trip *> trips=school->getTrips();
    vector<Loan *> loans=school->getLoans();
    vector<Material *> materials=school->getExistingMaterials();
    CHOOSEACTIVITY:

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Create New Activity" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Type of Activity" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Class\n";
    cout << "2 - Course\n";
    cout << "3 - Trip\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    op = ieMenu(3);
    if (op == 0) {return;}

    /* NOME, DIA E HORA DA ATIVIDADE */
    string name = readString("Name: ");
    double price = readDouble("Price: ");

    /* TIPO DE ATIVIDADE */
    //Classes
    Classes * newclass;
    Time time;
    string doubleC; bool doubleClass;
    string day;
    vector<Material *> choose_mat;
    //Courses
    Course * newcourse;
    vector<Classes *> choose;
    int numWeeks;
    //Trip
    Trip * newtrip;
    Date beginDate, endDate;
    string location;
    int maxAttendees;

    switch(op) {
        case 1: //CLASS

            time = readTime();
            do {
                day = readStringNoSpecial("Day (mon/tue/wed/thu/fri): ");
                if (toUpper(day)!="MON" && toUpper(day)!="TUE" && toUpper(day)!="WED" && toUpper(day)!="THU" && toUpper(day)!="FRI")
                    cout << "The school is not open on the weekends" << endl;
            } while (toUpper(day)!="MON" && toUpper(day)!="TUE" && toUpper(day)!="WED" && toUpper(day)!="THU" && toUpper(day)!="FRI");

            do{
                doubleC= readStringNoSpecial("Double class (yes or no): ");
                if (doubleC!="yes"&&doubleC!="no")
                    cout<<"Invalid Input! Try again.";
            }while (doubleC!="yes"&&doubleC!="no");

            if (doubleC == "yes")
                doubleClass = true;
            else
                doubleClass = false;

            choose_mat=chooseMaterials(classes,materials,time,day, loans, 0, courses);
            newclass = new Classes(name, time, toUpper(day), doubleClass, price,choose_mat);
            //classes.push_back(newclass);
            school->addClass(newclass);
            break;
        case 2: //COURSE
            choose = chooseClasses(classes);
            numWeeks = readNumber("Number of weeks: ");
            newcourse = new Course(name, price, choose, numWeeks);
            //courses.push_back(newcourse);
            school->addCourse(newcourse);
            break;
        case 3: //TRIP
            location = readStringNoSpecial("Location: ");
            beginDate = readDate();
            endDate = readDate();
            maxAttendees = readNumber("Available spots: ");
            newtrip = new Trip(name, location, beginDate, endDate, price, maxAttendees);
            //trips.push_back(newtrip);
            school->addTrip(newtrip);
            break;
        default:
            break;
    }
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Activity Created" << endl;
    cout << "__________________________________________________\n" << endl;
}

void ModifyActivity(School * school){
    vector<Classes *> classes=school->getClasses();
    vector<Course *> courses=school->getCourses();
    vector<Trip *> trips=school->getTrips();
    vector<Loan *> loans=school->getLoans();
    vector<Material *> materials=school->getExistingMaterials();

    typename vector<Classes *> ::const_iterator it=classes.begin();
    typename vector<Course *> ::const_iterator it_3 = courses.begin();
    typename vector<Trip *> ::const_iterator it_2=trips.begin();

    vector<Material *> choose_mat;
    string doubleC,day;
    Time time;
    vector<Classes *> choose;

    int op;

    CHOOSEACTIVITY:

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Modify Activity" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Type of Activity" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Class\n";
    cout << "2 - Course\n";
    cout << "3 - Trip\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    op = ieMenu(3);
    if (op == 0) {return;}


    bool read = false;

    switch(op) {
        case 1: //CLASS

            cout<<"\nClasses Available:\n";
            while(it!=classes.end()){
                if((*it)->getAnnual()==false){
                    cout<<(*it)->getActivity();
                }
                it++;
            }

            Classes *a;

            do {
                try {
                    a = FindActivity(classes);
                    read = true;
                }
                catch (...) {
                    cout << "Invalid Name. Try Again." << endl;
                }
            } while(!read);

            if (a == NULL) {
                goto CHOOSEACTIVITY;
            }

            time = readTime();
            (*a).setTime(time);
            do {
                day = readStringNoSpecial("Day (mon/tue/wed/thu/fri): ");
                if (toUpper(day)!="MON" && toUpper(day)!="TUE" && toUpper(day)!="WED" && toUpper(day)!="THU" && toUpper(day)!="FRI")
                    cout << "The school is not open on the weekends" << endl;
            } while (toUpper(day)!="MON" && toUpper(day)!="TUE" && toUpper(day)!="WED" && toUpper(day)!="THU" && toUpper(day)!="FRI");

            (*a).setDay(toUpper(day));

            do{
                doubleC= readStringNoSpecial("Double class (yes or no): ");
                if (doubleC!="yes"&&doubleC!="no")
                    cout<<"Invalid Input! Try again.";
            }while (doubleC!="yes"&&doubleC!="no");

            if (doubleC == "yes")
                (*a).setDoubleClass(true);
            else
                (*a).setDoubleClass(false);

            choose_mat=chooseMaterials(classes,materials,time,day, loans, 0, courses);
            (*a).setMaterial(choose_mat);

            break;
        case 2: //COURSE

            cout<<"\nCourses Available:\n";
            while(it_3!=courses.end()){
                cout<<(*it_3)->getActivity();
                it_3++;
            }

            Course *c;
            do {
                try {
                    c = FindActivity(courses);
                    read = true;
                }
                catch (...) {
                    cout << "Invalid Name. Try Again." << endl;
                }
            } while(!read);

            if (c == NULL) {
                goto CHOOSEACTIVITY;
            }

            choose = chooseClasses(classes);
            (*c).setClasses(choose);
            (*c).setNumWeeks(readNumber("Number of weeks: ")) ;
            break;
        case 3: //TRIP


            cout<<"\nTrips Available:\n";
            while(it_2!=trips.end()){
                cout<<(*it_2)->getActivity();
                it_2++;
            }

            Trip *t;

            do {
                try {
                    t = FindActivity(trips);
                    read = true;
                }
                catch (...) {
                    cout << "Invalid Name. Try Again." << endl;
                }
            } while(!read);

            if (t == NULL) {
                goto CHOOSEACTIVITY;
            }

            (*t).setLocation(readStringNoSpecial("Location: "));
            (*t).setBeginDate(readDate());
            (*t).setEndDate(readDate());
            (*t).setMaxAttendees(readNumber("Available spots: "));
            break;
        default:
            break;
    }
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Activity Modified" << endl;
    cout << "__________________________________________________\n" << endl;

}

void RemoveActivity(School * school){
    vector<Classes *> classes=school->getClasses();
    vector<Course *> courses=school->getCourses();
    vector<Trip *> trips=school->getTrips();
    vector<Loan *> loans=school->getLoans();
    vector<Material *> materials=school->getExistingMaterials();

    typename vector<Classes *> ::const_iterator it=classes.begin();
    typename vector<Course *> ::const_iterator it_3 = courses.begin();
    typename vector<Trip *> ::const_iterator it_2=trips.begin();

    vector<Material *> choose_mat;
    string doubleC,day;
    Time time;
    vector<Classes *> choose;

    int op;

    CHOOSEACTIVITY:

    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Remove Activity" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Type of Activity" << endl;
    cout << "__________________________________________________\n" << endl;
    cout << "1 - Class\n";
    cout << "2 - Course\n";
    cout << "3 - Trip\n";
    cout << "\n0 - Exit\n";
    cout << "__________________________________________________\n" << endl;
    op = ieMenu(3);
    if (op == 0) {return;}

    bool read = false;

    switch(op) {
        case 1: //CLASS

            cout<<"\nClasses Available:\n";
            while(it!=classes.end()){
                if((*it)->getAnnual()==false){
                    cout<<(*it)->getActivity();
                }
                it++;
            }

            Classes *a;

            do {
                try {
                    a = FindActivity(classes);
                    read = true;
                }
                catch (...) {
                    cout << "Invalid Name. Try Again." << endl;
                }
            } while(!read);

            if (a == NULL) {
                goto CHOOSEACTIVITY;
            }

            removeN(classes,a);
            break;
        case 2: //COURSE

            cout<<"\nCourses Available:\n";
            while(it_3!=courses.end()){
                cout<<(*it_3)->getActivity();
                it_3++;
            }

            Course *c;

            do {
                try {
                    c = FindActivity(courses);
                    read = true;
                }
                catch (...) {
                    cout << "Invalid Name. Try Again." << endl;
                }
            } while(!read);

            if (c == NULL) {
                goto CHOOSEACTIVITY;
            }

            removeN(courses,c);
            break;
        case 3: //TRIP
            cout<<"\nTrips Available:\n";
            while(it_2!=trips.end()){
                cout<<(*it_2)->getActivity();
                it_2++;
            }

            Trip *t;

            do {
                try {
                    t = FindActivity(trips);
                    read = true;
                }
                catch (...) {
                    cout << "Invalid Name. Try Again." << endl;
                }
            } while(!read);

            if (t == NULL) {
                goto CHOOSEACTIVITY;
            }

            removeN(trips,t);
            break;
        default:
            break;
    }
    cout << "__________________________________________________\n" << endl;
    cout << setw(23) << right << "Activity Remove" << endl;
    cout << "__________________________________________________\n" << endl;

}
