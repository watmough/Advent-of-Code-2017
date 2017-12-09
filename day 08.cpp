// Advent of Code 2017
// http://adventofcode.com/
// Day 08 - I Heard You Like Registers

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

/*
m n   o p  q r s
b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10
*/

void step(map<string, function<bool(int, int)> > ops, map<string, int>& reg, map<string, int>& regmax, stringstream ins)
{
    string m, n, p, q, r; int o, s;
    ins >> m >> n >> o >> p >> q >> r >> s;
    if (ops[r](reg[q],s))
        reg[m] += o*(n == "inc" ? 1 : -1);
    regmax[m] = max(reg[m], regmax[m]);
}

int main(int argc, char* argv[])
{
    map<string, function<bool(int, int)> > ops;
    ops["<"] =  [](int a, int b)->bool {return a <  b; };
    ops[">"] =  [](int a, int b)->bool {return a >  b; };
    ops["<="] = [](int a, int b)->bool {return a <= b; };
    ops[">="] = [](int a, int b)->bool {return a >= b; };
    ops["=="] = [](int a, int b)->bool {return a == b; };
    ops["!="] = [](int a, int b)->bool {return a != b; };

    map<string, int> reg, regmax;
    string row;
    while (getline(cin, row))
        step(ops, reg, regmax, stringstream(row));
    return 0;
}
