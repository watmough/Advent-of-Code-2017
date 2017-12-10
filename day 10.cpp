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
