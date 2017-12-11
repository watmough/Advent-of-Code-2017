# Advent-of-Code-2017 

### Day 11 - Hex Ed

Rank: 1035/1068 I 'live-streamed' this one, and it slowed me down a bit. I also gave up on the live-stream
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
se  sw -> o
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

This has now been cleaned up significantly. The input data is filtered and massaged, which
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

### Day 3 - Spiral Memory - Take 2: Another Crack at This!

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

Part 1

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
