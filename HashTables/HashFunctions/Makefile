all: compile_hashFunctions compile_tests
	./tests

compile_hashFunctions:
	@gcc -Wall -g -O3 -c hashFunctions.c 

compile_tests:
	@gcc -Wall -g hashFunctions.o tests.c -o tests

clean:
	@rm -f output.txt *.o tests
