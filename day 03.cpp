// day3.cpp : Defines the entry point for the console application.
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <map>

// track spiral totals in part 2
std::map<std::string,int> sum;

// x,y -> "x,y" 
std::string idx(int x,int y)
{
	std::string idx = std::to_string((long long)x);
	idx.push_back(',');
	idx.append(std::to_string((long long)y));
	return idx;
}

// lookup a sum at cell x,y
int lookup(int x, int y)
{
	std::string id = idx(x,y);
	if (sum.find(id)!=sum.end())
		return sum[id];
	return 0;
}

// sum the 8 neighbors of x,y and save it
int save_sum(int x,int y)
{
	int tot = 0;
	tot += lookup(x-1,y-1);
	tot += lookup(x,y-1);
	tot += lookup(x+1,y-1);
	tot += lookup(x-1,y+1);
	tot += lookup(x,y+1);
	tot += lookup(x+1,y+1);
	tot += lookup(x-1,y);
	tot += lookup(x+1,y);

	sum[idx(x,y)] = tot;
	std::cout << tot << std::endl;
	return tot;
}

// given a value, do spiral enwwsseeennn... etc. summing the 8 neighbors as we go
// find the first value higher than the problem input
int main2(int argc, char* argv[])
{
	sum[idx(0,0)] = 1;

	std::cout << "Enter a value for part 2" << std::endl;
	int val;
	std::cin >> val;

	int x=0, y=0;
	int count = 0;
	while(1) {
		// move east
		count++;
		for (int i=0;i<count;i++) {
			x++;
			if (val<save_sum(x,y))
				goto done;
		}
		// move north
		for (int i=0;i<count;i++) {
			y++;
			if (val<save_sum(x,y))
				goto done;
		}
		// move west
		count++;
		for (int i=0;i<count;i++) {
			x--;
			if (val<save_sum(x,y))
				goto done;
		}
		// move south
		for (int i=0;i<count;i++) {
			y--;
			if (val<save_sum(x,y))
				goto done;
		}
	}
done:
	std::cin >> val;
	return 0;
}

// part 1 given a spiral starting at 1, calculate the manhattan distance back
// to the center from the problem input.
// I used the following for some clues http://mathforum.org/library/drmath/view/62201.html
// then hack hack hack...
int main1(int argc, char* argv[])
{
	int val;
	std::cout << "Enter a value (or -1 to quit part 1)" << std::endl;
	while (1) {
		std::cin >> val;
		if (val==-1)
			break;
		int side = 1;
		int count = 1;
		int inner = 0;
		int pos = 0;
		int of = 0;
		int dist = 0;
		int rings = 1;

		do {									// iterate til we get a big enough ring
			side += 2;
			count = side*side;
			rings++;
		} while (count<val);
		inner = side>1 ? (side-2)*(side-2) : 0;	// count of cells inside the ring
		pos = ((val-inner)+side/2)%(side-1);	// distance away from the 12pm 3pm 6pm 9pm positions
		of = (side-1)*(side-1);					// unused - cells in this ring
		dist = pos + rings-1;					// total manhattan distance

		std::cout << "Rings " << rings << std::endl;
		std::cout << "Side  " << side << std::endl;
		std::cout << "Pos   " << pos << std::endl;
		std::cout << "Of    " << of << std::endl;
		std::cout << "Dist  " << dist << std::endl;
	};
	return 0;
}

int main(int argc, char* argv[])
{
	main1(argc,argv);
	main2(argc,argv);
}
