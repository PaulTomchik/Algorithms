runAllTests: testhashing testopenAddressing

runAllTestsWithStats: testhashing_wStats testopenAddressing_wStats



compile_hashFunctions:
	@gcc -Wall -g -c ../HashFunctions/hashFunctions.c 

compile_hashing_tests: compile_hashFunctions
	@gcc -Wall -g -I../HashFunctions hashFunctions.o hashTests.c -o testhashing

compile_hashing_tests_wStats: compile_hashFunctions
	@gcc -Wall -DOUTPUT_STATS -g -I..HashFunctions hashFunctions.o hashTests.c -o testhashing



compile_openAddressingOperations: compile_hashFunctions
	@gcc -Wall -g -c -I../HashFunctions ../OpenAddressing/openAddressingOperations.c 

compile_openAddressing_tests: compile_hashFunctions compile_openAddressingOperations
	@gcc -Wall -g -I../HashFunctions -I../OpenAddressing hashFunctions.o openAddressingOperations.o openAddressingTests.c -o testopenAddressing

compile_openAddressing_tests_wStats: compile_openAddressingOperations
	@gcc -Wall -DOUTPUT_STATS -g -I../OpenAddressing hashFunctions.o openAddressingOperations.o openAddressingTests.c -o testopenAddressing



testhashing: compile_hashing_tests
	@./testhashing

testhashing_wStats: compile_hashing_tests_wStats
	@./testhashing



testopenAddressing: compile_openAddressing_tests
	@./testopenAddressing

testopenAddressing_wStats: compile_openAddressing_tests_wStats
	@./testopenAddressing


clean:
	@rm -f *.o testhashing  testopenAddressing

