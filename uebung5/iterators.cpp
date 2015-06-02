#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

// function template for printing contents of containers to std::cout
template<class T>
void printContainer(T& container)
{
    std::cout << "{"; 
    for(auto element : container)
        std::cout << element << " ";
    std::cout << "}" << std::endl; 
}


// ToDo 5.1a - Merge front-back pairings of elements of inContainer into outContainer. Do *not* use the []-operator.
template<class T>
void front_back_pairing(T& inContainer, T& outContainer)
{
    // to do: merge front-back pairwise elements of inC into outC 
    auto itFront = inContainer.begin();
    auto itBack = inContainer.rbegin();
    for(int i=0; i<inContainer.size()/2; i++, ++itFront, ++itBack)
    {
        outContainer.push_back(*itFront);
        outContainer.push_back(*itBack);
    }
}

// ToDo 5.1b - Remove all duplicates from the given container. Do *not* use the []-operator.
template<class T>
void remove_duplicates(T& container)
{
    std::sort(container.begin(), container.end());
    auto last = std::unique(container.begin(), container.end());
    container.erase(last, container.end());
}

// 5.1b - Remove all duplicates from the given container. Use this variant if you want to use a special function to compare the elements.
template<class T, class Compare>
void remove_duplicates(T& container, Compare cmp)
{
    std::sort(container.begin(), container.end(), cmp);
    auto last = std::unique(container.begin(), container.end());
    container.erase(last, container.end());
}

// ToDo 5.1c - Expand the given container by inserting the numerical differences of each element to its neighbors. Do *not* use the []-operator.
template<class T>
void add_differences(T& container)
{
    // for empty containers: nothing to do
    if(container.size()==0) return;

    T helpContainer;
    auto it0 = container.begin();
    auto itL = container.end()-1;
    auto it = container.begin();
    for(auto it = container.begin(); it!=container.end(); ++it)
    {
        auto next = (it==itL) ? it0 : it+1; 
        auto prev = (it==it0) ? itL : it-1;
        helpContainer.push_back((*prev)-(*it));
        helpContainer.push_back(*it);
        helpContainer.push_back((*next)-(*it));
    }

    container.clear();
    std::copy(helpContainer.begin(), helpContainer.end(), std::back_inserter(container));
}

void testFrontBackPairingFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,12,13,14,15,16,17,18,19 };
    std::list<std::string> sampleDataString = { "Die", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung" };
    
    // test for integer vector
    std::vector<int> helpIntVector;
    front_back_pairing(sampleDataInt, helpIntVector);
    printContainer(sampleDataInt);
    printContainer(helpIntVector);
    
    // test for string list
    std::list<std::string> helpStringList;
    front_back_pairing(sampleDataString, helpStringList);
    printContainer(sampleDataString);
    printContainer(helpStringList);
}

void testRemoveDuplicateFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,10,13,14,15,15,15,18,19,12,11,17 };
    std::vector<std::string> sampleDataString = { "Die", "___", "eines", "ist", "Gebrauch", "der", "Sprache", "in", "sein", "Wortes", "Bedeutung", "Die", "ist", "blabla" };
    
    // test for integer vector
    printContainer(sampleDataInt);
    //remove_duplicates(sampleDataInt, std::less<int>() );
    remove_duplicates(sampleDataInt);
    printContainer(sampleDataInt);
    
    // test for string vector
    printContainer(sampleDataString);
    remove_duplicates(sampleDataString);
    printContainer(sampleDataString);
}

void testAddDifferenceFunctionality()
{
    // define sample data
    std::vector<int> sampleDataInt = { 10,11,14,16,1,18 };
    
    // test for integer vector
    printContainer(sampleDataInt);
    add_differences(sampleDataInt);
    printContainer(sampleDataInt);
}

int main(int argc, char** argv)
{
    testFrontBackPairingFunctionality();
    testRemoveDuplicateFunctionality();
    testAddDifferenceFunctionality();

    return 0;
}
