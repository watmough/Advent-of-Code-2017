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

/*
Output:

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
*/