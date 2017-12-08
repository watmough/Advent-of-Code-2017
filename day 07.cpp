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

struct node;
typedef struct node { string name; vector<node*> children; int size; } node;

void parse(map<string, node*>& nodes, stringstream input)
{
	string name;
	input >> name;
	node *n = nodes[name];
	if (n!=nullptr)	
		nodes.erase(name);
	if (n==nullptr)
		n = nodes[name] = new node;
	n->name = name;
	input >> n->size;
	while (input >> name) {
		if (nodes.find(name) == nodes.end()) {
			nodes[name] = new node;
			n->children.push_back(nodes[name]);
		}
		else {
			n->children.push_back(nodes[name]);
			nodes.erase(name);
		}
	}
}

int compute_size(node *n)
{
	int childtot = 0;
	for (auto it = n->children.begin(); it != n->children.end(); ++it)
		childtot += compute_size(*it);
	return n->size += childtot;
}

void find_balance(node * n, int imbalance)
{
	sort(n->children.begin(), n->children.end(), [](node *a, node *b)->bool {return a->size < b->size; });
	size_t last{ n->children.size() - 1 };
	if (n->children[0]->size != n->children[1]->size) 
		find_balance(n->children[0], n->children[1]->size - n->children[0]->size);
	else if (n->children[last]->size != n->children[last - 1]->size)
		find_balance(n->children[last], n->children[last-1]->size - n->children[last]->size);
	else {
		int childtot{ 0 };
		for (auto it = n->children.begin(); it != n->children.end(); ++it)
			childtot += (*it)->size;
		cout << "node: " << n->name << " should be " << n->size <<
			" + " << imbalance << " - " << childtot << " -> " << n->size + imbalance - childtot << endl;
	}
}

int main(int argc, char* argv[])
{
	map<string, node*> nodes;
	string row, name;
	while (getline(cin, row)) {
		row.erase(remove_if(row.begin(), row.end(), [](int i)->bool {return i == '(' || i == ')' || i == ',' || i == '-' || i == '>';}), row.end());
		parse(nodes, stringstream(row));
	}
	cout << "nodes count: " << nodes.size() << endl;
	node * n = nodes.begin()->second;
	cout << "name: " << n->name << " size: " << n->size << " children: " << n->children.size() << endl;
	compute_size(n);
	find_balance(n, 0);
	return 0;
}
