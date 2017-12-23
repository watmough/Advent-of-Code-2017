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
