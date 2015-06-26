
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
<<<<<<< HEAD

    /*for(int i = 0; i < I.size(); i++)
    {
        os << "start: " << I[i].start << "end: " << I[i].end << std::endl;
    }
     os << std::endl;*/
    #if 1
	for(int i = 0; i < I.size(); i++)
    {
        os << "#" << I[i].index << ": ";
        if(I[i].index < 10) os << " "; // für die Formatierung
        os << "$";
        for(int j = 0; j < I[i].start; j++)
            os << ".";
        for(int j = I[i].start; j < I[i].end; j++)
            os << "|";
        for(int j = I[i].end; j < MaxEnd; j++)
            os << ".";
        os << "$" << std::endl;
    }
    #endif
=======
    
	//TODO 6.3 
	//Implement a nice print function
>>>>>>> e875ad5cb472aab845c24ef07d4e0eeb06366dec
	
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
<<<<<<< HEAD
    std::sort(sorted.begin(), sorted.end(),[](Interval &interval1, Interval &interval2){
        return interval1.end < interval2.end;
    });
=======
>>>>>>> e875ad5cb472aab845c24ef07d4e0eeb06366dec
    // sort intervals

    std::cout << std::endl << "intervals (sorted):" << std::endl << sorted;

    // scheduled
    
    auto scheduled = std::vector<Interval>();
<<<<<<< HEAD
    scheduled.push_back(sorted[0]); //erster Termin kann rein
    for(int i = 1; i < N; i++)
    {
        if(sorted[i].start >= scheduled[scheduled.size()-1].end)
            scheduled.push_back(sorted[i]);
    }
=======
>>>>>>> e875ad5cb472aab845c24ef07d4e0eeb06366dec
    
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