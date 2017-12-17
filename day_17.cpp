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
    for (auto i{1};i<=50000000;++i) {
        pos = (pos + step) % sz; //buffer.size();
//        assert(sz==buffer.size());
        if (pos==0)
            buffer.insert(begin(buffer)+pos+1,i);
        sz++;
//        assert(sz==buffer.size());
        pos++;// = (pos +1)% buffer.size();
    }
    
    cout << buffer[0] << " " << buffer[1] << endl;
    //cout << buffer[(pos+1)%buffer.size()] << endl;
    
    return 0;
}