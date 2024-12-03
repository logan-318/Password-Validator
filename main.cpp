#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "Heap.h"
#include "Map.h"
#include <chrono>
using namespace std;

int main()
{   // this block reads user input for the file (rockyou.txt) and the amount of passwords they want to import
    string file;
    int lines_for_import;
    string border = "----------------------------------";
    cout << border << endl;
    cout << "Enter password list file: " << endl;
    cin >> file;
    ifstream infile(file);
    if (infile.is_open()) {
        cout << "File opened successfully!" << endl;
        cout << border << endl;
        cout << "How many lines do you want to import? " << endl;
        cin >> lines_for_import;
        cout << border << endl;

        // this block of code reads the passwords from the file up until the line the user specified
        vector<string> passwords;
        string line;
        int count = 0;
        while (getline(infile,line) && count < lines_for_import && !infile.eof()) {
            passwords.push_back(line);
            count++;
        }
        infile.close();
        // this block initializes the map and heap
        // the map inserts the password and frequency, the heap inserts the password based on frequency
        Map map;
        MinHeap heap;
        int frequency = 1;
        for (const auto& password : passwords) {
            map.insert(password, frequency);
            heap.insert(password, frequency);
            frequency += 1;
        }
        while (true) {
            string menu_option;
            cout << "Select an option: \n1. Search for password\n2. Return password by frequency\n3. End Program" << endl;
            cin >> menu_option;
            cout << border << endl;
            // end program if menu_option == 3
            if (menu_option == "3") {
                cout << "Have a great day!" << endl;
                break;
            }
            if (menu_option == "1") { // search for password
                string pswrd;
                cout << "Enter password to search: " << endl;
                cin >> pswrd;
                bool map_found = false;
                bool heap_found = false;

                // Find password on map
                auto start = chrono::high_resolution_clock::now();
                if (map.exists(pswrd)) map_found = true;
                auto end = chrono::high_resolution_clock::now();
                auto map_duration = chrono::duration_cast<chrono::microseconds>(end - start);

                // Find password on heap
                start = chrono::high_resolution_clock::now();
                if (findPassword(heap, pswrd)) heap_found = true;
                end = chrono::high_resolution_clock::now();
                auto heap_duration = chrono::duration_cast<chrono::microseconds>(end - start);

                if (map_found || heap_found) {
                    cout << "Password found! Your password may not be secure." << endl;
                }
                else {
                    cout << "Password not found! Your password is hard to guess." << endl;
                }
                cout << border << endl;
                cout << "Map Duration: " << map_duration.count() << " microseconds" << endl;
                cout << "Heap Duration: " << heap_duration.count() << " microseconds" << endl;
            }
            else if (menu_option == "2") { // find nth common password
                int freq;
                cout << "Enter the frequency of the password you want to find: " << endl;
                cin >> freq;

                if (freq > 0 && freq <= lines_for_import) {
                    // Search through map
                    auto start = chrono::high_resolution_clock::now();
                    string pswrd = map.findPassword(freq);
                    auto end = chrono::high_resolution_clock::now();
                    auto map_duration = chrono::duration_cast<chrono::microseconds>(end - start);

                    // Search through heap
                    start = chrono::high_resolution_clock::now();
                    MinHeap HeapCopy = heap;
                    HeapNode result;
                    for (int i = 0; i < freq; i++) {
                        result = HeapCopy.extractMin();
                    }
                    end = chrono::high_resolution_clock::now();
                    auto heap_duration = chrono::duration_cast<chrono::microseconds>(end - start);

                    string suffix = "th";
                    string freq_str = to_string(freq);
                    if (freq_str[freq_str.size() - 1] == '1') {
                        suffix = "st";
                    }
                    else if (freq_str[freq_str.size() - 1] == '2') {
                        suffix = "nd";
                    }
                    else if (freq_str[freq_str.size() - 1] == '3') {
                        suffix = "rd";
                    }
                    cout << "The " << freq << suffix << " most common password is: " << result.password << endl;

                    cout << border << endl;
                    cout << "Map Duration: " << map_duration.count() << " microseconds" << endl;
                    cout << "Heap Duration: " << heap_duration.count() << " microseconds" << endl;
                }
                else cout << "Frequency not in valid range!" << endl;
            }
            else {
                cout << "Invalid option!" << endl;
            }
            cout << border << endl;
        }
    }
    else {
        cout << "File could not be opened!";
    }
    return 0;
}