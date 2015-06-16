
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>


struct Interval
{
    Interval(const int i, const int start, const int length) 
    : index(i)
    , start(start)
    , end(start + length)
    { 
    }

    int index;
    int start;
    int end;
};

const static int MaxEnd = 74;
const static int MaxDuration = 10;

const static int N = 20;

std::ostream & operator<<(std::ostream & os, const std::vector<Interval> & I) 
{
	os << I.size() << std::endl;
    
	//TODO 6.3 
	//Implement a nice print function
	
	return os;
}

//creates data
void randomize(std::vector<Interval> & intervals)
{
    intervals.clear();
    srand(time(0));

    for (int i = 0; i < N; i++)
    {
        int duration = rand() % MaxDuration + 1;
        int start = rand() % (MaxEnd - duration);

        intervals.push_back(Interval(i, start, duration));
    }
}


void schedule(const std::vector<Interval> & intervals)
{
    // unsorted

    std::cout << std::endl << "intervals (randomized):" << std::endl << intervals;

    // ToDo: Exercise 6.3 - sort and schedule intervals

	auto sorted = intervals;
    // sort intervals

    std::cout << std::endl << "intervals (sorted):" << std::endl << sorted;

    // scheduled
    
    auto scheduled = std::vector<Interval>();
    
    //ToDo 6.3
	//implement greedy scheduling

    std::cout << std::endl << "intervals (scheduled, " << scheduled.size() << " of " << sorted.size() << " possible)" 
        << std::endl << scheduled << std::endl;
}

int main(int argc, char** argv) {

    auto intervals = std::vector<Interval>();

    randomize(intervals);
    schedule(intervals);

    return 0;
}