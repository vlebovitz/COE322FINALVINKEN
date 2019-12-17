//main program to test simple population, where the population is one person

//need to rename the file titled "main.cpp" to "library"
#include <iostream>
#include "library.h"
#include <random>

using std::cout;
using std::endl;
//does not employ the "population" function
int main()
{
	srand((unsigned)time(0));
	//Population pop = Population(7);

	Person bob; //= Person()?

	int i = 0;
	bool done = false;
	float infection_chance;


	while(!done)
	{
		i++;
		//make sure update method only subtracts 1 from n
		bob.update();
		infection_chance = (float) rand()/(float)RAND_MAX;

		if (infection_chance > .75)
		{
			bob.infect(5);
		}

		cout << "On day " << i << ", Bob is " << bob.status_string() << endl;
		if(bob.is_stable())
		{
			break;
		}
	}
	
	//old command; created function to act as our main file....
	//		compare the two to make sure it works!! use the main program in library file (it it still exists after using headers)
	//testPop.runSimTest();

	return 0;
}