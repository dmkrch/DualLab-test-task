#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Time.h"
#include "BusRecord.h"

struct sort_records_by_name
{
    inline bool operator() (const BusRecord& rec1, const BusRecord& rec2)
    {
        return (rec1.GetCompanyTitle() > rec2.GetCompanyTitle());
    }
};

struct sort_records_by_departure_time
{
    inline bool operator() (const BusRecord& rec1, const BusRecord& rec2)
    {
        return (rec1.GetDepartureTime() < rec2.GetDepartureTime());
    }
};

struct MatchString
{
public:
    MatchString(const std::string& s) : str(s) {}
    bool operator()(const BusRecord& rec) const
    {
        return rec.GetCompanyTitle() == str;
    }
private:
    const std::string& str;
};


int main(int argc, char** argv) {
    try {
        // opening input stream
        std::ifstream ist{argv[1]};

        BusRecord newRecord;
        std::vector<BusRecord> allRecords;

        // adding first record from input file to vector of allRecords
        ist >> newRecord;
        allRecords.push_back(newRecord);

        while(ist >> newRecord) {
             // this cycle is for knowing, whether we need to add next record from file or not to resulting vector
            bool coupledRecordsFlag = false;

            // here we check whether new record time trip is greather than 1 hour
            Time duration = newRecord.GetTripDuration();
            if (duration > Time("01", "00"))
                continue;

            for (auto& currRecord : allRecords) {
                if (areCoupledRecords(newRecord, currRecord)) {
                    coupledRecordsFlag = true;

                    // now if records are coupled, there 3 cases:
                    // 1. they are equal on time (name came differ)
                    // 2. new record is better than currRecord, so we change currRecord to newRecord
                    // 3. new record is worse than currRecord, so we do nothing, just break from cycle

                    // case 1:
                    if (areSameRecordsAccordingTime(newRecord, currRecord)) {
                        // we need to check, whether name of new Record is Posh, and currRecord name is Grotty
                        // if so, we change currRecord equal to newRecord
                        if (newRecord.GetCompanyTitle()=="Posh" && currRecord.GetCompanyTitle()=="Grotty")
                            currRecord=newRecord;

                        break;
                    }
                    // case 2:
                    else if (isFirstRecordBetterThanSecond(newRecord, currRecord))
                        currRecord=newRecord;

                    break;
                }
            }

            // if we are here - there wasn't any coupled record and it's unique, so we just push it to our vector
            if (!coupledRecordsFlag) {
                allRecords.push_back(newRecord);
            }
        }

        // first we sort all records by name
        std::sort(allRecords.begin(), allRecords.end(), sort_records_by_name());

        // then we sort 2 different parts: all Posh records and all Grotty records
        auto firstGrottyIt = std::find_if(allRecords.begin(), allRecords.end(), MatchString("Grotty"));

        std::sort(allRecords.begin(), firstGrottyIt, sort_records_by_departure_time());
        std::sort(firstGrottyIt, allRecords.end(), sort_records_by_departure_time());

        // opening output stream
        std::ofstream ost{argv[2]};

        for (auto it = allRecords.begin(); it != firstGrottyIt; it++) {
            auto rec = *it;

            ost << rec.GetCompanyTitle() << " " << rec.GetDepartureHours() << ":" << rec.GetDepartureMinutes() << 
            " " << rec.GetArrivalHours() << ":" << rec.GetArrivalMinutes() << std::endl;
        }
        
        ost << std::endl;

        for (auto it = firstGrottyIt; it != allRecords.end(); it++) {
            auto rec = *it;
            
            ost << rec.GetCompanyTitle() << " " << rec.GetDepartureHours() << ":" << rec.GetDepartureMinutes() << 
            " " << rec.GetArrivalHours() << ":" << rec.GetArrivalMinutes() << std::endl;
        }

        // closing 2 opened streams for reading and outputing
        ist.close();
        ost.close();
    }
    catch(...) {
        std::cerr << "some error" << std::endl;
    }
}