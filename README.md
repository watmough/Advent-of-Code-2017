# Advent-of-Code-2017

### Day 4 - Passphrases

This one was easy. 

```C++
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
```

### Day 3 - Another Crack at This!

Code for [Day 03.cpp](https://raw.githubusercontent.com/watmough/Advent-of-Code-2017/master/day%2003.cpp)

Here is the code:
```C++
// day3_redo.cpp : Defines the entry point for the console application.
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <map>

typedef enum dir {e=0,n,w,s} direction;
direction next_dir[] = {n,w,s,e};
direction d=e;
int x=0, y=0, count=1, done=0;

// kinda ugly generator of spiral coords
void next_coord(int& x, int&y)
{
	x += d==e ? 1 : (d==w) ? -1 : 0;		// east or west
	y += d==n ? 1 : (d==s) ? -1 : 0;		// north or south
	if (++done==count) done=0;				// moved required number of spots
	if (!done && (d==n || d==s)) count++;	// bump count on n or s
	if (!done) d = next_dir[d];				// switch direction
}

// get a value and iterate through the spiral, counting the x,y
// distance is then just abs(x)+abs(y)
int main1(int argc, char* argv[])
{
	std::cout << "Enter value (-1 to quit part 1)" << std::endl;
	int val;
	while (1) {
		std::cin >> val;
		if (val==-1) break;
		for (int i=1; i<val; ++i) {
			next_coord(x,y);
		}
		std::cout << "Distance is " << abs(x)+abs(y) << std::endl;
	}
	return 0;
}

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
	int tot=lookup(x-1,y-1)+lookup(x,y-1)+lookup(x+1,y-1)+lookup(x-1,y+1)+lookup(x,y+1)+lookup(x+1,y+1)+lookup(x-1,y)+lookup(x+1,y);
	return (sum[idx(x,y)]=tot);
}

int main2(int argc, char* argv[])
{
	sum[idx(0,0)] = 1;

	std::cout << "Enter value (-1 to quit part 2)" << std::endl;
	int val,sum;
	while (1) {
		std::cin >> val;
		if (val==-1) break;

		d=e, x=0, y=0, count=1, done=0;
		do {
			next_coord(x,y);
			sum = save_sum(x,y);
		} while (sum<=val);

		std::cout << "Value is " << sum << std::endl;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	main1(argc,argv);
	main2(argc,argv);
}
```

Here is the output:

```
Enter value (-1 to quit part 1)
347991
Distance is 480
-1
Enter value (-1 to quit part 2)
347991
Value is 349975
```

### Day 3 - Memory Spirals

I had a horrible time with this. I stayed up late, then was too tired, and gave up
after an hour.

Came back this morning and made some pretty ugly C++ to solve parts 1 + 2. 

Here's the code:
```C++
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
```
Here's the output:

```
Enter a value (or -1 to quit part 1)
347991
Rings 296
Side  591
Pos   185
Of    348100
Dist  480
-1
Enter a value for part 2
347991
...output redacted...
349975
```
 
