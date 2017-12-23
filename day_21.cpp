// Advent of Code 2017
// Day 21 - Fractal Art

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

string input = ".#...####";

/* Example input
../.# => ##./#../...
.#./..#/### => #..#/..../..../#..#
*/

void parse_input(vector<pair<string,string>>& rawrules)
{
    string line;
    while (getline(cin,line)) {
        string input(""), output("");
        auto it=begin(line);
        for (;it!=end(line);++it) {
            if ((*it)=='.') input+=".";
            if ((*it)=='#') input+="#";
            if ((*it)==' ') break;
        }
        for (;it!=end(line);++it) {
            if ((*it)=='.') output+=".";
            if ((*it)=='#') output+="#";
            if ((*it)=='\n'||(*it)=='\r') break;
        }
        // got the input output pairs
        //cout << input << "~" << output << endl;
        rawrules.push_back(pair<string,string>(input,output));
    }
}

void hash_rules(string in, string out, map<int,string>& rules)
{
    static int o2[8][4] = {{0,1,2,3},{2,3,0,1},{1,0,3,2},{3,2,1,0},{1,3,0,2},{2,0,3,1},
                           {0,2,1,3},{3,1,2,0}};
    if (in.length()==4) {
        for (int o=0;o<8;++o) {
            int hash=0;
            for (int b=0;b<4;++b) {
                hash+=(in[o2[o][b]]=='#'?(1<<b):0);
            }
            //cout << in << " hashes " << hex << hash << endl;
            rules[hash] = out;
        }
    }
    static int o3[8][9] = {{0,1,2,3,4,5,6,7,8},{2,1,0,5,4,3,8,7,6},{6,7,8,3,4,5,0,1,2},
                           {6,3,0,7,4,1,8,5,2},{8,7,6,5,4,3,2,1,0},{2,5,8,1,4,7,0,3,6},
                           {0,3,6,1,4,7,2,5,8},{8,5,2,7,4,1,6,3,0}};
    if (in.length()==9) {
        for (int o=0;o<8;++o) {
            int hash=0;
            for (int b=0;b<9;++b) {
                hash+=(in[o3[o][b]]=='#'?(1<<b):0);
            }
            //cout << in << " hashes " << hex << hash << dec << endl;
            rules[hash] = out;
        }
    }
}

int isqrt(int n,int s=1) { while(s*s<n) s++; return s;}

vector<int> split_and_hash(string input)
{
    vector<int> hashes;
    int llen = input.length();
    if (llen%2==0) {
        int side=isqrt(llen);
        for (int i=0;i<side/2;++i) {
            for (int j=0;j<side/2;++j) {
                int hash=0, bit=0;
                for (int r=0;r<2;++r) {
                    for (int c=0;c<2;++c) {
                        hash+=(input[(i*2+r)*side+2*j+c]=='#'?(1<<bit):0); bit++;
                    }
                }
                //cout << input << " 2x2-> " << hex << hash << dec << endl;
                hashes.push_back(hash);
            }
        }
    }
    else if (llen%3==0) {
        int blk=3;
        int side=isqrt(llen);
        int grd=side/blk;
        for (int s=0;s<llen/9;++s) {
            int hash=0, bit=0;
            for (int i=0;i<9;++i) {
                int y = s/grd*blk+i/blk;
                int x = s%grd*blk+i%blk;
                hash+=(input[y*side+x]=='#'?(1<<bit):0); bit++;
            }
            //cout << input << " 3x3-> " << hex << hash << dec << endl;
            hashes.push_back(hash);
        }
    }
    return hashes;
}

string unify(vector<int>& hashes, map<int,string>& rules)
{
    //cout << "unify " << hashes.size() << " hashes " << rules.size() << endl;
    vector<string> outs;
    int area = 0;
    for (auto h : hashes) {
        string o = rules[h]; area+=o.length();
        //cout << "\'" << o << "\'" << endl;
        outs.push_back(o);
    }
    //cout << " area is " << dec << area << endl;
    assert(isqrt(area)*isqrt(area)==area);

    // 'print' the output strings to a grid
    int hashcount = 0;
    int blk  = isqrt(outs[0].length());  // e.g. 2 or 3
    int side = isqrt(area);              // grid side e.g 4, 6 etc
    int grd  = side/blk;                  // rows and columns count
    string grid(area,' ');
    for (int s=0;s<outs.size();++s) {
        string str = outs[s];
        for (int i=0;i<str.length();++i) {
            int y = s/grd*blk+i/blk;
            int x = s%grd*blk+i%blk;
            //cout << "x: " << x << " y: " << y << " <- " << str[i] << endl;
            grid[y*side+x] = str[i];
            hashcount += (str[i]=='#'?1:0);
        }
    }
    cout << "Hashcount: " << hashcount << endl;
    return grid;
}

int main()
{
    vector<pair<string,string>> rawrules;
    parse_input(rawrules);

    map<int, string> rules2x2;
    map<int, string> rules3x3;
    for( auto rule : rawrules) {
        hash_rules(rule.first,rule.second, ((rule.first.length()%2)==0)?rules2x2:rules3x3);
    }

    string grid = input;
    for (int count=18;count>0;--count) {
        vector<int> split = split_and_hash(grid);
        grid = (grid.length()%2==0) ? unify(split,rules2x2) : unify(split,rules3x3);
    }
}

/*
Notes:
* no way for 2rules not to match

rules
2x2 -> 3x3
3x3 -> 4x4

hash all rule inputs for 2x2 and 3x3
flip x, flip y, rot 90, rot 180, rot 270

hash2x2 [0,1,2,3]
    for i=0 .. 3 hash|=(bit[i]<<i)

[[0,1,2,3],[2,3,0,1],[1,0,3,2],[1,3,0,2],[3,2,0,1],[2,0,3,1]]
hash2x2mult input output =
    for each configuration
        for i=0 .. 3 hash|=(bit[i]<<i)


split2:
    for r=0 .. side/2-1
        for c=0 ... side/2-1
            hash = 


Structures:

2rules: hash -> output 3x3
3rules: hash -> output 4x4

bitmap
    split2 -> list hashes
    split3 -> list hashes
    unify list hashes -> bitmap

unify: list outputs
    create a new bitmap -> vector<bool> bitmap
    for each list output
        copy output into bitmap

Read rules
Hash rule matches and create 2map hash -> output and 3map hash -> output

bitmap <- input
While not done count
    split2 or split3 bitmap to list of hashes (by row the col)
    [match hashes to output rules]
    generate2x2 or generate3x3 from list of hashes
    unify list of hashes
*/

