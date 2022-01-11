#include "BusRecord.h"

std::istream& operator>>(std::istream& is, BusRecord& busRecord)
{
    std::string title;
    Time departureTime;
    Time arrivalTime;

    is >> title >> departureTime >> arrivalTime;
    busRecord = BusRecord(title, departureTime, arrivalTime);

    return is;
}

bool areCoupledRecords(BusRecord& rec1, BusRecord& rec2) {
    // coupled records means that arrival time and departure time of rec1 are totally included into
    // departure time and arrival time of rec2
    return (((rec1.GetDepartureTime() >= rec2.GetDepartureTime()) && (rec1.GetArrivalTime() <= rec2.GetArrivalTime())) ||
            ((rec1.GetDepartureTime() <= rec2.GetDepartureTime()) && (rec1.GetArrivalTime() >= rec2.GetArrivalTime())));
}

bool isFirstRecordBetterThanSecond(BusRecord& rec1, BusRecord& rec2) {
    return rec1.GetDepartureTime() >= rec2.GetDepartureTime() && rec1.GetArrivalTime() <= rec2.GetArrivalTime();
}

bool areSameRecordsAccordingTime(BusRecord& rec1, BusRecord& rec2) {
    return ((rec1.GetArrivalTime()==rec2.GetArrivalTime()) && (rec1.GetDepartureTime()==rec2.GetDepartureTime()));
}