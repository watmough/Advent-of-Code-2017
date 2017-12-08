// Advent of Code 2017
// http://adventofcode.com/
// Day 8 - I Heard You Like Registers

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

/*
m n   o p  q r s
b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10
*/

void interpret(map<string, int>& reg, map<string, int>& regmax, vector<string>& inst)
{
    for (auto it = inst.begin(); it != inst.end(); ++it) {
        string ins = *it;
        stringstream input(ins);
        string m, n, o, p, q, r, s;
        input >> m >> n >> o >> p >> q >> r >> s;
        if (r == ">" && reg[q] > atoi(s.c_str()))
            reg[m] += atoi(o.c_str())*(n[0] == 'i' ? 1 : -1);
        if (r == "<" && reg[q] < atoi(s.c_str()))
            reg[m] += atoi(o.c_str())*(n[0] == 'i' ? 1 : -1);
        if (r == ">=" && reg[q] >= atoi(s.c_str()))
            reg[m] += atoi(o.c_str())*(n[0] == 'i' ? 1 : -1);
        if (r == "<=" && reg[q] <= atoi(s.c_str()))
            reg[m] += atoi(o.c_str())*(n[0] == 'i' ? 1 : -1);
        if (r == "==" && reg[q] == atoi(s.c_str()))
            reg[m] += atoi(o.c_str())*(n[0] == 'i' ? 1 : -1);
        if (r == "!=" && reg[q] != atoi(s.c_str()))
            reg[m] += atoi(o.c_str())*(n[0] == 'i' ? 1 : -1);
        regmax[m] = max(reg[m], regmax[m]);
    }

}

int main(int argc, char* argv[])
{
    map<string, int> reg;
    map<string, int> regmax;
    vector<string> inst;
    string row;
    while (getline(cin, row)) {
        inst.push_back(row);
    }
    interpret(reg, regmax, inst);   
    return 0;
}
