#include "RecordsController.h"

inline bool SortRecordsByName::operator() (const BusRecord& rec1, const BusRecord& rec2)
{
    return (rec1.GetCompanyTitle() > rec2.GetCompanyTitle());
}

inline bool SortRecordsByDepartureTime::operator() (const BusRecord& rec1, const BusRecord& rec2)
{
    return (rec1.GetDepartureTime() < rec2.GetDepartureTime());
}

bool MatchString::operator()(const BusRecord& rec) const
{
    return rec.GetCompanyTitle() == str;
}

void RecordsController::LoadEfficientRecords() {
    // adding first record
    BusRecord newRecord;
    ist >> newRecord;
    allRecords.push_back(newRecord);

    while(ist >> newRecord) {
            // this cycle is for knowing, whether we need to add next record from file or not to resulting vector
        bool coupledRecordsFlag = false;

        // if trip is greather than 1 hour just skip it and continue reading new records
        Time duration = newRecord.GetTripDuration();
        if (duration > Time("01", "00"))
            continue;

        // if records are "coupled", we need to compare wich is better and do appropriate action
        for (auto& currRecord : allRecords) {
            if (AreCoupledRecords(newRecord, currRecord)) {
                coupledRecordsFlag = true;

                if (AreSameRecordsAccordingTime(newRecord, currRecord)) {
                    if (newRecord.GetCompanyTitle()=="Posh" && currRecord.GetCompanyTitle()=="Grotty")
                        currRecord=newRecord;
                    break;
                }
                else if (IsFirstRecordBetterThanSecond(newRecord, currRecord))
                    currRecord=newRecord;

                break;
            }
        }

        // if we are here - there wasn't any coupled record and it's unique, so we just push it to our vector
        if (!coupledRecordsFlag) {
            allRecords.push_back(newRecord);
        }
    }
}

void RecordsController::PrintInFormat(const std::string& streamName) {
        std::ofstream ost{streamName};

        // first we sort all records by name
        std::sort(allRecords.begin(), allRecords.end(), SortRecordsByName());

        // then we sort 2 different parts: all Posh records and all Grotty records
        auto firstGrottyIt = std::find_if(allRecords.begin(), allRecords.end(), MatchString("Grotty"));

        std::sort(allRecords.begin(), firstGrottyIt, SortRecordsByDepartureTime());
        std::sort(firstGrottyIt, allRecords.end(), SortRecordsByDepartureTime());

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

        ost.close();
    }