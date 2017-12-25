// Advent of Code 2017
// http://adventofcode.com/
// Day 11 - Hex Ed

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;


/* Reduction Rules

fwd back
s   n  -> o
se  nw -> o	        // fixed typo
ne  sw -> o

l1 l2    r
n  se -> ne
n  sw -> nw
s  ne -> se
s  nw -> sw
ne nw -> n
se sw -> s

*/


void reduce_turn(map<string, int>& path, string l1, string l2, string r)
{
    int reduce_by = min(path[l1], path[l2]);
    path[l1] -= reduce_by;
    path[l2] -= reduce_by;
    path[r] += reduce_by;
}

void reduce_fwd_back(map<string, int>& path, string fwd, string back)
{
    int reduce_by = min(path[fwd], path[back]);
    path[fwd]  -= reduce_by;
    path[back] -= reduce_by;
}

int reduce(map<string, int> path)
{
    reduce_turn(path, "n" , "se", "ne");
    reduce_turn(path, "n" , "sw", "nw");
    reduce_turn(path, "s" , "ne", "se");
    reduce_turn(path, "s" , "nw", "sw");
    reduce_turn(path, "ne", "nw", "n" );
    reduce_turn(path, "se", "sw", "s" );

    reduce_fwd_back(path, "n" , "s" );
    reduce_fwd_back(path, "ne", "sw");
    reduce_fwd_back(path, "nw", "se");
    return accumulate(begin(path), end(path), 0, [](const int prev, pair<string, int> ent) {return prev + ent.second; });
}

int main(int argc, char* argv[])
{
    map<string,int> path;
    int maxpath{ 0 };
    string dir;
    while (cin >> dir) {
        path[dir]++;
        maxpath = max(maxpath,reduce(path));
    }
    cout << "Path:    " << reduce(path) << endl;
    cout << "Maxpath: " << maxpath << endl;
    return 0;
}
