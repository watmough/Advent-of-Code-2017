// Advent of Code 2017
// http://adventofcode.com/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

void reallocate(vector<int>& m)
{
    auto me = max_element(m.begin(),m.end());
    for (auto b{ exchange(*me,0) }; b--; ++*me) {
        if (++me==m.end()) 
            me=m.begin();
    }
}

int main(int argc, char* argv[])
{
    vector<int> m = { 10, 3, 15, 10, 5, 15, 5, 15, 9, 2, 5, 8, 5, 2, 3, 6 }; //vector<int> m = {0,2,7,0};
    map<vector<int>, int> states;
    auto cycles = 0;
    for (auto cycle{ 0 }; states.insert(pair<vector<int>, int>(m, cycles))./*did insert*/second == true; reallocate(m))
        cycles++;
    cout << "Part 1: " << cycles << endl <<
            "Part 2: " << cycles-states[m] << endl;
    return 0;
}
