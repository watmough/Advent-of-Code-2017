// Advent of Code 2017
// Day 17 - 

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main()
{
    // ???
    vector<int> buffer;

    int step{335},sz{1};

    buffer.push_back(0);
    assert(sz == buffer.size());
    auto pos{0u};
    for (auto i{1};i<2018;++i) {
        pos = (pos + step) % buffer.size();
        buffer.insert(begin(buffer)+pos+1,i);
        sz++;
        assert(sz==buffer.size());
        pos++;// = (pos +1)% buffer.size();
    }
    cout << buffer[(pos+1)%buffer.size()] << endl;

    return 0;
}