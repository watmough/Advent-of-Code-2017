// Advent of Code 2017
// Day 13 - Packet Scanners

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

int main(int argc, char* argv[])
{
    int depth, range;
    vector<int> depths, ranges;
    while (cin >> depth) {
        if (cin.peek() == ':') cin.get();
        cin >> range;
        depths.push_back(depth);
        ranges.push_back(range);
    }

    int severity{ 0 };
    for (int step = 0; step<depths.size(); ++step) {
        severity += (depths[step] % ((ranges[step] - 1) * 2))==0 ? (depths[step]*ranges[step]) : 0;
    }
    cout << "Part 1: " << severity << endl;

    auto start = std::chrono::high_resolution_clock::now();
    auto delay{ 0 }, fail{ 0 };
    for (;; ++delay) {
        fail = 0;
        for (auto step{ 0 }; fail == 0 && step < depths.size(); ++step)
            fail = !((depths[step] + delay) % ((ranges[step] - 1) * 2));
        if (fail == 0) break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Part 2: " << delay << " in " << elapsed_seconds.count()*1000 << " msec" << endl;
    return 0;
}

/*
Output:
Part 1: 1640
Part 2: 3960702 in 49.2783 msec
*/
