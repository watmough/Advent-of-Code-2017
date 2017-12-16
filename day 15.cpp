// Advent of Code 2017
// Day 15 - Dueling Generators

#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    //unsigned long long int a{ 65 }, b{ 8921 };
    unsigned long long int a{ 699 }, b{ 124 };
    int match{ 0 };
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i{ 0 }; i < 40000000; ++i) {
        a = (a * 16807ll) % 2147483647ll;
        b = (b * 48271ll) % 2147483647ll;
        if ((a&0xffff) == (b&0xffff))
            match++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Part 1: " << match << " matches." << endl;
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "Ran in " << elapsed_seconds.count()*1000 << " msec" << endl;

    a = 699, b = 124, match = 0;
    start = std::chrono::high_resolution_clock::now();
    for (auto i{ 0 }; i < 5000000; ++i) {
        do a = (a * 16807ll) % 2147483647ll; while (a % 4);
        do b = (b * 48271ll) % 2147483647ll; while (b % 8);
        if ((a & 0xffff) == (b & 0xffff))
            match++;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    cout << "Part 2: " << match << " matches." << endl;
    cout << "Ran in " << elapsed_seconds.count()*1000 << " msec" << endl;
    return 0;
}

