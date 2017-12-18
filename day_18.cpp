// Advent of Code 2017
// Day 18 -

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

/*
set a 1
add a 2
mul a a
mod a 5
snd a
set a 0
rcv a
jgz a -1
set a 1
jgz a -2
*/


bool step(vector<string> iv,vector<string> xv,vector<string> yv,
          map<string,long long>& reg,
          vector<long long>& send, long long& sentcount,
          vector<long long>& recv)
{
    string tok = iv[reg["pc"]];
    string opx = xv[reg["pc"]];
    string opy = yv[reg["pc"]];
//    cout << endl << "PC: " << reg["pc"] << " " << tok << " " << 
//                        opx << " " << opy;
    if (tok=="snd") {
        send.push_back(opx[0]<'a' ? stoi(opx) : reg[opx]);
        sentcount++;
//        cout << " snd " << (opx[0]<'a' ? stoi(opx) : reg[opx]);
    }
    if (tok=="rcv") {
        if (recv.size()==0) {
            cout << "w";
            return false;
        } else {
            reg[opx] = recv.front();
            recv.erase(begin(recv));
        }
    }
    long long opyval = opy.length()==0 ? 0 : (opy[0]<'a' ? stoi(opy) : reg[opy]);
    if (tok=="set") {
        reg[opx] = opyval;
//        cout << " reg-" << opx << " " << reg[opx] << " = " << opyval;
    }
    if (tok=="add") {
        reg[opx] += opyval;
//        cout << " reg-" << opx << " " << reg[opx] << " += " << opyval;
    }
    if (tok=="mul") {
        reg[opx] *= opyval;
//        cout << " reg-" << opx << " " << reg[opx] << " *= " << opyval;
    }
    if (tok=="mod") {
        reg[opx] %= opyval;
//        cout << " reg-" << opx << " " << reg[opx] << " %= " << opyval;
    }
    if (tok=="jgz" && ((opx[0]<'a' && stoi(opx)>0)||reg[opx]>0)) {
        reg["pc"] += opyval;
//        cout << " jmp " << opyval;
    } else {
        reg["pc"]++;
    }
    return true;
}


main()
{
    // ???
    vector<string> iv,xv,yv;

    string tok,opx,opy;
    map<string,long long> reg0;
    map<string,long long> reg1;
    vector<long long> mbox0,mbox1;
    long long sent0{0ll},sent1{0ll};
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
    reg0["p"] = 0;
    reg1["p"] = 1;
    while (1) {
        bool stepped0 = step(iv,xv,yv,reg0,mbox1,sent0,mbox0);
        bool stepped1 = step(iv,xv,yv,reg1,mbox0,sent1,mbox1);
        if (!stepped0 && !stepped1)
            break;
    }
    cout << "program 1 sent: " << sent1 << endl;
    return 0;    
}