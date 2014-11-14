all:
	gcc -Wall -Werror -g -pedantic -c maxsubarray_NLgN.c 
	gcc -Wall -Werror -g -pedantic -c maxsubarray_Linear.c 
	gcc -Wall -Werror -g -pedantic -c maxsubarray_tests.c 
	gcc -Wall -Werror -g -pedantic maxsubarray_NLgN.o maxsubarray_Linear.o maxsubarray_tests.o -o tests

clean:
	@rm -f *.o

clobber: clean
	@rm -f tests

memcheck:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes  ./tests

format:
	@find . -regex '.*\.[c h]' -exec sed -i 's/\t/  /g' {} \;
