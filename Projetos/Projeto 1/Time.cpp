#include "Time.h"

Time::Time() {
    hour=0;
    minute=0;
}

Time::Time(string time) {
    int counter = 0;
    string num;

    this->hour = stoi(time.substr(0,2));
    this->minute = stoi(time.substr(3,2));
}

Time::Time(int hour, int minute) {
    this->hour=hour;
    this->minute=minute;
}

bool Time::validTime() const {
    if (hour < 0 || hour > 23) {return false;}
    else if (minute < 0 || minute > 59) {return false;}
    return true;
}

string Time::getTime() const {
    string info;
    if (hour < 10)
        info = "0" + to_string(hour) + ":";
    else
        info = to_string(hour) + ":";
    if (minute < 10)
        info += "0" + to_string(minute);
    else
        info += to_string(minute);
    return info;
}

int Time::getHour() const {
    return this->hour;
}

int Time::getMinute() const {
    return this->minute;
}

void Time::setHour(int hr) {
    this->hour = hr;
}

void Time::setMinutes(int min) {
    this->minute = min;
}

Time Time::operator+(Time const &t2) {
    Time sum;
    sum.minute = (this->minute + t2.minute) % 60;
    if (this->minute + t2.minute >= 60)
        sum.hour = (this->hour + t2.hour + 1) % 24;
    else
        sum.hour = (this->hour + t2.hour) % 24;
    return sum;
}

Time Time::operator-(Time const &t2) {
    Time sub;
    if(t2.minute > this->minute) {
        this->hour -= 1;
        this->minute += 60;
    }
    sub.minute = this->minute-t2.minute;
    sub.hour = this->hour - t2.hour;
    return sub;
}

bool Time::operator<(Time const &t2) {
    if (this->hour < t2.hour)
        return true;
    else if (this->hour > t2.hour)
        return false;
    else
        return this->minute < t2.minute;
}

