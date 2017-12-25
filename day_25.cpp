// Advent of Code 2016
// Day 25 - The Halting Problem

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <map>
using namespace std;


int main()
{
    int state = 0;
    int slot = 0;
    int curval = 0;
    map<int,int> tape;

    int steps = 12459852;
    do {
        switch(state) {         // state A
        case 0: if (tape[slot]==0) {
            tape[slot]=1;
            slot++;
            state='b'-'a';
        } else if (tape[slot]==1) {
            tape[slot]=1;
            slot--;
            state = 'e'-'a';
        }
        break;
        case 1: if (tape[slot]==0) {    // B
            tape[slot]=1;
            slot++;
            state='c'-'a';
        } else if (tape[slot]==1) {
            tape[slot]=1;
            slot++;
            state = 'f'-'a';
        }
        break;
        case 2: if (tape[slot]==0) {    // C
            tape[slot]=1;
            slot--;
            state='d'-'a';
        } else if (tape[slot]==1) {
            tape[slot]=0; 
            slot++;
            state = 'b'-'a';
        }
        break;
        case 3: if (tape[slot]==0) {    // D
            tape[slot]=1;
            slot++;
            state='e'-'a';
        } else if (tape[slot]==1) {
            tape[slot]=0; 
            slot--;
            state = 'c'-'a';
        }
        break;
        case 4: if (tape[slot]==0) {    // E
            tape[slot]=1;
            slot--;
            state='a'-'a';
        } else if (tape[slot]==1) {
            tape[slot]=0;
            slot++;
            state = 'd'-'a';
        }
        break;
        case 5: if (tape[slot]==0) {    // F
            tape[slot]=1;
            slot++;
            state='a'-'a';
        } else if (tape[slot]==1) {
            tape[slot]=1;
            slot++;
            state = 'c'-'a';
        }
        break;

        }
    } while (--steps>0);
    int tot = 0;
    for (auto p : tape) {
        if (p.second==1) tot++;
    }
    cout << tot << endl;
}