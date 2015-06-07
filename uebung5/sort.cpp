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
	T tmp_mid = midIt;
	int counter = 0;
	std::vector<typename T::value_type> mergedValues(rightIt - leftIt);
	while(leftIt != tmp_mid && midIt != rightIt) {
		std::cout << "left: " << *leftIt << " mid: " << *midIt << " min: " << std::min(*leftIt, *midIt) << std::endl;
		if(std::min(*leftIt, *midIt) == (*leftIt)) {
			mergedValues.at(counter) = *leftIt;
			++counter;
			++leftIt;
			printContainer(mergedValues);
		} else {
			mergedValues.at(counter) = *midIt;
			++counter;
			++midIt;
			printContainer(mergedValues);
		}
	}
	while(leftIt != tmp_mid) {
			mergedValues.at(counter) = *leftIt;
			++counter;
			++leftIt;
			printContainer(mergedValues);
	}
	while(midIt != rightIt) {
			mergedValues.at(counter) = *midIt;
			++counter;
			++midIt;
			printContainer(mergedValues);
	}
	std::cout << "end: ";
	printContainer(mergedValues);
	std::cout << std::endl;
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
	//std::cout << cnt << " " << *leftIt << " " << *(rightIt-1) << std::endl;
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
#if 0
	// test for string vector
	printContainer(sampleDataString);
	mergeSort(sampleDataString.begin(), sampleDataString.end());
	printContainer(sampleDataString);
#endif
	return 0;
}
