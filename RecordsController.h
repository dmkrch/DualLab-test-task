#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "BusRecord.h"

struct SortRecordsByName
{
    inline bool operator() (const BusRecord& rec1, const BusRecord& rec2);
};

struct SortRecordsByDepartureTime
{
    inline bool operator() (const BusRecord& rec1, const BusRecord& rec2);
};

struct MatchString
{
public:
    MatchString(const std::string& s) : str(s) {}
    bool operator()(const BusRecord& rec) const;
private:
    const std::string& str;
};


class RecordsController {
public:
    RecordsController(const std::string fileName) : ist{fileName} { }
    ~RecordsController() { ist.close(); }

    void LoadEfficientRecords();
    void PrintInFormat(const std::string& streamName);

private:
    std::ifstream ist;
    std::vector<BusRecord> allRecords;
};