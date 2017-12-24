// Advent of Code 2016
// Day 24 - Electromagnetic Moat

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;

// parse input
void parse(vector<pair<int,int>>& parts)
{
    auto row{""s};
    auto p1{0},p2{0};
    ifstream data("day_24.inp");
    while (getline(data,row)) {
        stringstream line(row);
        line >> p1; line.get();
        line >> p2;
        parts.push_back(pair<int,int>(p1,p2));
    }
}

bool not_used(vector<int> used, int part_num)
{
    return find(begin(used),end(used),part_num)==end(used);
}

bool can_use(pair<int,int> part, int port)
{
    return part.first==port || part.second==port;
}

vector<int> get_moves(vector<pair<int,int>>& parts, vector<int> used,int port)    // components matching port that have not been used
{
    vector<int> moves;
    for (int i=0;i<parts.size();++i) {
        if (not_used(used,i) && can_use(parts[i],port)) {
            moves.push_back(i);
        }
    }
    return moves;
}

// Part 1 - Just solve for best strength
tuple<int,vector<int>> solve_strength(vector<pair<int,int>>& parts, vector<int> used, int port, int strength)
{
    vector<int> moves = get_moves(parts,used,port);
    auto best_strength = strength;
    vector<int> best_path = used;
    for (auto m : moves) {
        used.push_back(m);
        auto new_port = parts[m].first==port ? parts[m].second : parts[m].first;
        auto new_strength = strength+parts[m].first+parts[m].second;
        auto solution = solve_strength(parts,used,new_port,new_strength);
        if (get<0>(solution)>best_strength) {
            best_strength = get<0>(solution);
            best_path = get<1>(solution);
        }
        used.pop_back();
    }
    return make_tuple(best_strength,best_path);
}

// Part 2 - Solve for longest path
tuple<int,int,vector<int>> solve_length(vector<pair<int,int>>& parts, vector<int> used, int port, int strength,int length)
{
    vector<int> moves = get_moves(parts,used,port);
    auto best_length = length;
    auto best_strength = strength;
    vector<int> best_path = used;
    for (auto m : moves) {
        used.push_back(m);
        auto new_port = parts[m].first==port ? parts[m].second : parts[m].first;
        auto new_strength = strength+parts[m].first+parts[m].second;
        auto new_length = length+1;
        auto solution = solve_length(parts,used,new_port,new_strength,new_length);
        if (get<0>(solution)>best_length || (get<0>(solution)==best_length && get<1>(solution)>best_strength)) {
            best_length = get<0>(solution);
            best_strength = get<1>(solution);
            best_path = get<2>(solution);
        }
        used.pop_back();
    }
    return make_tuple(best_length,best_strength,best_path);
}

int main()
{
    vector<pair<int,int>> parts;
    parse(parts);

    auto solution_strength = solve_strength(parts,vector<int>{},0,0);
    cout << "Part 1: " << get<0>(solution_strength) << endl;

    auto solution_length = solve_length(parts,vector<int>{},0,0,0);
    cout << "Part 2: " << get<1>(solution_length) << endl;

    return 0;
}

/*
Output:

Part 1: 1906
Part 2: 1824
*/