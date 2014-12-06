runAllTests: runHashingTests runProbingTests
runAllTestsWithStats: runHashingTestsWithStats runProbingTestsWithStats

runHashingTests: compile_hashFunctions compile_hashing_tests 
runHashingTestsWithStats: compile_hashFunctions compile_hashing_tests_with_stats 

runProbingTests: compile_hashFunctions compile_probingFunctions compile_probing_tests 


compile_hashFunctions:
	@gcc -Wall -g -O3 -c hashFunctions.c 

compile_probingFunctions:
	@gcc -Wall -g -O3 -c probingFunctions.c 



compile_hashing_tests:
	@gcc -Wall -g hashFunctions.o hashingtests.c -o hashingtests
	@./hashingtests

compile_hashing_tests_with_stats:
	@gcc -Wall -DOUTPUT_STATS -g hashFunctions.o hashingtests.c -o hashingtests
	@./tests



compile_probing_tests:
	@gcc -Wall -g hashFunctions.o probingFunctions.o probingtests.c -o probingtests
	@./tests



clean:
	@rm -f *.o hashingtests probingtests
