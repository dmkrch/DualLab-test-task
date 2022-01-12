#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Time.h"
#include "BusRecord.h"
#include "RecordsController.h"


int main(int argc, char** argv) {
    try {
        RecordsController recordsController(argv[1]);
        recordsController.LoadEfficientRecords();
        recordsController.PrintInFormat(argv[2]);
        
        return 0;
    }
    catch(...) {
        std::cerr << "some error" << std::endl;

        return 1;
    }
}