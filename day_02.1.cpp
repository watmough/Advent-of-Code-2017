// Advent of Code 2017
// Day 2 - Corruption Checksum Part 1

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits.h>
using namespace std;

int main(int argc, char* argv[])
{
    auto row = string();
    auto num{0}, check{0};
    while (getline(cin,row) && row.length()>0) {
        stringstream str(row);
        int min{INT_MAX};
        int max{INT_MIN};
        while (str >> num) {
            min = std::min(min,num);
            max = std::max(max,num);
        }
        check += max-min;
    }
    std::cout << "Checksum is " << check << std::endl;
    return 0;
}
