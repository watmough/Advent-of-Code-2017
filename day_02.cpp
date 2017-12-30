// Advent of Code 2017
// Day 2 - Corruption Checksum

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "reader.h"
using namespace std;

int main(int argc, char* argv[])
{
    ifstream ifs("day_02.inp",ifstream::in);
    vector<string> input = read_input(ifs);
    auto checksum{0}, divisor_sum{0}, num{0};
    for (auto row : input) {
        istringstream sstr(row);
        vector<int> ints{istream_iterator<int>(sstr),istream_iterator<int>()};
        checksum += *max_element(begin(ints), ints.end())-*min_element(begin(ints), ints.end());

        for (auto n : ints)
            for (auto t : ints)
                if (n>t && n%t==0)
                    divisor_sum += n/t;
    }
    std::cout << "Part 1: " << checksum << std::endl;
    std::cout << "Part 2: " << divisor_sum << std::endl;
    return 0;
}

/* 
Output:

PS C:\Workarea\Advent-of-Code-2017> .\a.exe
Part 1: 47623
Part 2: 312
PS C:\Workarea\Advent-of-Code-2017>
*/
