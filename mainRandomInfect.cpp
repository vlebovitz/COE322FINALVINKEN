//Kenneth Meyer: klm5375
//Vincent Lebovitz: vjl369

//tests the final simulation; simulating random interactions between people, where some are vaccinated
#include <iostream>
#include "library.h"

int main()
{
	cout << "Example of random infection: " << endl;
	cout << "x: vaccinated, ?: susceptible, -: recovered, +: sick" << endl;
	//srand((unsigned)time(0));
	srand(time(NULL));
	int numPeople = 20;
	Population pop = Population(numPeople);
	bool done = false;
	string status = "";

	pop.set_innoculation(.25); //sets innoculation rate
	pop.random_infection();
	int x = pop.count_infected();
	//cout << x << endl;
	vector<Person> pop1 = pop.getPop();

	int day = 1;
	while(x > 0){
		//randomly interact; each person interacts with 3 ppl, contact has .5 chance of infection

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
		//interact with 3 people, .3 chance of disease contraction through interaction
		pop.random_interation(3,.3);
		pop1 = pop.getPop();
		day++;
		x = pop.count_infected();
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

}