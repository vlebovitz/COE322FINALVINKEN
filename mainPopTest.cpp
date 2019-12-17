//main program that tests a small population

//produces sample output with ?s, +s, -s, 

//might need to rename this, use library's header file
#include "main.cpp"
#include <iostream> //do we need this????

using std::cout;
using std::cin;
using std::string;

int main()
{

	srand((unsigned)time(0));

	//creates a population of 7 people
	Population pop = Population(7);

	int i = 1;
	int j;
	bool done = false;
	string status = "";

	pop(3).infect(5); //infects '4th' person in population for 5 days

	//also infecting them on first day, only want to test our population class
	while(!done)
	{
		//make sure update method only subtracts 1 from n

		cout << "Day " << i << ", #sick = " << pop.count_infected() << " : ";

		for (j = 0; j < 7; j++)
		{
			status = pop(j).status_string();
			if(status == "susceptible"){
				cout << "? ";
			}else if(status == "sick"){
				cout <<"+ ";
			}else{
				cout <<"- ";
			}
		}
		cout << endl;

		if(bob.is_stable())
		{
			break;
		}

		//including at the end, because we are infecting the person outside of loop
		pop.update();

	}

	cout << "The disease ran its course on Day " << i << endl;

}