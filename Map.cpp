#include "Map.h"

// O(2n) = O(n) space
void Map::insert(const string& password, const int frequency) {
    passwords[password] = frequency;
    frequencies[frequency] = password;
}

// O(1) time
string Map::findPassword(const int frequency) {
    // Checks if frequency exists in hash map
    if (frequencies.find(frequency) != frequencies.end()) {
        return frequencies[frequency];
    }
    // Returns empty string if no password has that frequency
    return "";
}

// O(1) time
bool Map::exists(const string &password) const {
    if (passwords.find(password) != passwords.end()) return true;
    return false;
}