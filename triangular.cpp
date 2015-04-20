
#include <cstdlib>
#include <iostream>
#include <math.h>

int triangular(int number)
{
	// ToDo: Exercise 1.a - return triangular number	
	if(number == 1)
		return 1;
	else return number + triangular(number-1);
}

void pretty_print(int decimal)
{
	// ToDo: Exercise 1.c - print number with decimal marks to console
	if(decimal < 1000) {
		std::cout << decimal;
		return;
	}
	pretty_print(decimal/1000);
	std::cout << ".";
	if(decimal%1000 < 100)
		std::cout << 0;
	if(decimal%1000 < 10)
		std::cout << 0;
	std::cout << decimal % 1000;	
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 

	// ToDo: Exercise 1.b - check if n is in domain, if not print valid domain and codomain and return 2
	unsigned int dmin = 1;
	unsigned int dmax = 65535;// -0.5+(sqrt(2*2147483647)));
	unsigned int cdmin = triangular(dmin);
	unsigned int cdmax = triangular(dmax);
	if(n > dmax) {
			std::cout << "[" << dmin << "," << dmax << "],[" << cdmin << "," << cdmax << "]" << std::endl;
			return 2;
	}
	int dreieckszahl = triangular(n);
	pretty_print(dreieckszahl);	
	std::cout << std::endl; 
	 

	return 0;
}
