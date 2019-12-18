//Kenneth Meyer: klm5375
//Vincent Lebovitz: vjl369

// this is the file containing most of our object definitions
// for the COE322 final project (disease propagation)

#include <iostream>
#include <random>
#include <vector>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
//using std::to_string;

class Person {

private:
	//could create a constant, SSN, as an identifier lol
	//could use age? age -> changing interactions and 
	//ability to be infected (idea)
	int condition;
public:
	//Default constructor
	Person()
	{
		//n(days left): sick, -2: susceptible, 0: recovered, -4: vaccinated
		condition = -2; //default condition is susceptible
	}

	//Constructor that allows us to determine a person's state - not actually used
	Person(int state) //probably won't end up using this constructor
	{
		condition = state;
	}

	//returns description of person's state as a string
	string status_string()
	{
		if (condition == -2) {
			return "susceptible";
		}
		else if (condition == 0) {
			return "recovered";
		}
		else if (condition == -4) {
			return "vaccinated";
		}
		//use the line that was commented out to test results
		else {
			//string result = "sick, " + std::to_string(condition) + " day(s) left.";
			return "sick";
		}
	}

	//updates the person's status to the next day
	void update() //might just make this an int
	{
		//increments n by -1 if it is non zero, stops when equal to zero
		if (condition > 0) {
			condition--;
		}
	}
	//simulates contact between two people, determines if a contact results in an infection
	//might be bad form; contact can infect someone from anybody - that is why we only let infected
	//people come into contact with other people in all of our methods (is also faster to do so)

	//for this specified sickness, we set the length of the disease to 5 days
	//this can (and probably should) be changed for different models
	void contact(Person &joe, float p)
	{
		float x = double(rand())/ RAND_MAX;
		//cout << "random num: " << x << endl;
		//checks probability and if the person contacting joe is sick
		
		if (x < p /*&& condition > 0*/) //condition is always -2, idk why; only contact occurs
		//between a sick person and a person joe anyway so it should be ok
		{
			joe.infect(5);
		}
	}
	//infect a person, disease runs for n days
	void infect(int n)
	{
		if(condition == -2){
			condition = n;
		}
		//cout << n << endl;
		//days = n;
	}

	//vaccinates a person - sets their condition to -4
	void vaccinate()
	{
		condition = -4;
	}

	//indicates whether the person has been sick and is recovered
	bool is_stable()
	{
		if (condition == 0){
			return true;
		}
		else {
			return false;
		}
	}

	//main purpose is to output to data file and terminal window
	//should have written separate methods, like is_stable(), as this
	//would make our main programs easier to understand/prevent silly errors
	int get_condition()
	{
		return condition;
	}

	/* used a get_condition method to replace this
	bool is_vaccinated()
	{
		if(condition == -4){
			return true;
		}else{
			return false;
		}
	}
	*/

};

//inherts Person class, as a Population is a vector of people
class Population : public Person {

protected:
	vector<Person> pop = {};
	int n, day;

	//p = probability of disease transfer on contact, v = % of vaccinated people
	float p, v;
public:

	//Default constructor, mainly a tester - one person in the population
	Population()
	{
		pop.push_back(Person());
		n = 1;
		day = 0;
	}

	//Constructor that sets population of size n
	Population(int npeople)
	{
		n = npeople;
		for (int i = 0; i < npeople; i++) {
			pop.push_back(Person());
		}
	}

	//infects a random person in the population
	void random_infection()
	{
		//might need to avoid 
		int dude = rand() % n;
		//cout << pop[dude].get_condition() << endl;
		//makes sure a vaccinated person is not infected
		while(pop[dude].get_condition() == -4){
			dude = rand() % n;
			//cout << pop[dude].get_condition() << endl;
		}
		pop[dude].infect(5); 

	}

	//sets the probability that the disease will be transferred when ppl interact
	void set_probability_of_transfer(float probability)
	{	
		//not entirely sure if they wanted this function to be combined with the contact function
		p = probability;
	}

	/* moved method to person class
	void contact(Person &joe)
	{
		//srand(time(NULL));
		//srand((unsigned)time(0));
		float x = double(rand())/ RAND_MAX;
		cout << "random num: " << x << endl;
		if (x < p)
		{
			joe.infect(5);
		}
	}
	*/

	//sets the % (0<x<1) of people who are vaccinated; sets that portion of the
	//population's condition to "vaccinated"
	void set_innoculation(float x)
	{
		v = x;
		//rounds the percent to get a whole number of people
		int num = int(v*n);
		vector<int> vac_Location(num,0);

		int y;
		int in, im;

		//knuth algorithm, generates unique random numbers between 0 and n
		im = 0;
		for (in = 0; in < n && im < num; ++in) {
  			int rn = n - in;
  			int rm = num - im;
 			//puts random, non-repeated number 0-n in the vector of the location of vaccinated people
 			if (rand() % rn < rm)    
    			vac_Location[im++] = in; //+ 1; /* +1 since your range begins from 1 */
		}

		//cout << "vector of locations of ppl who got vaccinated" << endl;

		//vacciantes the people at the locations randomly picked by the knurth algo
		for(int k = 0; k < num; k++)
		{
			pop[vac_Location[k]].vaccinate(); //vaccinates person in sepcified locaiton with vaccinate method in person class
			//cout << vac_Location[k] << " ";
		}
		//was used for testing

		/*cout << endl;
		cout << "vector of the conditions of all the people in the population:" << endl;
		for(int j = 0; j < n; j++)
		{
			cout << pop[j].get_condition() << " ";
		}
		cout << endl;
		*/
	}

	//function that simulates interactions, where people can only interact with their neighbors in the arrary
	void neighborInfect(float prob)
	{
		//when vaccinated people are added to the area, they act as boundaries/prevent disease spread
		double rate = 0;
		//srand(time(NULL));
		set_probability_of_transfer(prob);
		vector<int> totalInfected = {};

		for (int j = 0; j < n; j++)
		{
			if (pop[j].status_string() == "sick")
			{
				totalInfected.push_back(j);
			}
		}

		//testing to see if the rate is correct
		//caught that rate was always zero due to integer division!!!
		/*
		for(int z = 0; z < 10; z++){
			cout << double(rand())/ RAND_MAX << endl;
		}
		*/

		//can either handle edges as people with one neighbor, or treat array as a "circle" and connect ends
		for (int i = 0; i < totalInfected.size(); i++)
		{
			//rate = rand() / RAND_MAX; //need to do this right before someone is infected (can infect 2 ppl)
			if (pop[totalInfected[i]].status_string() == "sick")
			{
				//treats boundaries separately as they only have one neighbor
				if (totalInfected[i] > 0 && totalInfected[i] < (n - 1))
				{
					if (pop[totalInfected[i]+1].status_string() == "susceptible")
					{
						pop[totalInfected[i]].contact(pop[totalInfected[i]+1],p);
					}
					if (pop[totalInfected[i]-1].status_string() == "susceptible")
					{
						pop[totalInfected[i]].contact(pop[totalInfected[i]-1],p);
					}
				}
				//decided to treat ends of vector as boundaries/dead ends
				else if (totalInfected[i]  == 0)
				{
					if (pop[totalInfected[i]+1].status_string() == "susceptible")
					{
						pop[totalInfected[i]].contact(pop[totalInfected[i]+1],p);
					}
				}
				else
				{
					if (pop[totalInfected[i]-1].status_string() == "susceptible")
					{
						pop[totalInfected[i]].contact(pop[totalInfected[i]-1],p);
					}
				}

			}
		}
		//outputs the results for testing purposes
		//for (int i = 0; i < n; i++)
		//{
			//cout << pop[i].get_condition();
		//}
		//cout << endl;
	}
	//method is not the most effective (brute forces that random numbers) but it works and isn't THAT slow
	//function that "codes random interactions" - y = # people each person interacts with, y < n-1
	//was supposed to be "random_interaction, typo but didn't change lol"
	void random_interation(int y, float prob)
	{
		//can ignore large comment section, was my thought process

		//----------------------------------------------------------------

		//need to figure out some way to connect the people
		//should I use graph theory? brute force?....
		//can possibly incorporate the knuth algorithm thing into this

		//only becomes challenging when # sick people > n interactions (which almost always happens)
		//AND whenever random number gen is trying to pick a small portion of the nums

		//idea: contact matrix like cities connected via airports

		//easier: start with the first person, have them interact with 6 people,
		//then "remove" them from the list/random #generator. if someone is interacted
		//with 6 times, also remove them from the list.


		/* Previous attempts; convoluded
		--------------------------------------------------------------------
		//create vector with same number of elements as number of infected ppl
		vector<*Person> pointer_pop (pop.count_infected(),NULL); //not sure if this should be null
		vector<int> interactionCount(n,0);

		//only need to track interactions that include an infected person
		for(int i = 0; i < n; i++){
			if(pop[i].get_condition() > 0){
				pointer_pop[i] == &pop[i]; //not sure if this is the right way to declare a pointer
				//might want to make a person pointer, then set pointer
				//equal to pop[i], set arrary equal to that...but then would have to deference the pointer?.....
				//need to figure out the best way to do this!!!!
			}
		}
				
		//
		for(int j = 0; j < pointer_pop.size(); j++){
			//randomly interact with 6 people (knuble shuffle?)
			//checks that the person objects are not equal i.e. would be contacting itself

			while()
			//if(interaction_count[randomnum] == 6){
				//pop this and the element in the pointer_pop vector
			//}


			//only commented to test mainNEigh_vacc thing
			//pointer_pop.pop();

		}
		------------------------------------------------------------------------
		*/

		vector<int> sickLocations = {};
		for(int z = 0; z < n; z++){
			if(pop[z].get_condition() > 0){
				sickLocations.push_back(z);
			}
		}
		vector<int> interactionCount(n,0);
		set_probability_of_transfer(prob); //need to pass p to contact function
		//this should work, but is slow....would benefit from removing the people who have been interacted with 6 times
		int randIndex;
		for(auto k : sickLocations){
			//skips the person if they are not sick (only initiating contact from sick people
			//will create all the necessary interactions; avoids interactions btw 2 nonsick ppl
			if(pop[k].get_condition() < 1 || interactionCount[k] >= y){
				continue;
			}
			//it is possible for someone to have to "contact themselves"
			//this is an interesting graph theory problem; not going to solve it today lol
			while(interactionCount[k] < y){
				//allows people to contact the same people multiple times
				randIndex = rand()%n;
				if(interactionCount[randIndex] == y){
					continue;
				}//else if(interactionCount)
				//allows people to infect themselves as an escape condition
				else if(randIndex == k && n - count_infected() < 2 && interactionCount[k] < y - 2) // <2 or <number of interactions?....
				{
					contact(pop[randIndex],p);
					interactionCount[randIndex]++;
					interactionCount[k]++;
				}else{
					contact(pop[randIndex],p);
					interactionCount[randIndex]++;
					interactionCount[k]++;
				}
				//cout << "test" << endl;
			}
		}
	}
	
	//counts the number of infected people in the population
	int count_infected()
	{
		int num = 0;
		for (int i = 0; i < n; i++) {
			if (pop[i].get_condition() > 0){
				num++;
			}
		}
		return num;
	}
	//returns the number of stable ppl in the population
	int count_stable()
	{
		int num = 0;
		for (int i = 0; i < n; i++) {
			if (pop[i].is_stable()){
				num++;
			}
		}
		return num;
	}
	//updates the condition of every member in the population
	void update()
	{
		for (int i = 0; i < n; i++) {
			//see output for "joe" (1st guy) after we update each day
			//if (i == 0) {
				//cout << "Day " << day << ": Joe is " << pop[i].status_string() << endl;
			//}
			pop[i].update();
		}
	}
	vector<Person> getPop()
	{
		return pop;
	}
};