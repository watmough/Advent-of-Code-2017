// Advent of Code 2017
// Day 17 - Spinlock

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

int main()
{
    vector<int> buffer;
    int step{335};
    buffer.push_back(0);
    auto pos = 0u;
    for (auto i=1;i<=2017;++i) {
        pos = (pos + step) % buffer.size();
        buffer.insert(begin(buffer)+pos+1,i);
        pos++;
    }
    cout << "Part 1: " << buffer[(pos+1)%buffer.size()] << endl;
    
    buffer.erase(begin(buffer),end(buffer));
    buffer.insert(begin(buffer),0);
    pos = 0u;
    auto sz = 1u;
    for (auto i=1;i<=50000000;++i) {
        pos = (pos + step) % sz;
        if (pos==0)
            buffer.insert(begin(buffer)+pos+1,i);
        sz++;
        pos++;
    }    
    cout << "Part 2: " << buffer[1] << endl;   
    return 0;
}