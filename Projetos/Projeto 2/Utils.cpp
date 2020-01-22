#include "Utils.h"

using namespace std;

int readNumber(string msg) {
    string line;
    int num = 0;
    bool error = false;

    do
    {
        cout << msg;
        getline(cin, line);

        error = any_of(line.begin(), line.end(), ::isalpha); //Ver se tem alguma letra

        if (error)
            cout << "Invalid Input. Can not have letters." << endl;

        if (!error && line == "") {
            error = true;
            cout << "Empty Input. " << endl;
        }

        if (!error) {
            for (auto x : line) {
                if (isspace(x)) {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have spaces." << endl;
        }

        if (!error) {
            try {
                num = stoi(line);
            }
            catch (invalid_argument&) { //Ver se tem caracter especial
                error = true;
                cout << "Invalid Input. Can not have special characters." << endl;
            }
            catch (out_of_range&) { //Ver se o numero e demasiado grande
                error = true;
                cout << "Invalid Input. Number is to big." << endl;
            }
        }

        if (!error && line.size() != to_string(stoi(line)).size()) {
            for (auto x : line) {
                if (ispunct(x)) {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have special characters." << endl;
        }

    } while (error);

    num = stoi(line);
    return num;
}

double readDouble(string msg) {
    string line;
    double num = 0;
    bool error = false;

    do
    {
        cout << msg;
        getline(cin, line);

        error = any_of(line.begin(), line.end(), ::isalpha); //Ver se tem alguma letra

        if (error)
            cout << "Invalid Input. Can not have letters." << endl;

        if (!error && line == "") {
            error = true;
            cout << "Empty Input. " << endl;
        }

        if (!error) {
            for (auto x : line) {
                if (isspace(x)) {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have spaces." << endl;
        }

        if (!error) {
            try {
                num = stod(line);
            }
            catch (invalid_argument&) { //Ver se tem caracter especial
                error = true;
                cout << "Invalid Input. Can not have special characters." << endl;
            }
            catch (out_of_range&) { //Ver se o numero e demasiado grande
                error = true;
                cout << "Invalid Input. Number is to big." << endl;
            }
        }

        if (!error && line.size() != to_string(stod(line)).size()) {
            for (auto x : line) {
                if (ispunct(x) && x != '.') {
                    error = true;
                    break;
                }
            }
            if (error)
                cout << "Invalid Input. Can not have special characters 2." << endl;
        }

    } while (error);

    num = stod(line);
    return num;
}

string readString(string msg)
{
    string line;
    bool error = false;

    do {
        cout << msg;
        getline(cin, line);

        if(line=="0"){
            return line;
        }
        error = !(any_of(line.begin(), line.end(), ::isalpha)); //Verifica que tem pelo menos uma letra

        if (error)
            cout << "Invalid Input. It must contain at least one letter." << endl;

        if (!error)
            error = (line.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_.,/ @") != string::npos);

        if (error)
            cout << "Invalid Input. Can not have special characters." << endl;

    } while (error);

    return line;
}

string readStringNoSpecial(string msg)
{
    string line;
    bool error = false;

    do {
        cout << msg;
        getline(cin, line);

        if(line=="0"){
            return line;
        }

        error = !(any_of(line.begin(), line.end(), ::isalpha)); //Verifica que tem pelo menos uma letra

        if (error)
            cout << "Invalid Input. It must contain at least one letter." << endl;

        if (!error)
            error = (line.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -") != string::npos);

        if (error)
            cout << "Invalid Input. Can not have special characters." << endl;

    } while (error);

    return line;
}

Date readDate() {
    Date newdate;

    do {
        newdate.setYear(readNumber("- Year: "));
        newdate.setMonth(readNumber("- Month: "));
        newdate.setDay(readNumber("- Day: "));
        if (!newdate.validDate())
            cout << "Invalid Date. Try Again." << endl;
    } while (!newdate.validDate());

    return newdate;
}

Time readTime() {
    Time newtime;

    do {
        newtime.setHour(readNumber("- Hour: "));
        newtime.setMinutes(readNumber("- Minutes: "));
        if (!newtime.validTime())
            cout << "Invalid Time. Try Again." << endl;
    } while (!newtime.validTime());

    return newtime;
}

string readPostalCode(string msg)
{
    string line;
    bool error;

    do {
        error = false;
        cout << msg;
        getline(cin, line);

        if (line.length() !=8) {error = true;}
        else if ((!all_of(line.begin(), line.end() - 4, ::isdigit)) || (!all_of(line.begin() + 5, line.end(), ::isdigit)) || line[4] != '-' ){error= true;}

        if (error){
            cout << "Invalid Input. Postal code is not correct." << endl;
        }

    } while (error);

    return line;
}

Address readAddress(){
    Address newaddress;
    string door, floor;

    do{
        newaddress.setStreet(readStringNoSpecial("- Street: "));
        do {
            door = to_string(readNumber("- Door: "));
            if (stoi(door) <= 0)
                cout << "Invalid Input. Door number must be higher than 0." << endl;
        } while (stoi(door) <= 0);
        newaddress.setDoor(door);
        do {
           floor = to_string(readNumber("- Floor: "));
            if (stoi(floor) < 0)
                cout << "Invalid Input. Floor number must be 0 or higher." << endl;
        } while (stoi(floor) < 0);
        newaddress.setFloor(floor);
        newaddress.setPostalCode(readPostalCode("- Postal Code: "));
        newaddress.setLocation(readStringNoSpecial("- Location: "));
        if(!newaddress.validAddress()){
            cout<<"Invalid Address. Try Again."<<endl;
        }
    }while(!newaddress.validAddress());

    return newaddress;
}

string readEmail() {
    // define a regular expression
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

    bool error;
    string email;

    do {
        error = false;

        cout << "Email: ";
        getline(cin, email);

        error = !regex_match(email, pattern);

        if (error)
            cout << "Invalid Input. Email format is incorrect." << endl;
    } while (error);

    return email;
}

int ieMenu(int maxOption) {
    int op;

    do {
        op = readNumber("Choose an option (number): ");
        if (op > maxOption || op < 0)
            cout << "Invalid Input. Invalid option." << endl;
    } while(op > maxOption || op < 0);

    return op;
}

bool leapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

int findAge(Date birthDate)
{
    time_t t = time(0);
    tm* now = localtime(&t);
    int current_day = now->tm_mday;
    int current_month = now->tm_mon + 1;
    int current_year = now->tm_year + 1900;

    if (birthDate.getDay() > current_day)
        current_month--;

    if (birthDate.getMonth() > current_month)
        current_year--;

    return current_year - birthDate.getYear();
}

string toUpper(string msg) {
    for (int i = 0; i < msg.size(); i++) {
        if (msg[i] >= 'a' && msg[i] <= 'z')
            msg[i] += ('A' - 'a');
    }
    return msg;
}

