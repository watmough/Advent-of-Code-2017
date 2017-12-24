// Advent of Code 2016
// Day 24 - Air Duct Spelunking

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <tuple>
#include <algorithm>
#include <numeric>
using namespace std;

// parse input
void parse(vector<pair<int,int>>& parts,int& sum)
{
    string row;
    ifstream data("day_24.tst");
    while (getline(data,row)) {
        stringstream line(row);
        int p1,p2;
        line >> p1; line.get();
        line >> p2;
        parts.push_back(pair<int,int>(p1,p2));
        cout << p1 << " " << p2 << endl;
        sum+= (p1+p2);
    }
}

// heuristic - return 0 when at goal
// e.g. manhattan distance, points sill left to visit etc., parts still to use
// lower is better
int h(int total, int used)
{
    return total-used;
}

// generate moves
vector<int> get_moves(vector<int>& used, int port, vector<pair<int,int>>& parts)
{
    vector<int> moves;        // find any matching ports we can use
    for (auto it=begin(parts);it!=end(parts);++it) {
        if (find(begin(used),end(used),it-begin(parts))!=end(used)) continue;
        if ((*it).first==port || (*it).second==port) {
            moves.push_back(it-begin(parts));
        }
    }
    return moves;
}

int main()
{
    vector<pair<int,int>> parts;
    int sum = 0;
    parse(parts,sum);
    
    //              priority  port  used
    priority_queue<tuple<int,int,vector<int>>> frontier;       // priority, x,y
    map<tuple<int,vector<int>>,tuple<int,vector<int>>> previous;
    map<tuple<int,vector<int>>,int> best;
    vector<int> emp{};

    frontier.push(make_tuple(h(sum,0),0,emp));
    
    while (frontier.size()) {
        tuple<int,int,vector<int>> s = frontier.top();
        frontier.pop();
        auto used = get<2>(s);
        auto tot_used = accumulate(begin(used),end(used),0,[&](int a,int idx){return a+parts[idx].first+parts[idx].second;});
        if (sum-tot_used==0)
            break;              // we are done
        vector<int> moves = get_moves(used,get<1>(s),parts);
        for (auto xy : moves) {         // calculate cost and add moves to frontier

            auto t = make_tuple(get<1>(s),pair<int,int>(get<2>(s).first,get<2>(s).second));
            int new_cost = best[t]+1;
            auto s2 = make_tuple(v,pair<int,int>(xy.first,xy.second));        // s2 visited,x,y
            if (best.find(s2)==end(best) || new_cost<best[s2]) {
                frontier.push(make_tuple(new_cost+h(v),v,pair<int,int>(xy.first,xy.second)));
                best[s2] = new_cost;
                previous[s2] = make_tuple(get<1>(s),get<2>(s));
            }
            
        }
    }

    // solution on top of heap


    return 0;
}



