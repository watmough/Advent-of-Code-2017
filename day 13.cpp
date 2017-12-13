// Advent of Code 2017
// Day 13 - Packet Scanners

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
    int depth, range;
    vector<int> depths, ranges, severity;
    while (cin >> depth) {
        if (cin.peek() == ':') cin.get();
        cin >> range;
        depths.push_back(depth);
        ranges.push_back(range);
    }

    int delay = 0;
    while (1) {
        int severity{ 0 };
        for (int step = 0; step<depths.size(); ++step) {
            // move player
            severity += ((depths[step] + delay) % ((ranges[step] - 1) * 2)) == 0 ? max(1,depths[step] * ranges[step]) : 0;
        }
        if (severity == 0 ) break;
        if (delay == 0) cout << "Part 1: " << severity - 1 << endl;
        delay++;
    }
    cout << "Part 2: " << delay << endl;
    return 0;
}

/*
Output:
Part 1: 1640
Part 2: 3960702

*/
