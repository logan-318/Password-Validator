#pragma once

/* Heap Class Coded by Jackson Schreiber 
* 
 This is a min-heap implementation designed to store passwords from the rockyou.txt wordlist.
 Since rockyou.txt is sorted by password frequency, passwords should be inserted into the heap starting from the top of rockyou.txt to the bottom.
 Each inserted password is given an increasing priority number.
 When searching for a password, this implementation searches the most used passwords first
 This is an awful algorithm to use for this kind of dataset since heaps are best for inserting and extracting top/bottom value quickly. searching the heap for a password takes O(n)
*/

#include <iostream>
#include <string>
#include <vector>

//Individual heap nodes
class HeapNode {
public:
    std::string password; //password string
    int priority;         //The position in the file (smaller number = higher frequency)
    HeapNode(const std::string& pwd, int prio) : password(pwd), priority(prio) {}
};

//Heap class for managing heap nodes
class MinHeap {
private:
    //Vector based solution
    std::vector<HeapNode> heapArray;

    //Helper functions
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int i) const { return (i - 1) / 2; }
    int leftChild(int i) const { return (2 * i + 1); }
    int rightChild(int i) const { return (2 * i + 2); }

public:
    //Default constructor
    MinHeap();

    //Copy constructor
    MinHeap(const MinHeap& other) : heapArray(other.heapArray) {}

    //Insert a password into the heap
    void insert(const std::string& pwd, int position);

    //Extract the password with the minimum priority (most commonly used password)
    HeapNode extractMin();

    //Get the size of the heap
    int size() const { return heapArray.size(); }

    //Display heap (debugging)
    void displayHeap() const;
};

//Find password using extractMin
bool findPassword(const MinHeap& heap, const std::string& targetPassword);

//Example main for testing
/*
int main() {
    MinHeap minHeap;

    //Simulating passwords from rockyou.txt
    std::vector<std::string> passwords = {
        "password",   // Position 1
        "123456",     // Position 2
        "12345678",   // Position 3
        "qwerty",     // Position 4
        "abc123"      // Position 5
    };

    //Insert passwords into the heap from top to bottom
    for (size_t i = 0; i < passwords.size(); ++i) {
        minHeap.insert(passwords[i], static_cast<int>(i + 1)); //Positions start from 1
    }

    //Display heap contents
    minHeap.displayHeap();

    //Find a password
    std::string target = "qwerty";
    bool isFound = findPassword(minHeap, target);

    if (isFound) {
        std::cout << "\nPassword \"" << target << "\" found in the heap." << std::endl;
    }
    else {
        std::cout << "\nPassword \"" << target << "\" not found in the heap." << std::endl;
    }

    return 0;
}

*/
