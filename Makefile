CXX = g++
CXXFLAGS = -g -Wall

run:
	./prog
clean:
	rm -f *.o prog

Time.o: Time.cpp Time.h
	$(CXX) $(CXXFLAGS) -c Time.cpp -o Time.o

BusRecord.o: BusRecord.cpp BusRecord.h
	$(CXX) $(CXXFLAGS) -c BusRecord.cpp -o BusRecord.o

prog: main.cpp BusRecord.o Time.o
	$(CXX) $(CXXFLAGS) main.cpp Time.o BusRecord.o -o prog