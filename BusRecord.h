#pragma once

#include "Time.h"

class BusRecord {
public:
    BusRecord() {}

    BusRecord(std::string tit, Time depT, Time arrT) : 
        companyTitle{tit}, departureTime{depT}, arrivalTime{arrT} {}

    std::string GetCompanyTitle() const { return companyTitle; }
    std::string GetDepartureHours() const { return departureTime.GetHours(); }
    std::string GetDepartureMinutes() const { return departureTime.GetMinutes(); }
    std::string GetArrivalHours() const { return arrivalTime.GetHours(); }
    std::string GetArrivalMinutes() const { return arrivalTime.GetMinutes(); }
    const Time& GetArrivalTime() const { return arrivalTime; }
    const Time& GetDepartureTime() const { return departureTime; }
    Time GetTripDuration() { return Time(arrivalTime) - Time(departureTime); }


private:
    Time departureTime;
    Time arrivalTime;
    std::string companyTitle;
};

std::istream& operator>>(std::istream& is, BusRecord& busRecord);

bool AreCoupledRecords(BusRecord& rec1, BusRecord& rec2);
bool IsFirstRecordBetterThanSecond(BusRecord& rec1, BusRecord& rec2);
bool AreSameRecordsAccordingTime(BusRecord& rec1, BusRecord& rec2);