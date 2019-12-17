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

};

//inherts Person class, as a Population is a vector of people
class Population : public Person {

protected:
	vector<Person> pop = {};
	int n, day;
	float probability;
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
		int dude = rand() % n; //think this works? can test somewhere
		//cout << dude << endl;
		pop[dude].infect(5); //default: sick for 5 days...might want to allow change



	}

	//sets the probability of 
	void set_probability_of_transfer(float probability)
	{	
		probability = 0.6;
	
	}
	//creates algorithm for interactions
	void neighborInfect()
	{
		float rate = 0;
		srand(time(NULL));
		set_probability_of_transfer(0.6);

		for (int i = 0; i < n; i++)//loop through entire vector
		{
			 rate = rand() / RAND_MAX;
			 if (pop[i].status_string() == "sick") 
			 {
				 if (i != 0 && i != (n - 1))
				 {
					 if (pop[i+1].status_string() == "susceptible") //target susceptible people
					 {
						 if (rate < probability)//probability check
						 {
							 pop[i+1].infect(5);//infect the intended person for 5 days
						 }
					 }
					 if (pop[i-1].status_string() == "susceptible")
					 {
						 if (rate<probability)
						 {
							 pop[i-1].infect(5);
						 } 
					 }
					 else if (i == 0)
					 {
						 if (pop[i + 1].status_string() == "susceptible")
						 {
							 if (rate < probability)
							 {
								 pop[i+1].infect(5);
							 }
						 }
					 }
					 else if (pop[i - 1].status_string() == "susceptible")
					 {
						 if (rate < probability)
						 {
							 pop[i-1].infect(5);
						 }
					 }

				 }
			 }
		}
	}

	//counts the number of infected people in the population
	int count_infected()
	{
		int num = 0;
		for (int i = 0; i < n; i++) {
			if (!pop[i].is_stable()) {
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
			if (i == 0) {
				cout << "Day " << day << ": Joe is " << pop[i].status_string() << endl;
			}
			pop[i].update();
		}
	}

	//this function runs the simulation by looping the update method
	//from the population 
	void runSim()
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
	void runSim1()//!!this is the actual function for testing!!
	{
		random_infection();

		while ( count_infected()>0)
		{
			update();
			neighborInfect();
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

int main()
{
	srand((unsigned)time(0));
	Population testPop = Population(3);

	testPop.runSim1();
	//testPop.getPop(0).infect(5);
	
	//testPop.neighborInfect();
	//cout << testPop.getPop(0).status_string() << endl;

	//issue with "getPop", was trying to return Person, function 
	//definition actually returned a vector

	/*
	bool stable = testPop.getPop(0).is_stable();
	while (!stable)
	{
		testPop.getPop(0).update();
		cout << testPop.getPop(0).status_string() << endl;
		stable = testPop.getPop(0).is_stable();
	}
	*/

	return 0;
}