#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <random>
#include <algorithm>
#include <iterator>
#include <limits>
#include <string>
#include <ctime>

using namespace std;

// array printing
ostream& operator<<(ostream& os, const vector<int>& A) {
    os << A[0];
    for(int i=1; i<A.size(); ++i) os << "," << A[i];
    return os;
}

// random number in [a,b] range
inline float frand(float a, float b) {
    return a+((b-a) * (float)rand() / (float)RAND_MAX);
}


// tour set and tour definitions
const int N = 20;  // length of sequence, i.e., number of cities
const vector<int> NullTour(N, -1);
const int M = 20; // population size per generation, i.e., no of tours
int minDist = numeric_limits<int>::max(); // globale minimum of tour length, over all generations
int maxDist = numeric_limits<int>::min(); // globale maximum of tour length, over all generations


// ok, real data for N=20 (German city distances)
const vector<string> cityName {
    "Berlin", "Hamburg", "München", "Köln", "Frankfurt am Main", "Stuttgart", "Düsseldorf", "Dortmund", "Essen", "Bremen", "Dresden", "Leipzig", "Hannover", "Nürnberg", "Duisburg", "Bochum", "Wuppertal", "Bielefeld", "Bonn", "Münster"
};

const int distance_table[N][N] = {
	{000, 255, 504, 477, 424, 512, 477, 422, 453, 315, 165, 149, 249, 378, 471, 439, 452, 336, 479, 398}, 
	{255, 000, 612, 356, 393, 534, 338, 284, 308, 95, 377, 294, 132, 462, 321, 297, 320, 196, 370, 237}, 
	{504, 612, 000, 456, 304, 190, 486, 477, 493, 582, 359, 360, 488, 150, 503, 486, 470, 483, 433, 510}, 
	{477, 356, 456, 000, 152, 288, 34, 72, 57, 269, 474, 380, 249, 336, 56, 62, 37, 162, 25, 123}, 
	{424, 393, 304, 152, 000, 152, 182, 177, 190, 329, 371, 293, 261, 187, 200, 184, 167, 212, 131, 218}, 
	{512, 534, 190, 288, 152, 000, 322, 328, 335, 478, 412, 364, 401, 157, 342, 332, 311, 364, 264, 371}, 
	{477, 338, 486, 34, 182, 322, 000, 57, 30, 248, 485, 389, 240, 363, 23, 41, 26, 150, 59, 101}, 
	{422, 284, 477, 72, 177, 328, 57, 000, 32, 196, 439, 340, 182, 343, 49, 17, 36, 93, 90, 51}, 
	{453, 308, 493, 57, 190, 335, 30, 32, 000, 217, 470, 371, 212, 364, 18, 14, 24, 122, 81, 70}, 
	{315, 95, 582, 269, 329, 478, 248, 196, 217, 000, 405, 310, 100, 433, 229, 207, 231, 118, 285, 150}, 
	{165, 377, 359, 474, 371, 412, 485, 439, 470, 405, 000, 100, 312, 259, 487, 456, 460, 375, 467, 434}, 
	{149, 294, 360, 380, 293, 364, 389, 340, 371, 310, 100, 000, 214, 229, 389, 358, 363, 275, 375, 334}, 
	{249, 132, 488, 249, 261, 401, 240, 182, 212, 100, 312, 214, 000, 338, 229, 199, 217, 90, 258, 151}, 
	{378, 462, 150, 336, 187, 157, 363, 343, 364, 433, 259, 229, 338, 000, 377, 355, 343, 337, 318, 370}, 
	{471, 321, 503, 56, 200, 342, 23, 49, 18, 229, 487, 389, 229, 377, 000, 32, 33, 138, 81, 84}, 
	{439, 297, 486, 62, 184, 332, 41, 17, 14, 207, 456, 358, 199, 355, 32, 000, 26, 109, 84, 61}, 
	{452, 320, 470, 37, 167, 311, 26, 36, 24, 231, 460, 363, 217, 343, 33, 26, 000, 128, 58, 85}, 
	{336, 196, 483, 162, 212, 364, 150, 93, 122, 118, 375, 275, 90, 337, 138, 109, 128, 000, 175, 62}, 
	{479, 370, 433, 25, 131, 264, 59, 90, 81, 285, 467, 375, 258, 318, 81, 84, 58, 175, 000, 142}, 
	{398, 237, 510, 123, 218, 371, 101, 51, 70, 150, 434, 334, 151, 370, 84, 61, 85, 62, 142, 000}
};

// check if a tour is completely defined
bool tourDefined(const vector<int>& tour) {
    // all tours have N distinct cities
    // if a tour has undefined slots, they are marked by -1
    for(int i=0; i<N; ++i) {
        if(tour[i]==-1) return false;
    }
    return true;
}

// check if city is in tour
bool findCity(const vector<int>& tour, int city) {
    assert(city>=0 && city<N);
    assert(tour.size()==N);
    
    // a valid tour always returns true as the tour must include all cities
    // during evolution, tours temporarily have undefined slots, so this is way we need that function
    for(int i=0; i<N; ++i) {
        if(tour[i]==city) return true;
    }
    return false;
}

// check that all cities are included in a complete tour
bool validTour(const vector<int>& tour) {
    for(int i=0; i<N; ++i) {
        if(!findCity(tour, i)) return false;
    }
    return true;
}

// ToDo : returns distance between two cities based on the distance table
int cityDistance(int city1, int city2) {
    //ToDo : useful assertion check

    assert(city1 != city2);
    assert(city1 >= 0 && city1 < N);
    assert(city2 >= 0 && city2 < N);
    


	return distance_table[city1][city2]; 
}

// ToDo: calculate the lenth for a given tour, assuming a round trip
int tourLength(const vector<int>& T) {
	//ToDo : useful assertion check

    assert(tourDefined(T));
    assert(validTour(T));

    int temp = 0;
    for(int i = 0;i<N-1;i++)
    {
        temp+=cityDistance(T[i], T[i+1]);
    }
    temp+=cityDistance(T[N-1], T[0]);

    if(temp > maxDist)
        maxDist = temp;
    if(temp < minDist)
        minDist = temp;
    

    return temp;
}

//  print city names of a tour
void printTourCityNames(const vector<int>& T) {
    assert(validTour(T));
    for(int i=0; i<N; ++i) cout << (i==0 ? "" : "-") << cityName[T[i]];
    cout << endl;
}


// ToDo: inserts a city in an incomplete tour, using the next free slot
void insertCity(vector<int>& tour, int city) {
    assert(city >= 0 && city<N);
    assert(tour.size() == N);
    for(int i = 0;i<N;i++)
    {
        if(tour[i] == -1)
            {
                tour[i] = city;
                return;
            }

    }
    //assert(false);
}


// ToDo: Generate the tours as initial population and store them in the tour set. Hint: use std::shuffle.
void generateTours(vector< vector<int> >& tourSet) {
    static std::random_device rd;
    static std::mt19937 g(rd());

    for(auto& T : tourSet)
    {
        for(int i = 0;i<N;i++)
        {
            T[i] = i;
        }
        std::shuffle(T.begin(), T.end(), g);
        assert(tourDefined(T));
        assert(validTour(T));
    }
}

// ToDo: take two (good) parent tours, and build a new one by the gens of both. Hint: Use rand, findCity and insertCity.
void crossover(const vector<int>& parent1, const vector<int>& parent2, vector<int>& child) {

    for(int i = 0;i <= N; i++)
        child[i] = -1;

    int a = 0 + (rand() % N-5);
    int b = a + 5;

    for(int i = a; i<=b;i++)
        child[i] = parent1[i];
    for(int i = 0; i<N;i++)
    {
        int temp = parent2[i];
        if(!findCity(child, temp))
            insertCity(child, temp);
    }

    assert(tourDefined(child));
    assert(validTour(child));

}

// ToDo: Mutate a given tour, swapping cities randomly based on probability. Hint: Use frand and std::swap.
void mutate(vector<int>& tour) {
    const float mutationProbability = 0.02f; // x% probability per city in a tour to get mutated
    for(int i = 0;i<N;i++)
    {
        if(frand(0,1) < mutationProbability)
        {
            int j = (int)(frand(0,N-1));
            swap(tour[i],tour[j]);
        }
    }

}

// ToDo: Create a sorted sequence of (tour length, tour index) pairs (ascending order, i.e., the shorter, the better)
vector<pair<int,int>> fitness(vector<vector<int>>& tourSet) {
    vector<pair<int,int>> Check(M);

	for(int i = 0;i<M;i++)
    {
        Check[i] = std::make_pair(tourLength(tourSet[i]),i);
    }
    sort(Check.begin(), Check.end(), [](pair<int, int> p1, pair<int, int> p2){return p1.first < p2.first;});

    return Check;
}

// evolution step: transform the tour set into the next generation tour set
pair<int,int> evolution(vector<vector<int>>& tourSet, bool elite) {
    assert(tourSet.size()==M);
    pair<int,int> statistics; // used as return values (min/max tour lengths)
    
	// compute fitness of tours, store shortest and largest tour length in statistics
    auto F = fitness(tourSet);
    statistics.first = F[0].first; // tour with shortest tour length
    statistics.second = F[M-1].first; // tour with largest tour length
    
	// ToDo: compute crossover of two best tours and replace worst tour by the crossover. Use the crossover method.
    crossover(tourSet.at(F[0].second), tourSet.at(F[1].second) ,tourSet.at(F[M-1].second));

	// ToDo: Mutate all other tours (ignore two best trips and the former worst trip (replaced)). Use the mutate method.
    for(auto i = 2;i<M-1;i++)
    {
        mutate(tourSet.at(i));
    }

	return statistics;
 }


int main(int argc, char** argv) {
    // reset random generator
    srand((unsigned int)time(0));
    
    // report shortest/longest tour length for each evolution iteration in a csv file
    std::ofstream stats("output.csv", std::ios::binary);
    stats << "min tour length" << "; " << "max tour length" << endl;
    
    // generate randomly a tour set with M tours, each one between N cities
    vector<vector<int>> TourSet(M, NullTour);
    generateTours(TourSet);
    
    // do a fixed number of evolution steps
    for(int e=0; e<1000; e++) {
        auto lengths = evolution(TourSet, false);
        
        // report statistics
        stats << lengths.first << "; " << lengths.second <<endl;
    }
    
    // after evolution iterations, log on last tour
    auto FE = fitness(TourSet);
    cout << "final shortest trip:  " << FE[0].first << "km" << endl;
    //printTourCityNames(TourSet[FE[0].second]);
    cout << "over all generations, min dist = " << minDist << ", max dist = " << maxDist << endl;
    
    // close the log file (use excel to visualize data)
    stats.close();
    
    return 0;
}

