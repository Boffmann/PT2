
#include <cstdlib>
#include <iostream>

int counter;

int fibonacci(int number)
{
	// ToDo: Exercise 2.c - count number of calculation steps
	// ToDo: Exercise 2.b - retun 0 on bad arguments
	if(number <=0)
		return 0;
	// ToDo: Exercise 2.b - retrieve nth fibonacci number iteratively
	counter = 1;
	int aktuell = 1;
	int n1 = 1;//fibonacci vom Vorgänger
	int n2 = 0;//fibonacci vom zweiten Vorgänger
	while (counter < number) {
		counter++;
		aktuell = n1+n2;
		n2 = n1;
		n1 = aktuell;
	}
	return aktuell;
}

int main(int argc, char * argv[])
{
	if(argc != 2)
		return 1;	// invalid number of parameters

	int n = std::atoi(argv[1]); 
	// ToDo: Exercise 2.c - print calculation steps
	int fib = fibonacci(n);
	std::cout << n << " : " << fib << " : " << "#" << counter << std::endl;
	return 0;
}
