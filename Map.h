/*
Coded By Logan Black.
This is a hash map implementation designed to store and access passwords with O(1) time complexity.
This is much more efficient than the heap implementation, which has an O(n) time complexity when searching.
Two maps are created: one that can access frequencies via a password
                      and one that can access passwords via a frequency
*/

#pragma once
#include <string>
#include <unordered_map>
using namespace std;

class Map {
    // first = password name
    // second = password frequency (1 = highest)
    unordered_map<string, int> passwords;

    // first = password frequency (1 = highest)
    // second = password name
    unordered_map<int, string> frequencies;

public:
    void insert(const string& password, int frequency);
    string findPassword(int frequency);
    bool exists(const string& password) const;
};