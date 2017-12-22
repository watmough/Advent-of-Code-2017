// Advent of Code 2017
// Day 22 - Sporifica Virus

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

typedef enum {u=0,l,d,r} direction;
typedef enum {c=0,w,i,f} state;
state next_state[] = {w,i,f,c};

int main()
{
    // state 
    map<int,map<int,state>> world;

    // next move table
    map<state,map<direction,direction>> next_move;
    next_move[c][u] = l; next_move[c][l] = d; next_move[c][d] = r; next_move[c][r] = u;
    next_move[w][u] = u; next_move[w][l] = l; next_move[w][d] = d; next_move[w][r] = r;
    next_move[i][u] = r; next_move[i][l] = u; next_move[i][d] = l; next_move[i][r] = d;
    next_move[f][u] = d; next_move[f][l] = r; next_move[f][d] = u; next_move[f][r] = l;

    // read input
    string row;
    int cxy = 0, x=0,y=-1000;
    while (getline(cin,row)) {
        cout << row << " len: " << row.length() << endl;
        int ll = row.length();
        y = (y==-1000) ? 0-ll/2 : y;
        x = 0-ll/2;
        for(auto it=begin(row);it!=end(row);++it) {
            cout << x << " " << y << ((*it)=='#' ? " #" : " .");
            world[x++][y] = (*it)=='#' ? i : c;
        }
        cout << endl;
        y++;
    }

    // state
    vector<int> pos = {0,0};
    direction dir = u;
    map<direction,pair<int,int>> move;
    move[u] = pair<int,int>(0,-1);
    move[l] = pair<int,int>(-1,0);
    move[d] = pair<int,int>(0,1);
    move[r] = pair<int,int>(1,0);

    // step
    int infect = 0;
    int steps = 10000000;
    x = 0; y = 0;
    while (steps>0) {
        state cell = world[x][y];
        dir = next_move[cell][dir];
        world[x][y] = next_state[cell];
        infect += (world[x][y]==i ? 1 : 0);
        x += move[dir].first;
        y += move[dir].second;
        steps--;
    }
    cout << "infect: " << infect << endl;
}
