// aoc002a_checksum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

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
