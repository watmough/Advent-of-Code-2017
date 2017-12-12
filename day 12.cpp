// Advent of Code 2017
// http://adventofcode.com/
// Day 12 - Digital Plumber

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

void mergeprogram(int program, map<int, set<int>>& groups)
{
    set<int> childs = groups[program];
    for (auto it = begin(childs); it != end(childs); ++it) {
        if (program == *it) continue;
        if (groups.find(*it) != groups.end()) {
            groups[program].insert(begin(groups[*it]), end(groups[*it]));
            groups.erase(*it);
            mergeprogram(program, groups);
        }
    }
}

int main()
{
    string line;
    map<int, set<int>> groups;
    vector<int> inter(2048);
    int program;
    string delim;

    while (getline(cin, line)) {
        set<int> programs;
        stringstream row(line);
        row >> program >> delim;
        int linked;
        programs.insert(program);
        while (row >> linked) {
            programs.insert(linked);
            if (row.peek()==',')
                row.get();
        }
        groups[program] = programs;
    }

    for (auto pr = begin(groups); pr != end(groups); ++pr) {
        mergeprogram((*pr).first, groups);
    }
    cout << "Group 0 is: " << groups[0].size() << endl;
    cout << "There are : " << groups.size() << " groups" << endl;
    return 0;
}

/*
C:\Workarea\AOC2017\day 12\x64\Debug>"day 12.exe" < input.txt
Group 0 is: 145
There are : 207 groups

C:\Workarea\AOC2017\day 12\x64\Debug>
*/
