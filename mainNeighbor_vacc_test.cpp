//Kenneth Meyer: klm5375
//Vincent Lebovitz: vjl369

// this is the main program that tests both the infect neighbor and vaccinate methods

#include <iostream>
#include "library.h"

using std::cout;
using std::endl;

//this is by no means a complete simulation, but it shows that everything works as intended

//might want to update and make slighly better!!! ugly right now!!!
//can include the ?,+, and - nomenclature
int main()
{
	srand(time(NULL));
	int numPeople = 10;
	Population pop = Population(10);
	cout << "Testing infection by infecting neighbors, no innoculation:" << endl;
	//will use a probability of infection of .5

	bool done = false;
	string status = "";
	int day = 1;

	pop.random_infection();
	int x = pop.count_infected();
	vector<Person> pop1 = pop.getPop();
	while (!done)
	{
		cout << "Day " << day << ", " << x << " sick: ";
		for(int i = 0; i < numPeople; i++){
			if(pop1[i].get_condition() == -4){
				cout << "x ";
			}else if(pop1[i].get_condition() == -2){
				cout << "? ";
			}else if(pop1[i].get_condition() == 0){
				cout << "- ";
			}else{
				cout << "+ ";
			}
		}
		cout << endl;
		pop.update();
		pop.neighborInfect(float(.5));
		x = pop.count_infected();
		day++;
		pop1 = pop.getPop();
		if (pop.count_infected() == 0)
		{
			done = true;
		}
	}
	cout << "Day " << day << ", " << x << " sick: ";
		for(int i = 0; i < numPeople; i++){
			if(pop1[i].get_condition() == -4){
				cout << "x ";
			}else if(pop1[i].get_condition() == -2){
				cout << "? ";
			}else if(pop1[i].get_condition() == 0){
				cout << "- ";
			}else{
				cout << "+ ";
			}
		}
		cout << endl;

	cout << "Testing with an innoculation rate of .25:" << endl;
	pop = Population(numPeople);
	done = false;
	status = "";
	day = 1;

	//need to make sure my randon_infected and innoculation methods 
	//don't overlap (it's only one person, but technically doesn't work as intended)
	pop.set_innoculation(.25); //only one innoculated person will block spread lol
	pop.random_infection(); //ensures at least one person is infected
	x = pop.count_infected();
	pop1 = pop.getPop();
	while (!done)
	{
		cout << "Day " << day << ", " << x << " sick: ";
		for(int i = 0; i < numPeople; i++){
			if(pop1[i].get_condition() == -4){
				cout << "x ";
			}else if(pop1[i].get_condition() == -2){
				cout << "? ";
			}else if(pop1[i].get_condition() == 0){
				cout << "- ";
			}else{
				cout << "+ ";
			}
		}
		cout << endl;
		pop.update();
		pop.neighborInfect(float(.5));
		x = pop.count_infected();
		day++;
		pop1 = pop.getPop();
		if (pop.count_infected() == 0)
		{
			done = true;
		}
	}
	cout << "Day " << day << ", " << x << " sick: ";
		for(int i = 0; i < numPeople; i++){
			if(pop1[i].get_condition() == -4){
				cout << "x ";
			}else if(pop1[i].get_condition() == -2){
				cout << "? ";
			}else if(pop1[i].get_condition() == 0){
				cout << "- ";
			}else{
				cout << "+ ";
			}
		}
		cout << endl;
	return 0;
	/* code below tested set_innoculation to check that it worked

	//should write an actual test method to test in conjuction with 
	//infect_neighbor; this is just testing the function
	Population testPop = Population(8);
	testPop.set_innoculation(.25); //vacinates 1/4 of the population
	//printing within set_innoculation to test the method
	*/


	/* code below tested set_innoculation to check that it worked

	//should write an actual test method to test in conjuction with 
	//infect_neighbor; this is just testing the function
	Population testPop = Population(8);
	testPop.set_innoculation(.25); //vacinates 1/4 of the population
	//printing within set_innoculation to test the method
	*/
}