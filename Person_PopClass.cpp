// this is the file containing most of my object definitions
// for the COE322 final project (disease propagation)

#include <iostream>
#include <random>
#include <vector>

using std::cin
using std::cout
using std::endl
using std::string
using std::vector

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
		Person(int state)
		{
			condition = state;
			name = "avgJoe";
			days = 0;
			//SSN = SSN_recent + 1;
		
		//returns description of person's state as a string
		string status_string()
		{
			if(condition == -2){
				return "susceptible";
			}else if(condition == 0){
				return "recovered";
			}else if(condition == -4){
				return "vaccinated";
			}else{
				return "sick, " + condition " day(s) left";
			}
		}
		
		//updates the person's status to the next day
		void update() //might just make this an int
		{
			//not entirely sure what to put here/how to update, might need to
			//introduce another method called "contact" or something

			//this could be expanded upon maybe or something...idk lol
			
			//increments n by -1 if it is non zero, stops when equal to zero

			if (condition > 0) {
				condition--;
			}
		}
		
		//infect a person, disease runs for n days
		void infect(int n)
		{
			condition = n;
			//days = n;
		}
		
		//indicates whether the person has been sick and is recovered
		//NOTE: probably should return true for vaccinated and recovered (?)
		boolean is_stable()
		{
			if (condition == 0 || condition == 4){
				return true;
			}else{
				return false;
			}
		}
		
};

//inherts Person class, as a Population is a vector of people
class Population : class Person {

	protected:
		vector<Person> pop = {};
		int n;
	public:
		
		//Default constructor, mainly a tester - one person in the population
		Population()
		{
			//can combine these two lines; will do so in 2nd constructor
			person1 = Person();
			pop.pushback(person1);
			n = 1;
		}
		
		//Constructor that sets population of size n
		Population(int npeople)
		{
			n = npeople;
			for (int i = 0; i < npeople; i++){
				pop.pushback(Person());
			}
		}
		
		//infects a random person in the population
		void random_infection()
		{
			int dude = rand()%n; //think this works? can test somewhere
			pop(dude).infect(5); //default: sick for 5 days...might want to allow change
		}
		
		//counts the number of infected people in the population
		int count_infected()
		{
			int num = 0;
			for(int i = 0; i < n; i++){
				if (pop(i).is_stable() == false){
					num++;
				}
			}
			return num;
		}
		
		//updates the condition of every member in the population
		void update()
		{
			for(int i = 0; i < n; i++){
				pop(i).update();
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
			while (x > 0)
			{
				update();
				x = count_infected();
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
			Population testPop = Population();
			testPop.getPop(0).infect(5);
			cout << testPop.getPop(0).status_string(); << endl;
			
			boolean stable = testPop.getPop(0).is_stable();
			while (!stable)
			{
				testPop.getPop(0).update();
				cout << testPop.getPop(0).status_string(); << endl;
				stable = testPop.getPop(0).is_stable();
			}
			
			return 0;
}

			