// day04.cpp : Defines the entry point for the console application.
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

int main(int argc, char* argv[])
{
	int validcount = 0;
	std::string row;
	while (std::getline(std::cin,row) && row.length()>0) {
		std::stringstream str(row);
		std::vector<std::string> words;
		std::string pass;
		bool INVALID = false;
		while (str >> pass) {
			// Uncomment to sort individual words, so we catch 'anagrams'
			//std::sort(pass.begin(),pass.end());
			if (std::find(words.begin(),words.end(),pass)==words.end()) {
				// push back any words we don't already have
				words.push_back(pass);
			} else {
				// we found a repeated word, INVALID
				std::cout << pass << " invalid on " << row << std::endl;
				INVALID=true;
			}
		}
		// 
		if (!INVALID)
			validcount++;
	}
	std::cout << "Valid count is " << validcount << std::endl;
	return 0;
}
