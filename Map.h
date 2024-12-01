/* Map Class Coded by Logan Black */

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