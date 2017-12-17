// Advent of Code 2017
// Day 15 - Dueling Generators

#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    //unsigned long long int a{ 65 }, b{ 8921 };
    auto a{ 699ul }, b{ 124ul };
    auto match{ 0u };
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i{ 0 }; i < 40000000; ++i) {
        a = (a * 16807u) % 2147483647u;
        b = (b * 48271u) % 2147483647u;
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
        do a = (a * 16807u) % 2147483647u; while (a % 4u);
        do b = (b * 48271u) % 2147483647u; while (b % 8u);
        if ((a & 0xffff) == (b & 0xffff))
            match++;
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    cout << "Part 2: " << match << " matches." << endl;
    cout << "Ran in " << elapsed_seconds.count()*1000 << " msec" << endl;
    return 0;
}

