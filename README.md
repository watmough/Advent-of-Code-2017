# Advent-of-Code-2017 

### Day 22 - Coprocessor Conflagration

Rank: 345 / ---

Part 1 was a pretty simple hack of Day 18 - Duet.

```C++
// Advent of Code 2017
// Day 23 - Coprocessor Conflagration

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <chrono>
using namespace std;

long mul = 0;

bool step(const vector<string>& iv,const vector<string>& xv,const vector<string>& yv,
          map<string,long long>& reg,
          vector<long long>& send, long long& sentcount,
          vector<long long>& recv)
{
    string tok = iv[reg["pc"]];
    string opx = xv[reg["pc"]];
    string opy = yv[reg["pc"]];
//    cout << tok << " " << opx << " " << opy << endl;
    if (tok=="snd") {
        send.push_back(opx[0]<'a' ? stoi(opx) : reg[opx]);
        sentcount++;
    }
    if (tok=="rcv" && recv.size()==0) {
        return false;
    }
    if (tok=="rcv" && recv.size()>0) {
        reg[opx] = recv.front();
        recv.erase(begin(recv));
    }
    const long long opyval = opy.length()==0 ? 0 : (opy[0]<'a' ? stoi(opy) : reg[opy]);
    if (tok=="set") reg[opx] = opyval;
    if (tok=="sub") reg[opx] -= opyval;
    if (tok=="mul") {mul++; reg[opx] *= opyval;}
    if (tok=="mod") reg[opx] %= opyval;
    if (tok=="jnz" && ((opx[0]<'a' && stoi(opx)!=0)||reg[opx]!=0)) reg["pc"] += opyval;
    else reg["pc"]++;
    if (reg["pc"]<0||reg["pc"]>=iv.size()-1) return false;
    return true;
}

main()
{
    vector<string> iv,xv,yv;
    string tok,opx,opy;
    map<string,long long> reg0;
    map<string,long long> reg1;
    vector<long long> mbox0,mbox1;
    long long sent0{0ll},sent1{0ll},ins_count{0ll};
    while (cin >> tok >> opx) {
        if (!(tok=="snd"||tok=="rcv")) 
            cin >> opy;
        else 
            opy = "";
        cout << "Listing: " << tok << " " << opx << " " << opy << endl;
        iv.push_back(tok);
        xv.push_back(opx);
        yv.push_back(opy); 
    }

    // simulate two programs
    reg0["p"] = 0; reg1["p"] = 1;
//    reg0["a"] = 1;            // debug
    auto start = std::chrono::high_resolution_clock::now();
    while (1) {
        bool stepped0 = step(iv,xv,yv,reg0,mbox1,sent0,mbox0);
//        bool stepped1 = step(iv,xv,yv,reg1,mbox0,sent1,mbox1);
        ins_count+=2;
        if (!stepped0) break;
//        if (!stepped0 && !stepped1)
//            break;
    }
    cout << "Mul: " << mul << endl;
//    cout << "program 1 sent: " << sent1 << " messages." << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Instruction count: " << ins_count << " in " << 
             elapsed_seconds.count()*1000 << " msec " <<
             ins_count / elapsed_seconds.count() / 1000000 << " MIPs" << endl;
    return 0;    
}
```

Part 2 asked us to optimize the Duet assembly language and run it to 
completion with the answer being the contents of the h register.

The code below is *just barely* C++ code!

```C++
// Advent of Code 2017
// Day 23 Part 2 - Coprocessor Conflagration

#include <iostream>
using namespace std;

int main()
{
    long long a,b,c,d,e,f,g,h,i;
    a=1; b=c=d=e=f=g=h=0;

    b=93;                                           // set b 93
    c= b;                                           // set c b
    if (a!=0) goto l5;                              // jnz a 2
    goto l9;                                        // jnz 1 5
l5: b*=100;                                         // mul b 100
    b+=100000;              // b = 109300           // sub b -100000
    c=b;                                            // set c b
    c+=17000;               // c = b + 17000        // sub c -17000

    while (b!=c) {
    l9: f=1;                    // set flag             // set f 1
        d=2;                    // set trial multipland // set d 2

        // replace the following with:
        for (int factor=2;factor<b/2;++factor) {
            if (b%factor==0) {
                f=0;
                break;
            }
        }

/*      while (d!=b && f==1) {      // is_prime
        l11:e=2;                    // find                 // set e 2

            while (e!=b && f==1) {      // is_prime
            l12:g=d;                                            // set g d
                g*=e;                   // g = d*e              // mul g e
                g-=b;                   // if (d*e!=b)          // sub g b
                if(g!=0) goto l17;      //     f = 0            // jnz g 2
                f=0;                    // clear f if divisor   // set f 0
                                        // f = isprime
            l17:e++;                                            // sub e -1
                g=e;                    // g = e + 1            // set g e
                g-=b;                   // g = g - b            // sub g b
  //            if(g!=0) goto l12;                              // jnz g -8
            }

            d++;                                            // sub d -1
            g=d;                                            // set g d
            g-=b;                                           // sub g b
//          if(g!=0) goto l11;                              // jnz g -13
        }*/

        if(f!=0) goto l27;      // if (!is_prime)       // jnz f 2
        h++;                    //     h = h + 1        // sub h -1
    l27:g=b;                    // endif                // set g b
        g-=c;                   // if (b==c)            // sub g c
        if(g!=0) goto l31;      //     break            // jnz g 2
        goto done;              // quit if we get here  // jnz 1 3
    l31:b+=17;                                          // sub b -17
        goto l9;                                        // jnz 1 -23
    }

done:
    cout << h << endl;
    return 0;
}
```

### Day 22 - Sporifica Virus

I was a few hours late starting with this one. 

Rank: 1608 / 1534

```C++
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
```

### Day 21 - 

Rank: 2579 / 2509

Finally bashed out the code for Fractal Art. It was a bit worrying as I wasn't entirely convinced 
that my strategy would work. Does work though!

--- Part One ---
Thus, after 2 iterations, the grid contains 12 pixels that are on.
How many pixels stay on after 5 iterations?

--- Part Two ---
How many pixels stay on after 18 iterations?

```C++
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
```

### Day 20 - Particle Swarm

I started this one in F#, couldn't get part 2 to work, so rewrote in C++ and realized
my mistake eventually.

Rank: 4341 / 4342

Which particle will stay closest to position <0,0,0> in the long term?

How many particles are left after all collisions are resolved?

```C++
// Advent of Code 2017
// Day 20 - Particle Swarm

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef struct particle {
    int num;
    vector<int64_t> pos{0,0,0};
    int64_t vel[3];
    int64_t acc[3];
} particle;

int read_particles(vector<particle>& state)
{
    int64_t x,y,z,vx,vy,vz,ax,ay,az;
    int num = 0;
    while (cin >> x >> y >> z >> vx >> vy >> vz >> ax >> ay >> az) {
        particle p;
        p.num = num++;      // particles are 0 - num-1
        p.pos[0] = x;  p.pos[1] = y;  p.pos[2] = z; 
        p.vel[0] = vx; p.vel[1] = vy; p.vel[2] = vz; 
        p.acc[0] = ax; p.acc[1] = ay; p.acc[2] = az; 
        state.push_back(p);
    }
    return num;
}

void step(particle& p)
{
    p.vel[0] += p.acc[0]; p.vel[1] += p.acc[1]; p.vel[2] += p.acc[2]; 
    p.pos[0] += p.vel[0]; p.pos[1] += p.vel[1]; p.pos[2] += p.vel[2]; 
}

int main()
{
    // read in particles
    vector<particle> state;
    int num_particles = read_particles(state);
    // loop
    int ucount = state.size();
    int generations = 0;
    while (1)
    {
        // sort by position and eliminate dupes
        map<vector<int64_t>,int> dupes;
        for (auto it=begin(state);it!=end(state);++it) {
            dupes[((*it).pos)]++;
        }

        // filter dupes so only includes collision locations
        for (auto it=begin(dupes);it!=end(dupes);) {
            if ((*it).second>1) {
                cout << "dupe at pos " << (*it).first[0] << "," << (*it).first[1] << "," << (*it).first[2] << endl;
                it++;
            } else {
                it = dupes.erase(it++);
            }
        }

        // remove collided particles
        state.erase(remove_if(begin(state),end(state),[&](particle p)->bool{if (dupes.find(p.pos)!=end(dupes)) return true; else return false;}),end(state));
        cout << "Duplicates: " << dupes.size() << " particles: " << state.size() << " gen: " << generations++ << endl;

        // step time
        for (auto it=begin(state);it!=end(state);++it) {
            step(*it);
        }
    }
}
```

### Day 19 - A Series of Tubes

Rank: 631 / 628

The little packet looks up at you, hoping you can help it find the way. What letters will it see (in the order it would see them) if it follows the path? (The routing diagram is very wide; make sure you view it without line wrapping.)

How many steps does the packet need to go?

```C++
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
```

### Day 18 - Duet

Rank: 999 / 566

What is the value of the recovered frequency (the value of the most recently played sound) the first time a rcv instruction 
is executed with a non-zero value?

Once both of your programs have terminated (regardless of what caused them to do so), how many times did program 1 send a value?

```C++
// Advent of Code 2017
// Day 18 - Duet

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <chrono>
using namespace std;

bool step(const vector<string>& iv,const vector<string>& xv,const vector<string>& yv,
          map<string,long long>& reg,
          vector<long long>& send, long long& sentcount,
          vector<long long>& recv)
{
    string tok = iv[reg["pc"]];
    string opx = xv[reg["pc"]];
    string opy = yv[reg["pc"]];
    if (tok=="snd") {
        send.push_back(opx[0]<'a' ? stoi(opx) : reg[opx]);
        sentcount++;
    }
    if (tok=="rcv" && recv.size()==0) {
        return false;
    }
    if (tok=="rcv" && recv.size()>0) {
        reg[opx] = recv.front();
        recv.erase(begin(recv));
    }
    const long long opyval = opy.length()==0 ? 0 : (opy[0]<'a' ? stoi(opy) : reg[opy]);
    if (tok=="set") reg[opx] = opyval;
    if (tok=="add") reg[opx] += opyval;
    if (tok=="mul") reg[opx] *= opyval;
    if (tok=="mod") reg[opx] %= opyval;
    if (tok=="jgz" && ((opx[0]<'a' && stoi(opx)>0)||reg[opx]>0)) reg["pc"] += opyval;
    else reg["pc"]++;
    return true;
}

main()
{
    vector<string> iv,xv,yv;
    string tok,opx,opy;
    map<string,long long> reg0;
    map<string,long long> reg1;
    vector<long long> mbox0,mbox1;
    long long sent0{0ll},sent1{0ll},ins_count{0ll};
    while (cin >> tok >> opx) {
        if (!(tok=="snd"||tok=="rcv")) 
            cin >> opy;
        else 
            opy = "";
        cout << "Listing: " << tok << " " << opx << " " << opy << endl;
        iv.push_back(tok);
        xv.push_back(opx);
        yv.push_back(opy); 
    }

    // simulate two programs
    reg0["p"] = 0; reg1["p"] = 1;
    auto start = std::chrono::high_resolution_clock::now();
    while (1) {
        bool stepped0 = step(iv,xv,yv,reg0,mbox1,sent0,mbox0);
        bool stepped1 = step(iv,xv,yv,reg1,mbox0,sent1,mbox1);
        ins_count+=2;
        if (!stepped0 && !stepped1)
            break;
    }
    cout << "program 1 sent: " << sent1 << " messages." << endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Instruction count: " << ins_count << " in " << 
             elapsed_seconds.count()*1000 << " msec " <<
             ins_count / elapsed_seconds.count() / 1000000 << " MIPs" << endl;
    return 0;    
}
```

Output:

```
PS C:\Workarea\Advent-of-Code-2017> type day_18.ts2 | .\a.exe
Listing: set a 1
Listing: mul p 17
Listing: jgz p p
Listing: mul a 2
Listing: add i -1
Listing: jgz i -2
Listing: add a -1
Listing: set i 127
Listing: set p 680
Listing: mul p 8505
Listing: mod p a
Listing: mul p 129749
Listing: add p 12345
Listing: mod p a
Listing: set b p
Listing: mod b 10000
Listing: snd b
Listing: add i -1
Listing: jgz i -9
Listing: jgz a 3
Listing: rcv b
Listing: jgz b -1
Listing: set f 0
Listing: set i 126
Listing: rcv a
Listing: rcv b
Listing: set p a
Listing: mul p -1
Listing: add p b
Listing: jgz p 4
Listing: snd a
Listing: set a b
Listing: jgz 1 3
Listing: snd b
Listing: set f 1
Listing: add i -1
Listing: jgz i -11
Listing: snd a
Listing: jgz f -16
Listing: jgz a -19
program 1 sent: 7112 messages.
Instruction count: 140280 in 93.075 msec 1.50717 MIPs
PS C:\Workarea\Advent-of-Code-2017>
```

### Day 17 - Spinlock

Rank: 414 / 928

```C++
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
```

### Day 16 - Permutation Promenade

Rank: 959 / 580

You watch the dance for a while and record their dance moves (your puzzle input). In 
what order are the programs standing after their dance?

In what order are the programs standing after their billion dances?

```C++
// Advent of Code 2017
// Day 16 - Permutation Promenade

#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;

int main()
{
    // test inputs
/*  string input = "s1, x3/4, pe/b"; // a spin of size 1: eabcd.*/

    int n,n1,n2;
    string ins;
    char ch;
    map<string,uint> seq;            // cycle?
    string p = "abcdefghijklmnop";

    for(int i=0;i<1000000000%60;++i)
    {
        ifstream in("day_16.txt");
        while(in >> ch) {
            if (ch==',' || ch<'0' || ch=='/' || ch==' ')
                continue;
            if (ch=='s') {
                in >> n;
                string temp(p);
                copy(end(p)-n,end(p),temp.begin());
                copy(begin(p),end(p)-n,temp.begin()+n);
                p=temp;
            }
            if (ch=='x') {
                in >> n1;
                if(in.peek()=='/') in.get();
                in >> n2;
                swap(p[n1],p[n2]);
            }
            if (ch=='p') {
                string sw;
                char ch;
                while (in.peek()!=',' && in >> ch) 
                    sw.push_back(ch);
                auto slash = find_if(sw.begin(),sw.end(),[](int c)->bool{return c=='/';});
                string t1(sw.begin(),slash);
                string t2(slash+1,sw.end());
                auto it1 = p.find(t1);
                auto it2 = p.find(t2);
                copy(t1.begin(),t1.end(),p.begin()+it2);
                copy(t2.begin(),t2.end(),p.begin()+it1);
            }
        }
        if (seq.find(p)!=seq.end()) {
            cout << "Found a repeat of " << p << " at " << i << endl;
        }
        seq[p] = i;
    }
    cout << p << endl;
}
```

### Day 15 - Dueling Generators

Rank: 576 / 498

To get a significant sample, the judge would like to consider 40 million pairs. (In the example above, the judge would eventually find a total of 588 pairs that match in their lowest 16 bits.)
After 40 million pairs, what is the judge's final count?

After 5 million pairs, but using this new generator logic, what is the judge's final count?

```C++
// Advent of Code 2017
// Day 15 - Dueling Generators

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
    //unsigned long long int a{ 65 }, b{ 8921 };
    unsigned long long int a{ 699 }, b{ 124 };
    int match{ 0 };
    for (auto i{ 0 }; i < 40000000; ++i) {
        a = (a * 16807ll) % 2147483647ll;
        b = (b * 48271ll) % 2147483647ll;
        if ((a&0xffff) == (b&0xffff))
            match++;
    }
    cout << "Part 1: " << match << " matches." << endl;
    a = 699, b = 124, match = 0;
    for (auto i{ 0 }; i < 5000000; ++i) {
        do a = (a * 16807ll) % 2147483647ll; while (a % 4);
        do b = (b * 48271ll) % 2147483647ll; while (b % 8);
        if ((a & 0xffff) == (b & 0xffff))
            match++;
    }
    cout << "Part 2: " << match << " matches." << endl;
    return 0;
}
```
Output:
```
OS X:
Jonathans-Pro:Advent-of-Code-2017 jonathan$ clang day\ 15.cpp -std=c++14 -stdlib=libc++ -lc++ -O3 -march=native
Jonathans-Pro:Advent-of-Code-2017 jonathan$ ./a.out
Part 1: 600 matches.
Ran in 283.792 msec
Part 2: 313 matches.
Ran in 411.678 msec
Jonathans-Pro:Advent-of-Code-2017 jonathan$ 

Windows 10:
PS C:\Workarea\AOC2017\day 15\x64\Release> & '.\day 15.exe'
Part 1: 600 matches.
Ran in 241.696 msec
Part 2: 313 matches.
Ran in 373.521 msec
PS C:\Workarea\AOC2017\day 15\x64\Release>

Windows 10 GCC (defaults)

PS C:\Workarea\Advent-of-Code-2017> .\a.exe
Part 1: 600 matches.
Ran in 891.216 msec
Part 2: 313 matches.
Ran in 1096.93 msec
PS C:\Workarea\Advent-of-Code-2017>


```

### Day 14 - Disk Defragmentation

Rank: 304 / 334

Given your actual key string, how many squares are used?

How many regions are present given your key string?

```C++
// Advent of Code 2017
// Day 14 - Disk Defragmentation

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <cassert>
#include <bitset>
using namespace std;

void reverse(vector<int>& numbers, int start, int length)
{
    for (auto pos{ 0 }; pos < length / 2; ++pos)
        swap(numbers[(start + pos) % 256], numbers[(start + length - 1 - pos) % 256]);
}

int writeg(int* g, int row, int col, int hashchar)
{
    g += 128 * row + col * 8;
    for (auto i{ 0 }; i < 8; ++i) {
        *(g + i) = (hashchar & 1 << (7 - i)) ? -1 : 0;
    }
    return 0;
}

void floodfill(int *g, int i, int c)
{
    g[i] = c;
    if (i / 128 > 0 && g[i - 128] == -1) floodfill(g, i - 128, c);
    if (i / 128 <127  && g[i + 128] == -1) floodfill(g, i + 128, c);
    if (i % 128 > 0 && g[i - 1] == -1) floodfill(g, i - 1, c);
    if (i % 128 < 127  && g[i + 1] == -1) floodfill(g, i + 1, c);
}

int main()
{
    vector<int> numbers(256);
    vector<int> lengths = { 192, 69, 168, 160, 78, 1, 166, 28, 0, 83, 198, 2, 254, 255, 41, 12 };
    string seed = "ffayrhll";
    vector<int> trailing{ 17, 31, 73, 47, 23 };
    vector<int> hash(16);

/*  cout << "Part 1: ";
    iota(numbers.begin(), numbers.end(), 0);
    for (auto l{ 0 }, start{ 0 }, skip{ 0 }; l < lengths.size(); start += lengths[l] + l++, ++skip) {
        reverse(numbers, start %= 256, lengths[l]);
    }
    cout << numbers[0] * numbers[1] << endl;*/
    
    cout << "Part 1: ";
    int bitcount{ 0 };
    int g[128 * 128];
    for (int row{ 0 }; row < 128; ++row) { 
        string input(seed);
        input += "-";
        input += to_string(row);
        iota(numbers.begin(), numbers.end(), 0);
        lengths.resize(input.size() + trailing.size());
        copy(input.begin(), input.end(), lengths.begin());
        copy(trailing.begin(), trailing.end(), lengths.end() - trailing.size());
        auto start{ 0 }, skip{ 0 };
        for (int r = 0; r < 64; ++r) {
            for (auto l{ 0 }; l < lengths.size(); start += lengths[l] + skip++, l++) {
                reverse(numbers, start %= 256, lengths[l]);
            }
        }

        for (int i{ 0 }, hashchar{ 0 }; i < 256; ++i) {
            hashchar = i % 16 == 0 ? numbers[i] : hashchar ^ numbers[i];
//          i % 16 == 15 && cout << setw(2) << setfill('0') << hex << hashchar << endl;
            i % 16 == 15 && (bitcount += std::bitset<8>(hashchar).count());
            i % 16 == 15 && (writeg(g,row,i/16,hashchar));
        }
    }
    cout << bitcount << endl;

    int regions{ 0 };
    for (auto i{ 0 }; i < 128 * 128; ++i) {
        if (g[i] == -1) {
            floodfill(g, i, ++regions);
        }
    }

    cout << regions << endl;
    return 0;
}
```

### Day 13 - Packet Scanners

Rank: 3945 / 5082

Given the details of the firewall you've recorded, if you leave immediately, what is the severity of your whole trip?

What is the fewest number of picoseconds that you need to delay the packet to pass through the firewall without being caught?

```C++
// Advent of Code 2017
// Day 13 - Packet Scanners

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

int main(int argc, char* argv[])
{
    int depth, range;
    vector<int> depths, ranges;
    while (cin >> depth) {
        if (cin.peek() == ':') cin.get();
        cin >> range;
        depths.push_back(depth);
        ranges.push_back(range);
    }

    int severity{ 0 };
    for (int step = 0; step<depths.size(); ++step) {
        severity += (depths[step] % ((ranges[step] - 1) * 2))==0 ? (depths[step]*ranges[step]) : 0;
    }
    cout << "Part 1: " << severity << endl;

    auto start = std::chrono::high_resolution_clock::now();
    auto delay{ 0 }, fail{ 0 };
    for (;; ++delay) {
        fail = 0;
        for (auto step{ 0 }; fail == 0 && step < depths.size(); ++step)
            fail = !((depths[step] + delay) % ((ranges[step] - 1) * 2));
        if (fail == 0) break;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Part 2: " << delay << " in " << elapsed_seconds.count()*1000 << " msec" << endl;
    return 0;
}

/*
Output:
Part 1: 1640
Part 2: 3960702 in 49.2783 msec
*/
```
Output:
```
Part 1: 1640
Part 2: 3960702
```

### Day 12 - Digital Plumber

Rank: 1341 / 2225 Live-streamed.

How many programs are in the group that contains program ID 0?

How many groups are there in total?

```C++
// Advent of Code 2017
// http://adventofcode.com/
// Day 12 - Digital Plumber

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <cassert>
using namespace std;


void mergeprogram(int program, map<int, set<int>>& groups)
{
    set<int> childs = groups[program];
    for (auto it = begin(childs); it != end(childs); ++it) {
        if (program == *it) continue;
        if (groups.find(*it) != groups.end()) {
            groups[program].insert(begin(groups[*it]), end(groups[*it]));
            groups.erase(*it);
            mergeprogram(program, groups);
        }
    }
}

int main()
{
    string line;
    map<int, set<int>> groups;
    vector<int> inter(2048);
    int program;
    string delim;

    while (getline(cin, line)) {
        set<int> programs;
        stringstream row(line);
        row >> program >> delim;
        int linked;
        programs.insert(program);
        while (row >> linked) {
            programs.insert(linked);
            if (row.peek()==',')
                row.get();
        }
        groups[program] = programs;
    }

    for (auto pr = begin(groups); pr != end(groups); ++pr) {
        mergeprogram((*pr).first, groups);
    }
    cout << "Group 0 is: " << groups[0].size() << endl;
    cout << "There are : " << groups.size() << " groups" << endl;
    return 0;
}
```
Output:

```
/*
C:\Workarea\AOC2017\day 12\x64\Debug>"day 12.exe" < input.txt
Group 0 is: 145
There are : 207 groups

C:\Workarea\AOC2017\day 12\x64\Debug>
*/
```

### Day 11 - Hex Ed

Rank: 1035 / 1068 

I 'live-streamed' this one, and it slowed me down a bit. I also gave up on the live-stream
and was able to get my solution working in about 5 more minutes.

You have the path the child process took. Starting where he started, you need to determine the fewest 
number of steps required to reach him. (A "step" means to move from the hex you are in to any adjacent hex.)

How many steps away is the furthest he ever got from his starting position?

```C++
// Advent of Code 2017
// http://adventofcode.com/
// Day 11 - Hex Ed

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;


/* Reduction Rules

fwd back
s   n  -> o
se  nw -> o         // fixed typo
ne  sw -> o

l1 l2    r
n  se -> ne
n  sw -> nw
s  ne -> se
s  nw -> sw
ne nw -> n
se sw -> s

*/

void reduce_turn(map<string, int>& path, string l1, string l2, string r)
{
    int reduce_by = min(path[l1], path[l2]);
    path[l1] -= reduce_by;
    path[l2] -= reduce_by;
    path[r] += reduce_by;
}

void reduce_fwd_back(map<string, int>& path, string fwd, string back)
{
    int reduce_by = min(path[fwd], path[back]);
    path[fwd]  -= reduce_by;
    path[back] -= reduce_by;
}

int reduce(map<string, int> path)
{
    reduce_turn(path, "n" , "se", "ne");
    reduce_turn(path, "n" , "sw", "nw");
    reduce_turn(path, "s" , "ne", "se");
    reduce_turn(path, "s" , "nw", "sw");
    reduce_turn(path, "ne", "nw", "n" );
    reduce_turn(path, "se", "sw", "s" );

    reduce_fwd_back(path, "n" , "s" );
    reduce_fwd_back(path, "ne", "sw");
    reduce_fwd_back(path, "nw", "se");
    return accumulate(begin(path), end(path), 0, 
	    [](const int prev, pair<string, int> ent) {return prev + ent.second; });
}

int main(int argc, char* argv[])
{
    map<string,int> path;
    int maxpath{ 0 };
    string dir;
    while (cin >> dir) {
        path[dir]++;
        maxpath = max(maxpath,reduce(path));
    }
    cout << "Path:    " << reduce(path) << endl;
    cout << "Maxpath: " << maxpath << endl;
    return 0;
}
```
Output:
```
C:\Workarea\AOC2017\day 11\x64\Release>"day 11.exe" < input.txt
Path:    720
Maxpath: 1485

C:\Workarea\AOC2017\day 11\x64\Release>
```

### Day 10 - Knot Hash

Rank: 257 / 463

Once this process is complete, what is the result of multiplying the first two numbers in the list?

Treating your puzzle input as a string of ASCII characters, what is the Knot Hash of your puzzle input?

```C++
// Advent of Code 2017
// Day 10 - Knot Hash

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

void reverse(vector<int>& numbers, int start, int length)
{
    for (auto pos{ 0 }; pos < length / 2; ++pos)
        swap(numbers[(start + pos) % 256], numbers[(start + length - 1 - pos) % 256]);
}

int main()
{
    vector<int> numbers(256);
    vector<int> lengths = {192, 69, 168, 160, 78, 1, 166, 28, 0, 83, 198, 2, 254, 255, 41, 12};
    string input = "192,69,168,160,78,1,166,28,0,83,198,2,254,255,41,12";
    vector<int> trailing{ 17, 31, 73, 47, 23 };
    vector<int> hash(16);

    cout << "Part 1: ";
    iota(numbers.begin(), numbers.end(), 0);
    for (auto l{ 0 }, start{ 0 }, skip{ 0 }; l < lengths.size(); start+=lengths[l]+l++,++skip) {
        reverse(numbers,start %= 256, lengths[l]);
    }
    cout << numbers[0]*numbers[1] << endl;

    cout << "Part 2: ";
    iota(numbers.begin(), numbers.end(), 0);
    lengths.resize(input.size()+trailing.size());
    copy(input.begin(), input.end(), lengths.begin());
    copy(trailing.begin(),trailing.end(),lengths.end()-trailing.size());
    auto start{ 0 }, skip{ 0 };
    for (int r = 0; r < 64; ++r) {
        for (auto l{ 0 }; l < lengths.size(); start += lengths[l] + skip++, l++) {
            reverse(numbers, start %= 256, lengths[l]);
        }
    }
    for (int i{ 0 }, hashchar{ 0 }; i < 256; ++i) {
        hashchar = i % 16 == 0 ? numbers[i] : hashchar ^ numbers[i];
        i%16==15 && cout << setw(2) << setfill('0') << hex << hashchar;
    }
    return 0;
}
```
Output:
```
C:\Workarea\AOC2017\day 10\x64\Debug>"day 10.exe"
Part 1: 48705
Part 2: 1c46642b6f2bc21db2a2149d0aeeae5d
C:\Workarea\AOC2017\day 10\x64\Debug>
```

### Day 9 - Stream Processing

Rank: 314 / 256

Count and accumulate a simple nested grammar and skip an almost as simple garbage 
product. e.g. {{}{}<!>>{<>}}

```C++
// Advent of Code 2017 - Day 9 - Stream Processing
#include <iostream>
int main()
{
    int nest = 0, tot = 0, garbage = 0, gc=0;
    char ch;
    for (char ch; std::cin >> ch;) {
        if (!garbage) { switch (ch) {   case '<': garbage=1; break;
                                        case '{': ++nest; break;
                                        case '}': tot += nest--; break; }
        } else {        switch (ch) {   case '!': std::cin.get(); break;
                                        case '>': garbage = 0; break;
                                        default:  gc++; break; }
        }
    }
    std::cout << tot << std::endl;
    std::cout << gc << std::endl;
    return 0;
}
```

### Day 8 - I Heard You Like Registers

Rank: 931 / 910

What is the largest value in any register after completing the instructions in your puzzle input? 

Additionally, to
be safe, the CPU also needs to know the highest value held in any register during this process so that it can decide 
how much memory to allocate to these operations.

```C++
// Advent of Code 2017
// http://adventofcode.com/
// Day 08 - I Heard You Like Registers

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

/*
m n   o p  q r s
b inc 5 if a > 1
a inc 1 if b < 5
c dec -10 if a >= 1
c inc -20 if c == 10
*/

void step(map<string, function<bool(int, int)> > ops, map<string, int>& reg, map<string, int>& regmax, stringstream ins)
{
    string m, n, p, q, r; int o, s;
    ins >> m >> n >> o >> p >> q >> r >> s;
    if (ops[r](reg[q],s))
        reg[m] += o*(n == "inc" ? 1 : -1);
    regmax[m] = max(reg[m], regmax[m]);
}

int main(int argc, char* argv[])
{
    map<string, function<bool(int, int)> > ops;
    ops["<"] =  [](int a, int b)->bool {return a <  b; };
    ops[">"] =  [](int a, int b)->bool {return a >  b; };
    ops["<="] = [](int a, int b)->bool {return a <= b; };
    ops[">="] = [](int a, int b)->bool {return a >= b; };
    ops["=="] = [](int a, int b)->bool {return a == b; };
    ops["!="] = [](int a, int b)->bool {return a != b; };

    map<string, int> reg, regmax;
    string row;
    while (getline(cin, row))
        step(ops, reg, regmax, stringstream(row));
    cout << "Max (final): " << (*max_element(reg.begin(), reg.end(), [](pair<string, int> p1, pair<string, int> p2) {return p1.second < p2.second; })).second << endl;
    cout << "Max (ever ): " << (*max_element(regmax.begin(), regmax.end(), [](pair<string, int> p1, pair<string, int> p2) {return p1.second < p2.second; })).second << endl;
    return 0;
}
```
Output:
```
Max (final): 4902
Max (ever ): 7037
```

### Day 7 - Recursive Circus

Rank: 6625 / 5791

Notes: This has now been cleaned up significantly. The input data is filtered and massaged, which
is cheap and simplifies parsing. I have also broken out the fixing up of the nodes into a
tree out into a separate piece of code.

What is the name of the bottom program? 

Additionally, given that exactly one program is the wrong weight, what would its weight need 
to be to balance the entire tower?

```C++
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <numeric>

using namespace std;

struct node;
typedef struct node { string name; vector<node*> children; int size; } node;

void parse(map<string, node*>& nodes, stringstream input)
{
    node *n = new node;
    input >> n->name >> n->size;
    for (string name; input >> name ;) {
        n->children.push_back(new node);
        n->children.back()->name = name;
    }
    nodes[n->name] = n;
}

void fixup(map<string, node*>& nodes)
{
    vector<string> appearaschildren;
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
        for (auto it2 = (*it).second->children.begin(); it2 != (*it).second->children.end(); ++it2) {
            appearaschildren.push_back((*it2)->name);
            *it2 = nodes[(*it2)->name];
        }
    for_each(appearaschildren.begin(), appearaschildren.end(), [&](string n) {nodes.erase(n); });
}

int compute_size(node *n)
{
    int childtot = 0;
    for (auto it = n->children.begin(); it != n->children.end(); ++it)
        childtot += compute_size(*it);
    return n->size += childtot;
}

void find_balance(node * n, int imbalance)
{
    sort(n->children.begin(), n->children.end(), [](node *a, node *b)->bool {return a->size < b->size; });
    size_t last{ n->children.size() - 1 };
    if (n->children[0]->size != n->children[1]->size) 
        find_balance(n->children[0], n->children[1]->size - n->children[0]->size);
    else if (n->children[last]->size != n->children[last - 1]->size)
        find_balance(n->children[last], n->children[last-1]->size - n->children[last]->size);
    else {
        int childtot{ 0 };
        for (auto it = n->children.begin(); it != n->children.end(); ++it)
            childtot += (*it)->size;
        cout << "node: " << n->name << " should be " << n->size <<
            " + " << imbalance << " - " << childtot << " -> " << n->size + imbalance - childtot << endl;
    }
}

int main(int argc, char* argv[])
{
    map<string, node*> nodes;
    string row, name;
    while (getline(cin, row)) {
        row.erase(remove_if(row.begin(), row.end(), [](int i)->bool {return i == '(' || i == ')' || i == ',' || i == '-' || i == '>';}), row.end());
        parse(nodes, stringstream(row));
    }
    fixup(nodes);
    node * n = (*find_if(nodes.begin(), nodes.end(), [](pair<string, node*>p)->bool {return p.second != nullptr; })).second;
    cout << "name: " << n->name << " size: " << n->size << " children: " << n->children.size() << endl;
    compute_size(n);
    find_balance(n, 0);
    return 0;
}
```
Output is:
```
C:\Workarea\AOC2017\day 07\x64\Debug>"day 07.exe" < input.txt
name: jovejmr size: 40 children: 0
name: fesmk size: 24 children: 0
...redacted...
name: gynzo size: 86 children: 0
name: wnwzo size: 37 children: 0
nodes count: 1
name: ahnofa size: 7 children: 6
```
*Balancing - Part 2*
```
balance node: ahnofa
...
name: hwezjo size: 69875 children: 3
name: qqqxyrl size: 69875 children: 6
name: luralcy size: 69881 children: 5
balance node: luralcy
...
name: osgijzx size: 13964 children: 4
name: uppcjl size: 13964 children: 3
name: bvrxeo size: 13970 children: 6
balance node: bvrxeo
...
name: vvgyhb size: 1786 children: 3
name: ltleg size: 1792 children: 6
balance node: ltleg
...
name: kzuimi size: 164 children: 2
name: kwlqal size: 164 children: 2
name: lahieha size: 164 children: 4
children are balanced
node: ltleg should be 1792 + -6 - 984 -> 802

C:\Workarea\AOC2017\day 07\x64\Debug>
```
### Day 6 - Memory Reallocation

Rank: 5253 / 5049

Given the initial block counts in your puzzle input, how many redistribution cycles must be 
completed before a configuration is produced that has been seen before?

Additionally, how many cycles are in the infinite loop that arises from the configuration in your puzzle input?

Cleaned up courtesy of this post on [reddit](https://www.reddit.com/r/adventofcode/comments/7hvtoq/2017_day_6_solutions/dquz3rv/).

```C++
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

void reallocate(vector<int>& m)
{
    auto me = max_element(m.begin(),m.end());
    for (auto b{ exchange(*me,0) }; b--; ++*me) {
        if (++me==m.end()) 
            me=m.begin();
    }
}

int main(int argc, char* argv[])
{
    vector<int> m = { 10, 3, 15, 10, 5, 15, 5, 15, 9, 2, 5, 8, 5, 2, 3, 6 }; //vector<int> m = {0,2,7,0};
    map<vector<int>, int> states;
    auto cycles = 0;
    for (auto cycle{ 0 }; states.insert(pair<vector<int>, int>(m, cycles))./*did insert*/second == true; reallocate(m))
        cycles++;
    cout << "Part 1: " << cycles << endl <<
            "Part 2: " << cycles-states[m] << endl;
    return 0;
}
```
Output is
```
C:\Workarea\AOC2017\day 06\x64\Release>"day 06.exe"
Part 1: 14029
Part 2: 2765

C:\Workarea\AOC2017\day 06\x64\Release>
```

### Day 5 - A Maze of Twisty Trampolines - All Alike

Rank: 6932 / 6599

How many steps does it take to reach the exit? 

Additionally, now the jumps are even stranger: after each jump, 
if the offset was three or more, instead decrease it by 1. Otherwise, increase it by 1 as before. 
How many steps does it now take to reach the exit?

```C++
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

int interpret(vector<int> ins,bool part2 = false)
{
    int executioncount{ 0 }, pc{ 0 };
    while (pc>=0 && pc<ins.size())
        executioncount++, pc += (part2 && ins[pc]>2 ? ins[pc]-- : ins[pc]++);
    return executioncount;
}

int main(int argc, char* argv[])
{
    vector<int> ins{ istream_iterator<int>{std::cin},{} };
    cout << "Executed part 1: " << interpret(ins) << endl;
    cout << "Executed part 2: " << interpret(ins,true) << endl;
    return 0;
}
```
Output is:
```
C:\Workarea\AOC2017\day 05\x64\Release>"day 05.exe" < input.txt
Executed part 1: 394829
Executed part 2: 31150702

C:\Workarea\AOC2017\day 05\x64\Release>
```

### Day 4 - Passphrases

Rank: 1410 / 1109

The system's full passphrase list is available as your puzzle input. How many passphrases are valid? 

Additionally, for added security, yet another system policy has been put in place. Now, a valid passphrase must contain no two 
words that are anagrams of each other - that is, a passphrase is invalid if any word's letters can be rearranged 
to form any other word in the passphrase. Under this new system policy, how many passphrases are valid?

```C++
// day04.cpp : Defines the entry point for the console application.
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


int main(int argc, char* argv[])
{
    int validcount = 0;
    std::string row;
    while (std::getline(std::cin,row) && row.length()>0) {
        std::stringstream str(row);
        std::vector<std::string> words;
        std::string pass;
        bool INVALID = false;
        while (str >> pass) {
            // Uncomment to sort individual words, so we catch 'anagrams'
            //std::sort(pass.begin(),pass.end());
            if (std::find(words.begin(),words.end(),pass)==words.end()) {
                // push back any words we don't already have
                words.push_back(pass);
            } else {
                // we found a repeated word, INVALID
                std::cout << pass << " invalid on " << row << std::endl;
                INVALID=true;
            }
        }
        // 
        if (!INVALID)
            validcount++;
    }
    std::cout << "Valid count is " << validcount << std::endl;
    return 0;
}
```

### Day 3 - Spiral Memory - Take 2: Rewite!

Code for [Day 03.cpp](https://raw.githubusercontent.com/watmough/Advent-of-Code-2017/master/day%2003.cpp)

I wanted another go at this, as I wan't happy with my spiral generating code.

How many steps are required to carry the data from the square identified in your puzzle input all the way to the access port?

What is the first value written that is larger than your puzzle input?

Here is the code:
```C++
// day3_redo.cpp : Defines the entry point for the console application.
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <map>

typedef enum dir {e=0,n,w,s} direction;
direction next_dir[] = {n,w,s,e};
direction d=e;
int x=0, y=0, count=1, done=0;

// generate spiral coords per the puzzle
void next_coord(int& x, int&y)
{
    x += d==e ? 1 : (d==w) ? -1 : 0;        // east or west
    y += d==n ? 1 : (d==s) ? -1 : 0;        // north or south
    if (++done==count) done=0;              // moved required number of spots
    if (!done && (d==n || d==s)) count++;   // bump count on n or s
    if (!done) d = next_dir[d];             // switch direction
}

// get a value and iterate through the spiral, counting the x,y
// distance is then just abs(x)+abs(y)
int main1(int argc, char* argv[])
{
    std::cout << "Enter value (-1 to quit part 1)" << std::endl;
    int val;
    while (1) {
        std::cin >> val;
        if (val==-1) break;
        for (int i=1; i<val; ++i) {
            next_coord(x,y);
        }
        std::cout << "Distance is " << abs(x)+abs(y) << std::endl;
    }
    return 0;
}

// track spiral totals in part 2
std::map<std::string,int> sum;

// x,y -> "x,y" 
std::string idx(int x,int y)
{
    std::string idx = std::to_string((long long)x);
    idx.push_back(',');
    idx.append(std::to_string((long long)y));
    return idx;
}

// lookup a sum at cell x,y
int lookup(int x, int y)
{
    std::string id = idx(x,y);
    if (sum.find(id)!=sum.end())
        return sum[id];
    return 0;
}

// sum the 8 neighbors of x,y and save it
int save_sum(int x,int y)
{
    int tot=lookup(x-1,y-1)+lookup(x,y-1)+lookup(x+1,y-1)+lookup(x-1,y+1)+lookup(x,y+1)+lookup(x+1,y+1)+lookup(x-1,y)+lookup(x+1,y);
    return (sum[idx(x,y)]=tot);
}

int main2(int argc, char* argv[])
{
    sum[idx(0,0)] = 1;

    std::cout << "Enter value (-1 to quit part 2)" << std::endl;
    int val,sum;
    while (1) {
        std::cin >> val;
        if (val==-1) break;

        d=e, x=0, y=0, count=1, done=0;
        do {
            next_coord(x,y);
            sum = save_sum(x,y);
        } while (sum<=val);

        std::cout << "Value is " << sum << std::endl;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    main1(argc,argv);
    main2(argc,argv);
}
```

Here is the output:

```
Enter value (-1 to quit part 1)
347991
Distance is 480
-1
Enter value (-1 to quit part 2)
347991
Value is 349975
```

### Day 3 - Memory Spirals

Rank: 5454 / 3723 (Based on this code, not the rewrite)

How many steps are required to carry the data from the square identified in your puzzle input all the way to the access port?

What is the first value written that is larger than your puzzle input?

Here's the code:
```C++
// day3.cpp : Defines the entry point for the console application.
// Advent of Code 2017
// http://adventofcode.com/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <map>

// track spiral totals in part 2
std::map<std::string,int> sum;

// x,y -> "x,y" 
std::string idx(int x,int y)
{
    std::string idx = std::to_string((long long)x);
    idx.push_back(',');
    idx.append(std::to_string((long long)y));
    return idx;
}

// lookup a sum at cell x,y
int lookup(int x, int y)
{
    std::string id = idx(x,y);
    if (sum.find(id)!=sum.end())
        return sum[id];
    return 0;
}

// sum the 8 neighbors of x,y and save it
int save_sum(int x,int y)
{
    int tot = 0;
    tot += lookup(x-1,y-1);
    tot += lookup(x,y-1);
    tot += lookup(x+1,y-1);
    tot += lookup(x-1,y+1);
    tot += lookup(x,y+1);
    tot += lookup(x+1,y+1);
    tot += lookup(x-1,y);
    tot += lookup(x+1,y);

    sum[idx(x,y)] = tot;
    std::cout << tot << std::endl;
    return tot;
}

// given a value, do spiral enwwsseeennn... etc. summing the 8 neighbors as we go
// find the first value higher than the problem input
int main2(int argc, char* argv[])
{
    sum[idx(0,0)] = 1;

    std::cout << "Enter a value for part 2" << std::endl;
    int val;
    std::cin >> val;

    int x=0, y=0;
    int count = 0;
    while(1) {
        // move east
        count++;
        for (int i=0;i<count;i++) {
            x++;
            if (val<save_sum(x,y))
                goto done;
        }
        // move north
        for (int i=0;i<count;i++) {
            y++;
            if (val<save_sum(x,y))
                goto done;
        }
        // move west
        count++;
        for (int i=0;i<count;i++) {
            x--;
            if (val<save_sum(x,y))
                goto done;
        }
        // move south
        for (int i=0;i<count;i++) {
            y--;
            if (val<save_sum(x,y))
                goto done;
        }
    }
done:
    std::cin >> val;
    return 0;
}

// part 1 given a spiral starting at 1, calculate the manhattan distance back
// to the center from the problem input.
// I used the following for some clues http://mathforum.org/library/drmath/view/62201.html
// then hack hack hack...
int main1(int argc, char* argv[])
{
    int val;
    std::cout << "Enter a value (or -1 to quit part 1)" << std::endl;
    while (1) {
        std::cin >> val;
        if (val==-1)
            break;
        int side = 1;
        int count = 1;
        int inner = 0;
        int pos = 0;
        int of = 0;
        int dist = 0;
        int rings = 1;

        do {                                    // iterate til we get a big enough ring
            side += 2;
            count = side*side;
            rings++;
        } while (count<val);
        inner = side>1 ? (side-2)*(side-2) : 0; // count of cells inside the ring
        pos = ((val-inner)+side/2)%(side-1);    // distance away from the 12pm 3pm 6pm 9pm positions
        of = (side-1)*(side-1);                 // unused - cells in this ring
        dist = pos + rings-1;                   // total manhattan distance

        std::cout << "Rings " << rings << std::endl;
        std::cout << "Side  " << side << std::endl;
        std::cout << "Pos   " << pos << std::endl;
        std::cout << "Of    " << of << std::endl;
        std::cout << "Dist  " << dist << std::endl;
    };
    return 0;
}

int main(int argc, char* argv[])
{
    main1(argc,argv);
    main2(argc,argv);
}
```
Here's the output:

```
Enter a value (or -1 to quit part 1)
347991
Rings 296
Side  591
Pos   185
Of    348100
Dist  480
-1
Enter a value for part 2
347991
...output redacted...
349975
```
### Day 2 - Corruption Checksum

Rank: 6722 / 6018

Part 1

Accumulate the difference between the largest and smallest value on each line.

```C++
// Advent of Code 2017
// Day 2 - Corruption Checksum Part 1

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>

int main(int argc, char* argv[])
{
    std::string row;
    int num = 0;
    int check = 0;
    while (std::getline(std::cin,row) && row.length()>0) {
        std::stringstream str(row);
        int min = INT_MAX;
        int max = INT_MIN;
        while (str >> num) {
            min = std::min(min,num);
            max = std::max(max,num);
        }
        check += max-min;
    }
    std::cout << "Checksum is " << check << std::endl;
    return 0;
}
```

Part 2

Find the only two evenly divisible numbers on each line and accumulate the result of
each division by line.

```C++
// Advent of Code 2017
// Day 02 - Corruption Checksum Part 2

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
    std::string row;
    int num = 0;
    int check = 0;
    std::vector<int> arr;
    while (std::getline(std::cin,row) && row.length()>0) {
        std::stringstream str(row);
        arr.erase(arr.begin(),arr.end());
        while (str >> num)
            arr.push_back(num);
        for (auto it = arr.begin(); it<arr.end(); ++it) {
            for (auto it2 = arr.begin(); it2<arr.end(); ++it2) {
                int di = *it;
                int dv = *it2;
                if (di>dv && di%dv==0) {
                    check += (di/dv);
                }
            }
        }
    }

    std::cout << "Checksum is " << check << std::endl;
    return 0;
}
```

### Day 1 - Inverse Captcha

Rank: 7576 / 6254

Find the sum of all digits that match the next digit in the list.

```C++
// Advent of Code 2017 
// Day 1 - Inverse Captcha
#include "stdafx.h"
char * input = "5228833336355848549915459366737982598312959583817455621545976784792489468198365998232722734876612332352376192813552949814275947575774339529811976644361517795586998319242241614813622734255797569571577699238592667287428166398221572885869416419682687759743978434571821267146514338394624525648338739929479912368172669885577319718389278168766844487948761697438722556857882433224393723131298876252626643517236883999115665656935521675772866516185899317132494716723615493476397115627687887665194781746377341468995954554518252916859227397693885254329628812355612487594445522395853551734567498838382248616137969637971369615443599973588326388792893969924855316437952313492551671545714262784738343517166544197194547173515155927244175447296474282154114951181648317875827525814453758846194548872789943372281952995222779173812444186491115426476188672253249744478946863317915136832199132868917891243591195719354721129116229164688256853628339233919671468781913167415624214152793864585332944468428849171876873433621524242289488135675313544498245498637424139153782925723745249728743885493877792648576673196889949568317234125863369187953788611841388353999875519172896329524346527265231767868839696693328273381772726782949166112932954356923757485139367298699922984925977724972944277991686823219295939734313874834861796179591659174726432357533113896212781566659154939419866797488347448551719481632572231632463575591599696388223344219228325134233238538854289437756331848887242423387542214691157226725179683638967415678697625138177633444765126223885478348951332634398291612134852858683942466178329922655822225426534359191696177633167962839847985826676955417426617126288255366123169174674348417932158291334646767637764323226842771523598562429399935789788215958367362467652444854123951972118358417629679454978687337137675495295768451719631999398617828287671937584998697959425845883145736323818225129311845997214987663433375689621746665629187252511643969315283316269222835744532431378945137649959158495714472963839397214332815241141327714672141875129895";
int main(int argc, char* argv[])
{
	char * pos = input;
	unsigned int total = 0;
	unsigned int prevdigit = (*(pos+strlen(input)-1))-'0';
	unsigned int curdigit = 0;
	while (*pos) {
		curdigit = (*pos++)-'0';
		if (curdigit==prevdigit)
			total += curdigit;
		prevdigit = curdigit;
	}

	printf("total = %d\n",total);
	return 0;
}
```

Part 2

Find the sum of all digits that match the digit halfway further through the list.

```C++
// Advent of Code 2017
// Day 1 - Inverse Captcha
#include "stdafx.h"
#include <string.h>
char * input = "5228833336355848549915459366737982598312959583817455621545976784792489468198365998232722734876612332352376192813552949814275947575774339529811976644361517795586998319242241614813622734255797569571577699238592667287428166398221572885869416419682687759743978434571821267146514338394624525648338739929479912368172669885577319718389278168766844487948761697438722556857882433224393723131298876252626643517236883999115665656935521675772866516185899317132494716723615493476397115627687887665194781746377341468995954554518252916859227397693885254329628812355612487594445522395853551734567498838382248616137969637971369615443599973588326388792893969924855316437952313492551671545714262784738343517166544197194547173515155927244175447296474282154114951181648317875827525814453758846194548872789943372281952995222779173812444186491115426476188672253249744478946863317915136832199132868917891243591195719354721129116229164688256853628339233919671468781913167415624214152793864585332944468428849171876873433621524242289488135675313544498245498637424139153782925723745249728743885493877792648576673196889949568317234125863369187953788611841388353999875519172896329524346527265231767868839696693328273381772726782949166112932954356923757485139367298699922984925977724972944277991686823219295939734313874834861796179591659174726432357533113896212781566659154939419866797488347448551719481632572231632463575591599696388223344219228325134233238538854289437756331848887242423387542214691157226725179683638967415678697625138177633444765126223885478348951332634398291612134852858683942466178329922655822225426534359191696177633167962839847985826676955417426617126288255366123169174674348417932158291334646767637764323226842771523598562429399935789788215958367362467652444854123951972118358417629679454978687337137675495295768451719631999398617828287671937584998697959425845883145736323818225129311845997214987663433375689621746665629187252511643969315283316269222835744532431378945137649959158495714472963839397214332815241141327714672141875129895";
int main(int argc, char* argv[])
{
	char * pos = input;
	unsigned int len = strlen(input);
	unsigned int total = 0;
	unsigned int chkdigit = 0;
	unsigned int curdigit = 0;
	while (pos-input<len/2) {
		curdigit = *pos-'0';
		chkdigit = *(pos++ +len/2)-'0';
		if (curdigit==chkdigit)
			total += curdigit+chkdigit;
	}
	printf("total = %d\n",total);
	return 0;
}
```
