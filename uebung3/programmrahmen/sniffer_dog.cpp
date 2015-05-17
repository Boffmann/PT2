#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>

// todo 3.3: Calculate minimum time needed for both dogs to return 
int minTimeDogTraining(int searchValueX, int searchValueY, const std::vector<int> &boxes)
{
	int same1 = 0; // both dogs start with first box
	int same2 = 0; // both dogs start with last box
	int diff1 = 0; // dog x starts with first box, dog y with last box
	int diff2 = 0; // dog y starts with first box, dog x with last box
	bool x_same1 = false;
	bool y_same1 = false;
	bool x_same2 = false;
	bool y_same2 = false;
	bool x_diff1 = false;
	bool y_diff1 = false;
	bool x_diff2 = false;
	bool y_diff2 = false;
	for (int i = 0; i < boxes.size(); i++) {
		
		// increment time for not yet successful ways
		if(!(x_same1 && y_same1))
			same1++;
		if(!(x_same2 && y_same2))
			same2++;
		if(!(x_diff1 && y_diff1))
			diff1++;
		if(!(x_diff2 && y_diff2))
			diff2++;
		
		// dog x starting with first box is successful
		if(searchValueX == boxes[i]) {
			x_same1 = true;
			x_diff1 = true;
		}
		
		// dog y starting with first box is successful
		if(searchValueY == boxes[i]) {
			y_same1 = true;
			y_diff2 = true;
		}
		
		// dog x starting with last box is successful
		if(searchValueX == boxes[boxes.size() - (i + 1)]) {
			x_same2 = true;
			x_diff2 = true;
		}
		
		// dog y starting with last box is successful
		if(searchValueY == boxes[boxes.size() - (i + 1)]) {
			y_same2 = true;
			y_diff1 = true;
		}	
	}

	// return minimum of 4 different ways if there is a successful way
	if((x_same1 && y_same1) || (x_same2 && y_same2) || (x_diff1 && y_diff1) || (x_diff2 && y_diff2))
		return std::min({same1, same2, diff1, diff2});
	return -1;
}

int main(int argc, char * argv[])
{
	if (argc < 3)
	{
		std::cout << "Missing parameters. Usage: <searchValue1> <searchValue2> [box1] [box2] [...]" << std::endl;
		return 0;
	}

	const int searchValueX = std::atoi(argv[1]);
	const int searchValueY = std::atoi(argv[2]);
	if(searchValueX < 1 || searchValueY < 1)
	{
		std::cerr << "Search values must be greater than zero!";
	}
	
	if (searchValueX == searchValueY)
	{
		std::cerr << "Search values must be different!";
		return 1;
	}

	std::vector<int> boxes;
	for (int i = 3; i < argc; i++)
	{
		int value = std::atoi(argv[i]);
		if (value < 1)
		{
			std::cerr << "Box value must be greater than zero!";
			return 2;
		}

		boxes.push_back(std::atoi(argv[i]));
	}

	int minTime = minTimeDogTraining(searchValueX, searchValueY, boxes);
	if (minTime == -1)
	{
		std::cout << "There exists no two boxes with the given search values!" << std::endl;
	}
	else
	{
		std::cout << "The coach will have to wait at least " << minTime << " seconds!" << std::endl;
	}
	
	return 0;
}