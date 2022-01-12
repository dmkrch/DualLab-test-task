----------------HOW TO USE-------------------
There is a Makefile, so executable file can be done with such commands:
1. make prog
2. ./prog arg1 arg2             where arg1 - name of input file, arg2 - name of output file

e.g. ./prog input.txt output.txt

----------DESCRIPTION OF CLASSES--------------
there are 3 main classes: 
1. Time
    class for storing time in std::string format HH:MM. Contains different overload functions to make class flexible in use
    There is >> operator overload, so information can be easily putted from any stream in determined format
2. BusRecord
    class that stores record in timetable. It contains such variables: departure time, arrival time, company title
    There is >> operator overload, so information can be easily putted from any stream in determined format. Moreovere, 
    function to use: 
        2.1. GetTripDuration - returns object of Time between arrival and departure times.
        2.2. AreCoupledRecords - returns true if trip's time is "in" another trip time
        2.3. IsFirstRecordBetterThanSecond - returns true if first argument(trip1) is better than second argument(trip2)
        2.4. AreSameRecordsAccordingTime - returns true if 2 records have same departure and arrival times
3. RecordsController
    class that stores readed records from stream, which is opened in constructor of that class.
    function to use:
        3.1. LoadEfficientRecords - reads records from stream and adding only those, that are efficient
        3.2. PrintInFormat - prints all records that are sorted in determined order and format to output stream