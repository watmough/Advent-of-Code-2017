// Advent of Code 2017
// http://adventofcode.com/
// Day 19 - A Series of Tubes

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef enum direction {nomove,u,d,l,r} direction;

direction next_move(vector<string>& lines, int row, int col,direction dir)
{
    switch(dir) {       // preferred direction
    case u: if (dir!=d && row>0 && lines[row-1][col]!=' ') return u;
    case d: if (dir!=u && row<lines.size()-1 && lines[row+1][col]!=' ') return d;
    case r: if (dir!=l && col<lines[row].length()-1 && lines[row][col+1]!=' ') return r;
    case l: if (dir!=r && col>0 && lines[row][col-1]!=' ') return l;
            if (dir!=d && row>0 && lines[row-1][col]!=' ') return u;        // mop up any corners
            if (dir!=u && row<lines.size()-1 && lines[row+1][col]!=' ') return d;
            if (dir!=l && col<lines[row].length()-1 && lines[row][col+1]!=' ') return r;
    }
    return nomove;
}

string follow(vector<string>& lines, int& steps)
{
    string letters;
    int row=0,col=0;
    while (lines[row][col]!='|') col++;         // find starting position
    direction dir = d;
    while (dir != nomove) {
        steps++, dir = next_move(lines,row,col,dir);
        switch(dir) {
            case d: row++; break;
            case u: row--; break;
            case r: col++; break;
            case l: col--; break;
            case nomove:
                cout << "STUCK!! at " << row << " " << col << " " << steps << endl;
        }
        if (lines[row][col]>='A' && lines[row][col]<='Z' && dir!=nomove)
            letters+=lines[row][col];
    }
    return letters;
}

int main()
{
    vector<string> lines;
    ifstream ifs("day_19.ts2",ifstream::in);
    string l;
    while (getline(ifs,l)) {
        lines.push_back(l);
        cout << l << endl;
    }
    int steps = 0;
    string letters = follow(lines,steps);
    cout << letters << " " << steps << endl;
    return 0;
}
