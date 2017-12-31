// Advent of Code 2017
// Day 05 - A Maze of Twisty Trampolines, All Alike

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

int interpret(vector<int> ins,bool part2 = false)
{
    int executioncount{ 0 }, pc{ 0 };
    while (pc>=0 && pc<ins.size())
        executioncount++, pc += (part2 && ins[pc]>2 ? ins[pc]-- : ins[pc]++);
    return executioncount;
}

int main(int argc, char* argv[])
{
    vector<int> ins{ istream_iterator<int>{cin},{} };
    cout << "Executed part 1: " << interpret(ins) << endl;
    cout << "Executed part 2: " << interpret(ins,true) << endl;
    return 0;
}
