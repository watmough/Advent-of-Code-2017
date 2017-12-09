// Advent of Code 2017
// http://adventofcode.com/
// Day 09 - Stream Processing

#include "stdafx.h"
#include <iostream>

using namespace std;

int main()
{
    int nest = 0, tot = 0, garbage = 0, gc=0;
    char ch;
    while (cin >> ch) {
        if (!garbage) {
            switch (ch) {
            case '<':
                garbage=1;
                break;
            case '{':
                ++nest;
                break;
            case '}':
                tot += nest--;
                break;
            }
        }
        else {
            switch (ch) {
            case '!':
                cin.get();
                break;
            case '>':
                garbage = 0;
                break;
            default:
                gc++;
                break;
            }

        }
    }
    cout << tot << endl;
    cout << gc << endl;
    return 0;
}
