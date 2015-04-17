
#include <cstdlib>
#include <iostream>


int triangular(int number)
{
	// ToDo: Exercise 1.a - return triangular number
	
	if(number == 1) return 1;
	return number + triangular(number-1);

	//return 0;
}

void pretty_print(int decimal)
{
	// ToDo: Exercise 1.c - print number with decimal marks to console
	
	if(decimal < 1000)
	{
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
	int dreieckszahl = triangular(n);
	
	if(dreieckszahl < n) 
		{
				std::cout << "Zahl zu groß";
				return 2;
		}
	/*Ein Integer in C++ hat die Größe von 4 Bytes. (Ermittelt über die Methode "sizeof(int)") Also umfasst ein Integer einen Wertebereich von 
	 * 2^32. Ein signed Int umspannt also den Zahlenbereich von -2^31 = -2147483648 bis (2^31)-1 = 2147483647.*/
		
pretty_print(dreieckszahl);	
std::cout << "\n"; 
	 

	return 0;
}
