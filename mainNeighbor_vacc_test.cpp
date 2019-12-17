// this is the main program that tests both the infect neighbor and vaccinate methods

#include <iostream>
#include "library.h"

//this is by no means a complete simulation, but it shows that everything works as intended

//might want to update and make slighly better!!! ugly right now!!!
//can include the ?,+, and - nomenclature
int main()
{
	srand((unsigned)time(0));
	Population pop = Population(7);
	bool done = false;
	string status = "";

	pop.random_infection();
	cout << pop.count_infected() << endl;

	while (!done)
	{
		pop.neighborInfect();
		cout << pop.count_infected() << endl;
		pop.update();
		if (pop.count_infected() == 0)
		{
			done = true;
		}
	}


	Population pop1 = Population(7);
	done = false;
	status = "";

	//need to make sure my randon_infected and innoculation methods 
	//don't overlap (it's only one person, but technically doesn't work as intended)
	pop1.set_innoculation(.25); //only one innoculated person will block spread lol
	pop1.random_infection(); //ensures at least one person is infected
	cout << pop1.count_infected() << endl;

	while (!done)
	{
		pop1.neighborInfect();
		cout << pop1.count_infected() << endl;
		pop1.update();
		if (pop1.count_infected() == 0)
		{
			done = true;
		}
	}
	return 0;


	/* code below tested set_innoculation to check that it worked

	//should write an actual test method to test in conjuction with 
	//infect_neighbor; this is just testing the function
	Population testPop = Population(8);
	testPop.set_innoculation(.25); //vacinates 1/4 of the population
	//printing within set_innoculation to test the method
	*/
}