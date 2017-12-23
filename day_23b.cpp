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