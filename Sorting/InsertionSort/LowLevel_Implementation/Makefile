all:
	gcc -Wall -g -pedantic -c arm_insertionSort.S
	gcc -Wall -g -pedantic -c c_insertionSort.c 
	gcc -Wall -g -pedantic -c insertionSortTests.c 
	gcc -Wall -g -pedantic arm_insertionSort.o c_insertionSort.o insertionSortTests.o -o tests

runTests: all
	./tests

clean:
	@rm -f *.o

clobber: clean
	@rm -f tests

