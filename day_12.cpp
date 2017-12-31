// Advent of Code 2017
// Day 12 - Digital Plumber

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "reader.h"
#include "graph.h"
using namespace std;

int main()
{
    ifstream ifs("day_12.inp",ifstream::in);
    vector<string> input = read_input(ifs);

    jwGraph<int> G;
    for (string line : input) {
        stringstream sstr{without_punctuation(line,with_whitespace)};
        int parent, child;
        sstr >> parent;
        while (sstr >> child) {
            G.add_edge(parent,child,undirected);
        }
    }

    auto groups = G.connected_groups(G.get_parents());
    cout << "Part 1: Group 0 has " << groups[0] << " members." << endl;
    cout << "Part 2: " << groups.size() << " connected groups." << endl;
}

/*
Output:

Part 1: Group 0 has 145 members.
Part 2: 207 connected groups.
*/
