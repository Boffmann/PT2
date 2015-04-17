
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

std::string change(const int due, const int paid)
{
	// ToDo: Exercise 3.a - return set of change tuples
	int toChange = paid - due;
	int counter = 14;
	char changed[15*8] = {0}; //drei für Value, drei für quantity, einer für Komma und einer für Leerzeichen * 15 maximale Zeilen
	
	int value[15] = {1,2,5,10,20,50,100,200,500,1000,2000,5000,10000,20000,50000};
	int quantity[15] = {0};
	
	while (toChange != 0)
	{
			if(value[counter] <= toChange)
		{
				toChange -= value[counter];
				quantity[counter] += 1;
		}else{
			counter--;
		}
	}
		
		for(int i = 0; i<15;i++)
		{	
				if(quantity[i] != 0)
				{
					char v[3];
					char q[3];
					sprintf(v, "%d", value[i]);
					sprintf(q, "%d", quantity[i]);
					
					strcat(changed, v);
					strcat(changed, ", ");
					strcat(changed, q);
					strcat(changed, "\n");

				}
		}
	return (std::string)changed;
}

int main(int argc, char * argv[])
{
	if(argc < 3)
		return 1;	// invalid number of parameters

	const int due  = std::atoi(argv[1]); 
	const int paid = std::atoi(argv[2]); 

	// ToDo: Exercise 3.c - catch invalid arguments
	if(argc == 5 && strcmp(argv[2], "-o"))
		{
				std::ofstream f;
				f.open(argv[4]);
				f << change(due, paid);
				f.close();
		}

	change(due,paid);
	
	std::cout << change(due, paid);

	// ToDo: Exercise 3.b - print change data as CSV to console 

	return 0;
}
