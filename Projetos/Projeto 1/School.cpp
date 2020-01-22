#include "School.h"

using namespace std;

School::School(istream &clients_file, istream &teachers_file, istream &classes_file, istream &courses_file, istream &trips_file, istream &material_file, istream &loans_file) {
    string material_name, amount, price, used;

    if (material_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto CLASSESFILE;

    while(!material_file.eof()){
        getline(material_file,material_name,';');
        getline(material_file,price,';');
        getline(material_file,amount, ';');
        getline(material_file,used);
        Material *new_material = new Material(material_name,stod(price),stoi(amount), stoi(used));
        materials.push_back(new_material);
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

    if (teachers_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        goto LOANSFILE;

    while(!teachers_file.eof()){
        getline(teachers_file,name_person,';');
        getline(teachers_file,gender,';');
        getline(teachers_file,nif,';');
        getline(teachers_file,birth_date,';');
        getline(teachers_file,address,';');
        getline(teachers_file,email,';');
        getline(teachers_file,phone);
        Teacher *new_teacher = new Teacher(name_person,gender,nif,Date(birth_date),Address(address),email,phone);
        teachers.push_back(new_teacher);
    }

    sortClassesByHour();
    AssignTeachers(classes,teachers);

    LOANSFILE:

    string idmaterial_need;

    if (loans_file.peek() == ifstream::traits_type::eof()) //check if the file is empty
        return;

    while(!loans_file.eof()) {
        getline(loans_file,day,';');
        getline(loans_file,time,';');
        getline(loans_file,materials_needed,';');
        stringstream mat(materials_needed);
        while(getline(mat, idmaterial_need, ',') )
            ids.push_back(stoi(idmaterial_need));
        for (int i = 0; i < ids.size(); i++)
            if (ids[i] < materials.size())
                materialsNeeded.push_back(materials[ids[i] - 1]);
            else
                materialsNeeded.push_back(new Material("Removed Material", 0, 0, 0));
        getline(loans_file,nif,';');
        getline(loans_file,price, ';');
        getline(loans_file, numWeeks);
        Loan * new_loan = new Loan("Rental",day, Time(time), materialsNeeded, stoi(nif), stod(price), stoi(numWeeks));
        loans.push_back(new_loan);
        ids.clear();
        materialsNeeded.clear();
    }

    AssignLoans();
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
    vector<Teacher*> ::const_iterator it=teachers.begin();
    while(it!=teachers.end()){
        cout<<(*(*it));
        it++;
    }
}

void School::PrintTeacher() {
    string search_init = readStringNoSpecial("Teacher's initials ('0' to Exit): ");

    typename vector<Teacher *> ::const_iterator it=teachers.begin();

    if (search_init == "0")
        return;

    search_init = toUpper(search_init);

    for(;it!=teachers.end();it++)
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


void School::addClient(Client *client) {
    this->clients.push_back(client);
}

void School::addTeacher(Teacher *teacher) {
    this->teachers.push_back(teacher);
}

void School::addActivity(Activity *activity) {
    this->activities.push_back(activity);
}

void School::addClass(Classes *classes) {
    this->classes.push_back(classes);
}

void School::addCourse(Course *course) {
    this->courses.push_back(course);
}

void School::addTrip(Trip *trip) {
    this->trips.push_back(trip);
}

void School::addMaterial(Material *material) {
    this->materials.push_back(material);
}

vector<Client *> School::getClients() const {
    return this->clients;
}

vector<Teacher *> School::getTeachers() const {
    return this->teachers;
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

School::~School() {

    ofstream clientsFile, teacherFile, classesFile, coursesFile, tripsFile, loansFile, materialsFile;

    //WRITE ON CLIENTS FILE
    clientsFile.open("..\\clients.txt");
    for (int i = 0; i < clients.size(); i++) {
        if (i != 0)
            clientsFile << endl;
        clientsFile << clients[i]->WriteToFile();
    }
    clientsFile.close();


    //WRITE TO TEACHERS FILE
    teacherFile.open("..\\teachers.txt");
    for (int i = 0; i < teachers.size(); i++) {
        if (i != 0)
            teacherFile << endl;
        teacherFile << teachers[i]->WriteToFile();
    }
    teacherFile.close();


    //WRITE TO CLASSES FILE
    classesFile.open("..\\Activities\\classes.txt");
    for (int i = 0; i < classes.size(); i++) {
        if (i != 0)
            classesFile << endl;
        classesFile << classes[i]->WriteToFile();
    }
    classesFile.close();


    //WRITE TO COURSES FILE
    coursesFile.open("..\\Activities\\courses.txt");
    for (int i = 0; i < courses.size(); i++) {
        if (i != 0)
            coursesFile << endl;
        coursesFile << courses[i]->WriteToFile();
    }
    coursesFile.close();


    //WRITE TO TRIPS FILE
    tripsFile.open("..\\Activities\\trips.txt");
    for (int i = 0; i < trips.size(); i++) {
        if (i != 0)
            tripsFile << endl;
        tripsFile << trips[i]->WriteToFile();
    }
    tripsFile.close();

    //WRITE TO LOANS FILE
    loansFile.open("..\\Activities\\loans.txt");
    for (int i = 0; i < loans.size(); i++) {
        if (i != 0)
            loansFile << endl;
        loansFile << loans[i]->WriteToFile();
    }
    loansFile.close();


    //WRITE TO MATERIALS FILE
    materialsFile.open("..\\materials.txt");
    for (int i = 0; i < materials.size(); i++) {
        if (i != 0)
            materialsFile << endl;
        materialsFile << materials[i]->WriteToFile();
    }
    materialsFile.close();
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




