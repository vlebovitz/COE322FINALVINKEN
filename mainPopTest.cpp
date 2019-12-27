//Kenneth Meyer: klm5375
//Vincent Lebovitz: vjl369

//main program that tests a small population

//produces sample output with ?s, +s, -s, 

//might need to rename this, use library's header file
#include <iostream>
#include "library.h"
#include <random>
 //do we need this????

using std::cout;
using std::cin;
using std::string;

int main()
{
	cout << "Testing Population class, no transmission allowed: " << endl;
	srand((unsigned)time(0));
	Population pop = Population(7);

	int i = 0;
	int j;
	bool done = false;
	string status = "";

	pop.random_infection(); //infects random person for 5 days

	//also infecting them on first day, only want to test our population class
	while(!done)
	{
		//make sure update method only subtracts 1 from n

		i++;
		cout << "Day " << i << ", #sick = " << pop.count_infected() << " : ";
		for (j = 0; j < 7; j++)
		{
			//not sure if this is the best way to access
			status = pop.getPop()[j].status_string();
			if(status == "susceptible"){
				cout << "? ";
			}else if(status == "sick"){
				cout <<"+ ";
			}else{
				cout <<"- "; //recovered
			}
		}
		cout << endl;

		if(pop.count_infected() == 0)
		{
			done = true;
		}else{ //no need to update if disease has already run its course
			//including at the end, because we are infecting the person outside of loop
			pop.update();
		}
	}
	cout << "The disease ran its course on Day " << i << endl;
	return 0;

	/* code below tested set_innoculation to check that it worked

	//should write an actual test method to test in conjuction with 
	//infect_neighbor; this is just testing the function
	Population testPop = Population(8);
	testPop.set_innoculation(.25); //vacinates 1/4 of the population
	//printing within set_innoculation to test the method
	*/
}