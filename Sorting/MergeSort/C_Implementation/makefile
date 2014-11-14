all:
	gcc -Wall -Werror -g -pedantic -c c_mergesort.c 
	gcc -Wall -Werror -g -pedantic -c mergesort_tests.c 
	gcc -Wall -Werror -g -pedantic c_mergesort.o mergesort_tests.o -o tests 

clean:
	rm -f *.o

clobber: clean
	rm -f tests

memcheck:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./tests

format:
	find . -regex '.*\.[c h]' -exec sed -i 's/\t/  /g' {} \;
