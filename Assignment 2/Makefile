all: sort

sort: main.o sort.o
	g++ -o sort main.o sort.o

main.o: main.cpp sort.h
	g++ -c main.cpp

sort.o: sort.cpp
	g++ -c sort.cpp

clean:
	rm -f *.o sort

