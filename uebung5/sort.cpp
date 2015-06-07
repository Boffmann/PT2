#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
	std::cout << "{";
	for (auto element : container)
		std::cout << element << " ";
	std::cout << "}" << std::endl;
}

// ToDo 5.3 - Merge the given lists [leftIt..midIt) and [midIt..rightIt)
template<class T>
void merge(T leftIt, T midIt, T rightIt)
{
	assert(leftIt <= midIt && midIt <= rightIt);

	//temp attributes for sorting the vector
	T left = leftIt;
	T mid = midIt;
	std::vector<typename T::value_type> mergedValues(rightIt - leftIt);
	auto vector_it = mergedValues.begin();
	
	// while both sides not empty
	while(left != midIt && mid != rightIt) {

		// add smaller of both first elements to vector
		if(std::min(*left, *mid) == (*left)) {
			(*vector_it) = *left;
			++vector_it;
			++left;
		} else {
			(*vector_it) = *mid;
			++vector_it;
			++mid;
		}
	}

	// left side not yet empty
	while(left != midIt) {
			(*vector_it) = *left;
			++vector_it;
			++left;
	}

	// right side not yet empty
	while(mid != rightIt) {
			(*vector_it) = *mid;
			++vector_it;
			++mid;
	}

	// copy sorted data to pointers
	vector_it = mergedValues.begin();
	while(leftIt != rightIt) {	
		(*leftIt) = *vector_it;
		++vector_it;
		++leftIt;
	}
}

// ToDo 5.3 - Sort the given container using merge sort.
template<class T>
void mergeSort(T leftIt, T rightIt)
{
	assert(leftIt < rightIt);
	T tmp = leftIt;
	int cnt = 0;
	while(tmp != rightIt){
		tmp++;
		cnt++;
	}
	cnt /= 2;
	tmp = leftIt;
	for (int i = 0; i < cnt; ++i) {
		tmp++;
	}
	T mid = tmp;
	if(leftIt != rightIt-1) {
		mergeSort(leftIt, mid);
		mergeSort(mid, rightIt);
	}
	merge(leftIt, mid, rightIt);
}

int main(int argc, char** argv)
{
	// define sample data
	std::vector<int> sampleDataInt = { 10, 1, 12, 33, 24, 5, 6, -7, -2, 19 };
	std::vector<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };

	// test for integer vector
	printContainer(sampleDataInt);
	mergeSort(sampleDataInt.begin(), sampleDataInt.end());
	printContainer(sampleDataInt);

	// test for string vector
	printContainer(sampleDataString);
	mergeSort(sampleDataString.begin(), sampleDataString.end());
	printContainer(sampleDataString);

	return 0;
}
