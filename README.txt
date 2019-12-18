This contains a list of instructions on how to build the programs used in our final project

1. Compile the library.h file - it contains our class definition
2. To compile any of the main programs to test the output, compile the main program, then run the .bin file. The list of which files correspond to which question is found below; intended to use a build file
3. I would sugggest not running the mainDataOutput.cpp file, as it takes a while to complete and only outputs data used to determine the relation between the length of disease and the % of vaccinated people, and the relation between the % vaccination required to yield a herd immunity of .95 for different contaigiousness levels 

List of main programs and their functions:

mainJoe.cpp : emulates the output of the sample output in section 44.2, 		tests our person class
mainPopTest.cpp : emulates the output of the sample output in section     , 	tests our population class (does not allow spreading/contact)
mainNeighbor_vacc_test.cpp : tests interactions restricted to neighbors, and 	tests the effect of vaccinating certain members of the population
mainRandomInfect.cpp : this tests the full capabilities of our code, tests 		the random_infect method that simulates random interactions with a set 		number of interactions per person
mainDataOutput.cpp : generates two .csv files that are used to plot our data 	and determine the relationship between % vaccianted and time the disease 	remains in the population, and vaccination rate and contagiousness to get 	 herd immunity