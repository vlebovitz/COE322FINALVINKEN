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
		condition = n;
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
		int dude = rand() % n;

		//most likely want to allow this to be changed!!!
		pop[dude].infect(5); 

	}

	//sets the probability that the disease will be transferred when ppl interact
	void set_probability_of_transfer(float probability)
	{	
		p = probability;
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
		//not really sure what this does
		//assert(im == M);

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

	//currently has entire population interat with phantom person (will be deleted when merged, not used)
	
	/*
	void reactionRate()
	{
		float rate = 0;
		srand(time(NULL));

		for (int i = 0; i < n; i++)//loop through entire vector
		{
			 rate = rand() / RAND_MAX;
				if (pop[i].status_string() == "susceptible") //target susceptible people
				{
					if (rate < probability)//probability check
					{
						pop[i].infect(5);//infect the intended person for 5 days
					}
				}
			
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

	//this function runs the simulation by looping the update method
	//from the population 
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
	//might want to create different sims for different "Qs", or 
	//could just write it in the main program
	void runSim1()//!!this is the actual function we will use!!!
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
		return pop; //probably want to delete this method
	}


};


//note - we might want to create multiple main programs and turn them in;
//they would output the stuff at each separate step - do we need a main program 
//for this file if it only contains the classes????

//this just tests whatever we are working on
int main()
{
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