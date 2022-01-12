#include "Time.h"

Time Time::operator-(const Time& time2) {
    int mm1 = std::stoi(this->GetMinutes());
    int hh1 = std::stoi(this->GetHours());
    int mm2 = std::stoi(time2.GetMinutes());
    int hh2 = std::stoi(time2.GetHours());

    bool minusHour = false;

    int mmLeft = mm1-mm2;

    if (mmLeft < 0) {
        mmLeft += 60;
        minusHour = true;
    }

    int hhLeft = hh1-hh2;
    if (minusHour)
        --hhLeft;

    if (hhLeft < 0) {
        hhLeft += 24;
    }

    std::string hours_str = std::to_string(hhLeft);
    std::string minutes_str = std::to_string(mmLeft);

    if (hours_str.length()==1)
        hours_str.insert(0, "0");
    if (minutes_str.length()==1)
        minutes_str.insert(0, "0");

    hours = hours_str;
    minutes = minutes_str;

    return *this;
}

const bool Time::operator<(const Time &t) const {
    if (hours < t.GetHours())
        return true;
    else if (hours == t.GetHours() && std::stoi(minutes) < std::stoi(t.GetMinutes()))
        return true;
    return false;
}

const bool Time::operator>(const Time &t) const {
    if (hours > t.GetHours())
        return true;
    else if (hours == t.GetHours() && std::stoi(minutes) > std::stoi(t.GetMinutes()))
        return true;
    return false;
}

const bool Time::operator==(const Time& t) const {
    return hours==t.GetHours() && minutes==t.GetMinutes();
}

const bool Time::operator>=(const Time& t) const {
    return (*this > t || *this == t);
}

const bool Time::operator<=(const Time& t) const {
    return (*this < t || *this == t);
}

std::istream& operator>>(std::istream& is, Time& time)
{
    std::string str; 
    is >> str;

    std::stringstream ss(str);
    std::string hours;
    std::string minutes;
    char delim = ':';

    std::getline(ss, hours, delim);
    std::getline(ss, minutes, delim);
    time = Time(hours, minutes);

    return is;
}