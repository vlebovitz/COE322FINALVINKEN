// this is the file containing most of my object definitions
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

//consider using a compartmental model in addition to a contact model
class Person {

private:
	//could create a constant, SSN, as an identifier lol
	//could use age? age -> changing interactions and 
	//ability to be infected (idea)
	int condition; //days; //would SSN need to be global to ensure no repition?
	string name;
public:
	//Default constructor
	Person()
	{
		//n(days left): sick, -2: susceptible, 0: recovered, -4: vaccinated
		condition = -2; //default condition is susceptible
		name = "avgJoe";
	

		//days = 0;
		//SSN = SSN_recent + 1;
	}

	//Constructor that allows us to determine a person's state
	//not sure if we want to use this; can easily just infect somebody...
	//only real use would be to vaccinate people; could actually do this randomly
	//need to figure out best way to create 10k people objects
	Person(int state) //probably won't end up using this constructor
	{
		condition = state;
		name = "avgJoe";
	
		//days = 0;
		//SSN = SSN_recent + 1;
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
		//not entirely sure what to put here/how to update, might need to
		//introduce another method called "contact" or something

		//this could be expanded upon maybe or something...idk lol


		//only for testing purposes - need to alter this function
		//cout << "Joe is " << status_string() << endl;

		//increments n by -1 if it is non zero, stops when equal to zero
		if (condition > 0) {
			condition--;
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
	//NOTE: probably should return true for vaccinated and recovered (?)
	bool is_stable()
	{
		if (condition == 0 || condition == -4) {
			return true;
		}
		else {
			return false;
		}
	}

	//sole purpose is to write to a text file
	int get_condition()
	{
		return condition;
	}

	/* might want to create an "is vaccinated" method, original
		condition above for is_stable() was if condition == 0 || condition == -4

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
		//combined lines
		//Person person1 = Person(); - could be useful to track 
		//the "first" person as an example/to print out easily
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

		//most likely want to allow this to be changed!!!
		pop[dude].infect(5); 

	}

	//sets the probability that the disease will be transferred when ppl interact
	void set_probability_of_transfer(float probability)
	{	
		//not entirely sure if they wanted this function to be combined with the contact function
		p = probability;
	}

	//not working, not sure why - uncommented old code I commented out; not of most importance
	//simulates contact between two people, determines if a contact results in an infection
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
	
	//
	void neighborInfect()
	{
		//when vaccinated people are added to the area, they act as boundaries/prevent disease spread
		double rate = 0;
		//srand(time(NULL));
		set_probability_of_transfer(0.3);
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
				if (totalInfected[i] > 0 && totalInfected[i] < (n - 1))
				{
					if (pop[totalInfected[i]+1].status_string() == "susceptible")
					{
						contact(pop[totalInfected[i]+1]);
						//rate = double(rand())/ RAND_MAX;
						//if (rate < p)
						//{
							//pop[totalInfected[i]+1].infect(5);
						//}
					}
					if (pop[totalInfected[i]-1].status_string() == "susceptible")
					{
						contact(pop[totalInfected[i]-1]);
						//rate = double(rand())/ RAND_MAX;
						//if (rate < p)
						//{
							//pop[totalInfected[i]-1].infect(5);
						//}
					}
				}
				//decided to treat ends of vector as boundaries/dead ends
				else if (totalInfected[i]  == 0)
				{
					if (pop[totalInfected[i]+1].status_string() == "susceptible")
					{
						contact(pop[totalInfected[i]+1]);
						//rate = double(rand())/ RAND_MAX;
						//if (rate < p)
						//{
							//pop[totalInfected[i]+1].infect(5);
						//}
					}
				}
				else
				{
					if (pop[totalInfected[i]-1].status_string() == "susceptible")
					{
						contact(pop[totalInfected[i]-1]);
						//rate = double(rand())/ RAND_MAX;
						//if (rate < p)
						//{
							//pop[totalInfected[i]-1].infect(5);
						//}
					}
				}

			}
		}
		//outputs the results for testing purposes
		for (int i = 0; i < n; i++)
		{
			cout << pop[i].get_condition();
		}
		cout << endl;
	}
	//talk about effectiveness of how truly random whatever method i use is
	//also talk about efficiency of the method i use
	//function that "codes random interactions" - y = # people each person interacts with, y < n-1
	/*
	void random_interation(int y)
	{

		//need to figure out some way to connect the people
		//should I use graph theory? brute force?....
		//can possibly incorporate the knuth algorithm thing into this

		//only becomes challenging when # sick people > n interactions (which almost always happens)
	
		//idea: store in n x n matrix, like airport map, should be 6 1's in each row and col
		//draw back: for very large populations, this will be slow/require too much memory

		//I feel like this is really innefficient lol but idk how to do this
		//vector<int> pop_Loc
		

		//easier: start with the first person, have them interact with 6 people,
		//then "remove" them from the list/random #generator. if someone is interacted
		//with 6 times, also remove them from the list.

		//create vector with same number of elements as number of infected ppl
		vector<Person> pointer_pop (pop.count_infected());
		vector<int> interaction_count(n,0);

		//only need to track interactions that include an infected person
		for(int i = 0; i < pop.count_infected(); i++){
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

			//if(interaction_count[randomnum] == 6){
				//pop this and the element in the pointer_pop vector
			//}


			//only commented to test mainNEigh_vacc thing
			//pointer_pop.pop();

		}
	}
	*/

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

	//simulations will be written as main programs; delete
	void runSimTest()
	{
		//do we need to use "this" as done in JAVA??
		int x = 1; //want to do this on the current obj
		random_infection();

		//should also write print statements here
		//might want to create separate methods or something; 
		//want to allow different ways to show output....
		while (x > 0 || day < 6) //added day < 6 to go beyond infection period
		{

			update();
			x = count_infected();
			day++;
		}
	}
	//simulations will be written as main programs; delete
	void runSim1() //delete this
	{
		//reactionRate();


		int x = 1; //want to do this on the current obj
		random_infection();

		while (x > 0 || day < 6) //added day < 6 to go beyond infection period
		{
			update();
			x = count_infected();
			day++;
		}
	}

	//most likely need to add a setter method to allow me to access
	//values in the vector of people

	//will "getting" the vector then infecting the person change the value of 
	//the person/change their status??? (and be updated in the vector??)
	vector<Person> getPop()
	{
		return pop;
	}


};


//note - we might want to create multiple main programs and turn them in;
//they would output the stuff at each separate step - do we need a main program 
//for this file if it only contains the classes????

//this just tests whatever we are working on
int main()
{
	//srand((unsigned)time(0));
	srand(time(NULL));
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