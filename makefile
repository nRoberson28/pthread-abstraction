
output: main.o thread.h
	g++ main.o -o output

main.o: main.cpp thread.h
	g++ -c main.cpp thread.h

clean:
	rm *.o output