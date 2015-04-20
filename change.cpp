
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

int values[] = {5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
void change(const int due, const int paid)
{
	int current = paid - due;
	int i = 0;
	int n = 0;
	if(current >= 0) {		
		std::cout << "coin,num" << std::endl;	// only print line when due and paid are valid numbers
	}
	while(1) {
		if(current >= values[i]) {
			current -= values[i];
			n++;
		} else {
			if(n > 0)
				std::cout << values[i] << "," << n << std::endl;
			i++;
			n = 0;
			if (current == 0) break;	// exit loop after last line got printed
		}
	}
}

int main(int argc, char * argv[])
{
	int paid;
	int due;
	std::ofstream filestr;
	if(argc == 5 && (std::strcmp(argv[1], "-o") == 0 || std::strcmp(argv[3], "-o") == 0)) {
		if(std::strcmp(argv[1], "-o") == 0) { 
			// redirect cout into file
			char * filename = argv[2];
			filestr.open (filename);
  			std::cout.rdbuf(filestr.rdbuf());

			due  = std::atoi(argv[3]); 
	 		paid = std::atoi(argv[4]);
		} else {
			// redirect cout into file
			char * filename = argv[4];
			filestr.open (filename);
  			std::cout.rdbuf(filestr.rdbuf());

			due  = std::atoi(argv[1]); 
	 		paid = std::atoi(argv[2]);
		}
	} else if(argc != 3) {
		return 1;	// invalid number of parameters
	} else {
		due  = std::atoi(argv[1]); 
	 	paid = std::atoi(argv[2]);	
	}
	if(due > paid) {
		return 1;
	}
	change(due,paid);
	return 0;
}
