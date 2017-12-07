// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

typedef struct node;
typedef struct node { string name; vector<node*> children; int size; } node;
map<string, node*> nodes;

node *parse(stringstream input)
{
    string name;
    input >> name;
    node *n = NULL;
    if (nodes.find(name) == nodes.end()) {
        n = nodes[name] = new node;
    }
    else {
        n = nodes[name];
        nodes.erase(name);
    }
    n->name = name;
    while (input && (input.peek() == ' ' || input.peek() == '('))
        input.get();
    input >> n->size;
    while (input && (input.peek() == ' ' || input.peek() == ')'))
        input.get();
    while (input >> name) {
        if (name == "->")
            continue;
        name.erase(name.find_last_not_of(",") + 1);
        if (nodes.find(name) == nodes.end()) {
            // create one so it can be loaded
            nodes[name] = new node;
            n->children.push_back(nodes[name]);
        }
        else {
            n->children.push_back(nodes[name]);
            nodes.erase(name);
        }
    }
    return n;
}

int compute_size(node *n)
{
    int childtot = 0;
    for (auto it = n->children.begin(); it != n->children.end(); ++it)
        childtot += compute_size(*it);
    return n->size += childtot;
}

struct sortobj {
    bool operator()(node *a, node *b)
    {
        return a->size < b->size;
    }
} sortobj;

void find_balance(node * n, int imbalance)
{
    // sort children
    cout << "balance node: " << n->name << endl;
    sort(n->children.begin(), n->children.end(), sortobj);
    for (auto it=n->children.begin(); it!=n->children.end(); it++)
        cout << "name: " << (*it)->name << " size: " << (*it)->size << " children: " << (*it)->children.size() << endl;
    int last{ static_cast<int>(n->children.size()) - 1 };
    if (n->children[0]->size != n->children[1]->size)
        find_balance(n->children[0], n->children[1]->size - n->children[0]->size);
    else if (n->children[last]->size != n->children[last - 1]->size)
        find_balance(n->children[last], n->children[last-1]->size - n->children[last]->size);
    else {
        cout << "children are balanced " << endl;
        int childtot{ 0 };
        for (auto it = n->children.begin(); it != n->children.end(); ++it)
            childtot += (*it)->size;
        cout << "node: " << n->name << " should be " << n->size <<
            " + " << imbalance << " - " << childtot << " -> " << n->size + imbalance - childtot << endl;
    }
}

int main(int argc, char* argv[])
{
    int validcount = 0;
    string row, name;
    while (getline(cin, row) && row.length()>0) {
        node * n = parse(stringstream(row));
        cout << "name: " << n->name << " size: " << n->size << " children: " << n->children.size() << endl;
    }
    cout << "nodes count: " << nodes.size() << endl;
    node * n = nodes.begin()->second;
    cout << "name: " << n->name << " size: " << n->size << " children: " << n->children.size() << endl;
    compute_size(n);
    find_balance(n, 0);
    return 0;
}
