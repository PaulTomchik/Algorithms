all: compile_java compile_native

compile_java:
	javac RadixSorter.java RadixSortTest.java
	javah -jni RadixSorter

compile_native:
	gcc -Ofast "-I$(JAVA_HOME)/include" "-I$(JAVA_HOME)/include/linux" -z noexecstack -fPIC -o RadixSort.so -shared radixsort.s RadixSorter.c


clean:
	rm -f *.o *.class RadixSorter.h *.so

clobber: clean
	rm rsort

runit:
	java -Xmx1024M RadixSortTest
