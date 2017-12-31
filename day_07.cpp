// Advent of Code 2017
// Day 07 - Recursive Circus

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include "reader.h"
#include "graph.h"
using namespace std;

int main()
{
    ifstream ifs("day_07.inp",ifstream::in);
    vector<string> input = read_input(ifs);

    jwGraph<string> G;
    for (string line : input) {
        stringstream sstr{without_punctuation(line,with_whitespace)};
        string parent, weight, child;
        sstr >> parent >> weight;
        G.add_node_weight(parent,stoi(weight));
        while (sstr >> child) {
            G.add_edge(parent,child,directed);
        }
    }

    // dump entire graph    
    G.dump_graph();

    // list roots, internal nodes and leaf nodes
    set<string> roots{G.get_roots()};
    cout << "roots: " << roots.size() << " " << (roots.size()>0 ? *(roots.begin()) : "none") << endl;
    set<string> internals{G.get_internals()};
    cout << "internals: " << internals.size() << " " << (internals.size()>0 ? *(internals.begin()) : "none") << endl;
    set<string> leafs{G.get_leafs()};
    cout << "leafs: " << leafs.size() << " " << (leafs.size()>0 ? *(leafs.begin()) : "none") << endl;

    // Count members in group 0, and number of connected groups
    map<string,int> groups = G.connected_groups(G.get_roots());
    cout << "Part 1: Root " << *begin(roots) << " has " << groups[*begin(roots)] << " members." << endl;
    cout << "...with " << groups.size() << " connected groups." << endl;
    
    cout << "Part 2:" << endl;
    auto total_weight = G.compute_weights(*begin(roots));
    G.find_balance(*begin(roots),0);
}
