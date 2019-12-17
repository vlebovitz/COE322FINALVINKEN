//main program to test simple population, where the population is one person

//need to rename the file titled "main.cpp" to "library"
#include "main.cpp"
#include random

using std::cout;
using std::endl;
//does not employ the "population" function
int main()
{
	//not sure if we need this for the simple simulation
	srand((unsigned)time(0));

	//Population testPop = Population();

	//is this the correct declaration????
	Person bob; //= Person()?

	int i = 1;
	bool done = false;
	float infection_chance;


	while(!done)
	{
		//make sure update method only subtracts 1 from n
		joe.update();
		infection_chance = (float) rand()/(float)RAND_MAX;

		if (infection_chance > .9)
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