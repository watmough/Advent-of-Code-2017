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
    map<string,unsigned int> seq;            // cycle?
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

