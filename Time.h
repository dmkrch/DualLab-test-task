#pragma once

#include <string>
#include <sstream>

class Time {
public:
    Time() {}
    Time(const std::string& hh, const std::string& mm) : hours{hh}, minutes{mm} {}

    std::string GetHours() const { return hours; }
    std::string GetMinutes() const { return minutes; }

    Time operator-(const Time& time2);

    const bool operator<(const Time &t) const;
    const bool operator>(const Time &t) const;
    const bool operator==(const Time& t) const;
    const bool operator>=(const Time& t) const;
    const bool operator<=(const Time& t) const;

private:
    std::string hours;
    std::string minutes;
};

std::istream& operator>>(std::istream& is, Time& time);