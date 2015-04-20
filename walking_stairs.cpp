
#include <cstdlib>
#include <iostream>

// ToDo: Exercise 2.d - adapt and implement combinations
unsigned long long int combinations(int number)
{
	unsigned long long int x=1;
	unsigned long long int y=0;
	unsigned long long int z=0;
	for(int i=0; i<number;i++)
	{
		z = x+y;
		y = x;
		x = z;
	} 
	return z;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 
	std::cout << combinations(n) << std::endl;
	return 0;
}