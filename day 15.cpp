// Advent of Code 2017
// Day 15 - Dueling Generators

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
    unsigned long long int a{ 699 }, b{ 124 };
    int match{ 0 };
    for (auto i{ 0 }; i < 40000000; ++i) {
        a = (a * 16807ll) % 2147483647ll;
        b = (b * 48271ll) % 2147483647ll;
        if ((a&0xffff) == (b&0xffff))
            match++;
    }
    cout << "Part 1: " << match << " matches." << endl;
    a = 699, b = 124, match = 0;
    for (auto i{ 0 }; i < 5000000; ++i) {
        do a = (a * 16807ll) % 2147483647ll; while (a % 4);
        do b = (b * 48271ll) % 2147483647ll; while (b % 8);
        if ((a & 0xffff) == (b & 0xffff))
            match++;
    }
    cout << "Part 2: " << match << " matches." << endl;
    return 0;
}
