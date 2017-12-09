// Advent of Code 2017
// Day 2 - Corruption Checksum Part 1

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

int main(int argc, char* argv[])
{
    std::string row;
    int num = 0;
    int check = 0;
    while (std::getline(std::cin,row) && row.length()>0) {
        std::stringstream str(row);
        int min = INT_MAX;
        int max = INT_MIN;
        while (str >> num) {
            min = std::min(min,num);
            max = std::max(max,num);
        }
        check += max-min;
    }
    std::cout << "Checksum is " << check << std::endl;
    return 0;
}
