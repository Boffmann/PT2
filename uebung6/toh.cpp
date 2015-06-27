
#include <cassert>
#include <iostream>
#include <string>
#include <cstddef>
#include <vector>
#include <cstring>
#include <cmath>


static const auto N = 5;
//static const auto N = 4;

auto A = std::vector<int>();
auto B = std::vector<int>();
auto C = std::vector<int>();


void print()
{
    #ifdef _WIN32
    std::system("cls");
    #else
    std::system("clear");
    #endif

    //TODO 6.2
	//print state
    for(int i = N-1; i >= 0; --i)
    {
        std::cout << "              ";
        int index;
        if(i < A.size())
        index = A.at(i);
        else index = 0;
            
        for(int j = 0; j < (N * 2 - index * 2) / 2; j++) {
            std::cout << " ";
        }
        for(int j = 0; j < index * 2; j++) {
            std::cout << "_";
        }
        for(int j = 0; j < (N * 2 - index * 2) / 2; j++) {
            std::cout << " ";
        }

        std::cout << "              ";
        index;
        if(i < B.size())
        index = B.at(i);
        else index = 0;
            
        for(int j = 0; j < (N * 2 - index * 2) / 2; j++) {
            std::cout << " ";
        }
        for(int j = 0; j < index * 2; j++) {
            std::cout << "_";
        }
        for(int j = 0; j < (N * 2 - index * 2) / 2; j++) {
            std::cout << " ";
        }
        
        std::cout << "              ";
        index;
        if(i < C.size())
        index = C.at(i);
        else index = 0;
            
        for(int j = 0; j < (N * 2 - index * 2) / 2; j++) {
            std::cout << " ";
        }
        for(int j = 0; j < index * 2; j++) {
            std::cout << "_";
        }
        for(int j = 0; j < (N * 2 - index * 2) / 2; j++) {
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void ToH(int n, int a, int b, int c, int & moves) 
{
    int element;
    //TODO 6.2
	//Implement Towers of Hanoi and print
    if(n==1)  {
        char from = (char)('A'+a);
        char to = (char)('A'+c);
        std::cout << "Move " << from << " -> " << to << std::endl;
        if(from == 'A' && to == 'B') {
            auto it = A.end();
            auto it2 = B.end();
            auto insert = B.begin();
            element = *(it-1);
            if(B.size() == 0) {
                A.pop_back();
                B.push_back(element);
                //B.insert(insert, element);
            } else if(element < *(it2-1)) {
                A.pop_back();
                B.push_back(element);
                //B.insert(insert, element);
            }
        }
        //von b nach a
        else if(from == 'B' && to == 'A') {
            auto it = B.end();
            auto it2 = A.end();
            auto insert = A.begin();
            element = *(it-1);
            if(A.size() == 0) {
                B.pop_back();
                A.push_back(element);
                //A.insert(insert, element);
            }
            else if(element < *(it2-1)) {
                B.pop_back();
                A.push_back(element);
                //A.insert(insert, element);
            }   
        }
        //von a nach c
        else if(from == 'A' && to == 'C') {
            auto it = A.end();
            auto it2 = C.end();
            auto insert = C.begin();
            element = *(it-1);
            if(C.size() == 0) {
                A.pop_back();
                C.push_back(element);
                //C.insert(insert, element);
            }
            else if(element < *(it2-1)) {
                A.pop_back();
                C.push_back(element);
                //C.insert(insert, element);
            }  
        }
        //von c nach a
        else if(from == 'C' && to == 'A') {
            auto it = C.end();
            auto it2 = A.end();
            auto insert = A.begin();
            element = *(it-1);
            if(A.size() == 0) {
                C.pop_back();
                A.push_back(element);
                //A.insert(insert, element);
            }
            else if(element < *(it2-1)) {
                C.pop_back();
                A.push_back(element);
                //A.insert(insert, element);
            }  
        }
        //von b nach c
        else if(from == 'B' && to == 'C') {
            auto it = B.end();
            auto it2 = C.end();
            auto insert = C.begin();
            element = *(it-1);
            if(C.size() == 0) {
                B.pop_back();
                C.push_back(element);
                //C.insert(insert, element);
            }
            else if(element < *(it2-1)) {
                B.pop_back();
                C.push_back(element);
                //C.insert(insert, element);
            }   
        }
        //von c nach b
        else if(from == 'C' && to == 'B') {
            auto it = C.end();
            auto it2 = B.end();
            auto insert = B.begin();
            element = *(it-1);
            if(B.size() == 0) {
                C.pop_back();
                B.push_back(element);
                //B.insert(insert, element);
            }
            else if(element < *(it2-1)) {
                C.pop_back();
                B.push_back(element);
                //B.insert(insert, element);
            }
        }   
        getchar();
        print();
    } else {
        moves++;
        ToH(n-1, a, c, b, moves); 
        ToH(1, a, b, c, moves);
        ToH(n-1, b, a, c, moves); 
    }  
}  

int main(int argc, char ** argv) 
{
    int moves = 0;

    for (int i = N; i > 0; --i)
        A.push_back(i);

	print();
	getchar();
    ToH(N, 0, 1, 2, moves);
    std::cout << "minimal number of moves: " << moves << std::endl;

	getchar();
    return 0;
}
