#include "Date.h"
#include "Utils.h"

Date::Date() {
    year = 0;
    month = 0;
    day = 0;
}

Date::Date(string date) {
    int counter = 0;
    string num;

    for (int i = 0; i < date.length(); i++)
    {
        if (isdigit(date[i]))
        {
            num += date[i];
        }
        else
        {
            if (counter == 0)
                this->day = stoi(num);
            else if (counter == 1)
                this->month = stoi(num);
            counter++;
            num = "";
            continue;
        }
    }
    this->year = stoi(num);
}

Date::Date(int year, int month, int day) {
    year = year;
    month = month;
    day = day;
}

bool Date::validDate() const {
    if (year < 1900 || year > 2100) {return false;}
    else if (month < 1 || month > 12) {return false;}
    else if (day < 1 || day > 31) {return false;}
    else if (month == 2 && ((leapYear(year) && day > 29) || (!leapYear(year) && day > 28))) {return false;}
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {return false;}
    return true;
}

string Date::getDate() const {
    string info = "";
    if (day < 10)
        info += "0" + to_string(day) + "-";
    else
        info += to_string(day) + "-";

    if (month < 10)
        info += "0" + to_string(month) + "-";
    else
        info += to_string(month) + "-";

    info += to_string(year);
    return info;
}

int Date::getDay() const {
    return this->day;
}

int Date::getMonth() const {
    return this->month;
}

int Date::getYear() const {
    return this->year;
}

void Date::setYear(int year) {
    this->year = year;
}

void Date::setMonth(int month) {
    this->month = month;
}

void Date::setDay(int day) {
    this->day = day;
}

