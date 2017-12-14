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
    cout << numbers[0] * numbers[1] << endl;
    */
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
