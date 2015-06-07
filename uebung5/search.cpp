#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

struct Route
{
	int airlineId;
	int sourceId;
	int destinationId;
};

bool operator<(const Route& r1, const Route& r2) {
	return r1.destinationId < r2.destinationId;
}

bool operator==(const Route& r1, const Route& r2) {
	return r1.destinationId == r2.destinationId;
}

void importRoutesData(char* path, std::vector<Route>& routes)
{
	std::cout << "Importing routes data.." << std::endl;
	std::ifstream file(path);
	std::string field, line;
	
	while (std::getline(file, line))
	{
		std::istringstream linestream;
		linestream.str(line);
		int fieldNum = 0;
		Route route;
		route.airlineId = route.sourceId = route.destinationId = -1;

		while (std::getline(linestream, field, ';'))
		{
			try
			{
				switch (fieldNum)
				{
					case 1: // airline id
						route.airlineId = std::stoi(field);
						break;
					case 3: // source id
						route.sourceId = std::stoi(field);
						break;
					case 5: // dest id
						route.destinationId = std::stoi(field);
						break;
					default:
						break;
				}
			}
			catch (const std::invalid_argument&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (invalid argument)!" << std::endl;
				//std::cout << field << std::endl;
			}
			catch (const std::out_of_range&)
			{
				//std::cout << "Couldn't convert field " << currentLineNum << " correctly (out of range)!" << std::endl;
				//std::cout << field << std::endl;
			}

			fieldNum++;
		}

		if (route.airlineId > -1 && route.sourceId > -1 && route.destinationId > -1)
			routes.push_back(route);
	}
}

// ToDo 5.2a - Return the number of routes for the given destination id based on a linear search. Count the number of lookups.
int linearSearch(int destID, std::vector<Route>& routes, long long& numLookups)
{
	int numRoutes = 0;
	for(auto it = routes.begin(); it != routes.end(); ++it) {
		numLookups++;
		if((*it).destinationId == destID)
			numRoutes++;			
	}

	return numRoutes;
}

// ToDo 5.2a - Evaluate the linearSearch function by calling it for every possible destination id (1..9541). 
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
std::pair<long long, long long> evaluateLinearSearch(std::vector<Route>& routes)
{
	long long numLookups = 0;
	long long duration = 0;
	long long counter = 0;

	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i <= 954; i++)
	{
		counter += linearSearch(i, routes, numLookups);
	}
	auto time_needed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count() ;
	duration = (long long) time_needed;

	std::cout << "Linear Search: " << counter << std::endl;

	return std::make_pair(numLookups, duration);
}

// ToDo 5.2b - Return the number of routes for the given destination id based on a binary search. Count the number of lookups.
// The vector should have been sorted before calling this function.
int binarySearch(int destID, std::vector<Route>& routes, long long& numLookups)
{
	int numRoutes = 0;
	int a = 0;
	int b = routes.size()-1;

	while(a<b){
		numLookups ++;
		int m = (int)((a+b)/2);
		if(routes[m].destinationId == destID)
		{
			//std::cout << m << std::endl;
			int i = m;
			while(routes[i].destinationId == destID)
			{
				numRoutes++;
				i++;
			}
			return numRoutes;
		}
		else if(routes[m].destinationId < destID)
			a = m+1;
		else
			b = m-1;
	}
}

// ToDo 5.2b - Evaluate the binarySearch function by calling it for every possible destination id (1..9541). 
// Return the number of lookups and the processing time as a pair of long longs.
// Use std::chrono for time measurement.
// Attention: sorting is *not* part of the evaluation and should be conducted beforehand.
std::pair<long long, long long> evaluateBinarySearch(std::vector<Route>& routes)
{
	long long numLookups = 0;
	long long duration = 0;
	long long counter = 0;

	std::sort(routes.begin(), routes.end(), [](Route &r1, Route &r2){
		return r1 < r2;
	});

	auto start = std::chrono::high_resolution_clock::now();
	for(int i = 0; i <= 954; i++)
	{
		counter += binarySearch(i, routes, numLookups);
	}
	auto time_needed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count() ;
	duration = (long long) time_needed;
	std::cout << "Binary Search: " << counter << std::endl;

	return std::make_pair(numLookups, duration);
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: sort [ROUTE DATASET]" << std::endl;
		return -1;	// invalid number of parameters
	}

	static std::vector<Route> routes;

	std::cout << "Given path to routes.csv: " << argv[1] << std::endl;

	importRoutesData(argv[1], routes);

	auto result = evaluateLinearSearch(routes);
	std::cout << result.first << " - " << result.second << std::endl;
	result = evaluateBinarySearch(routes);	
	std::cout << result.first << " - " << result.second << std::endl;
	
	return 0;
}
