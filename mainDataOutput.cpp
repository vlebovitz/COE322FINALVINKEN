//Kenneth Meyer: klm5375
//Vincent Lebovitz: vjl369

//this is the main program that outputs data for the things we are investigating.
//only will use the random infect program to accomplish this
#include <iostream>
#include "library.h"
#include <fstream>

int main()
{
	std::ofstream myfile1;
	std::ofstream myfile2;
    myfile1.open("LengthOfDisease.csv");
    myfile1 << "Vaccination, Length of Disease\n";
    myfile2.open("HerdImmunity.csv");
    myfile2 << "Contagiousness, Vaccination rate to achieve .95 immunity\n";

	srand(time(NULL));
	int numPeople = 40000; //number of undergrads at ut!!
	Population pop = Population(numPeople);
	int x;

	int day = 1;
	double avgDay;
	int sumDay;
	//j = vaccination percent
	double j = 0;

	//outputs data to file to investigate length of disease run
	for(int i = 0; i < 100; i++){
		//use 30 trials to compute an AVERAGE of the recorded values for each innoculation rate
		//for(int k = 0; k < 30; k++){
			day = 1;
			pop = Population(numPeople);
			pop.set_innoculation(float(j));
			pop.random_infection();
			x = pop.count_infected();
			while(x > 0){
				pop.update();
				//chose constants of 7 interactions and .5 cahnge to infect
				pop.random_interation(7,.5); 
				//pop1 = pop.getPop();
				day++;
				x = pop.count_infected();
			}
			//sumDay+=day;
		//}
		//avgDay = double(sumDay)/30;
		myfile1 << j << "," << day << "\n";
		cout << j << "," << day << endl;
		j = j + 0.01;
	}

	pop = Population(numPeople);
	double percentUninfected = 0.0;

	//vaccination rate
	j = 0;
	double contagiousness = 0.01;

	//investigating herd immunity
	for(int i = 0; i < 100; i++){
		//use 30 trials to compute an AVERAGE of the required vaccination rate to achieve a herd immunity of .95
		//for(int k = 0; k < 30; k++){
			percentUninfected = 0;
			//would have been more effictive to set j to a larger number when contagiousness inc
			j = 0;
			while(percentUninfected < .95){
				pop = Population(numPeople);
				pop.set_innoculation(float(j));
				pop.random_infection();
				x = pop.count_infected();
				while(x > 0){
					pop.update();
					//chose constants of 7 interactions
					pop.random_interation(7,contagiousness); 
					//pop1 = pop.getPop();
					day++;
					x = pop.count_infected();
				}
				j = j + 0.01;
				percentUninfected = 1 - double(pop.count_stable())/(numPeople - int(j*numPeople) - 1);
			}
		//}
		myfile2 << j << "," << contagiousness << "\n";
		cout << j << "," << contagiousness << endl;
		contagiousness = contagiousness + 0.01;
	}

	myfile1.close();
	myfile2.close();
}