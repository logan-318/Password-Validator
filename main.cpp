#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <Heap.h>
#include <Map.h>
#include <chrono>
using namespace std;

int main()
{   // this block reads user input for the file (rockyou.txt) and the amount of passwords they want to import
    string file;
    int lines_for_import;
    cout << "Enter password list file: " << endl;
    cin >> file;
    cout << "How many lines do you want to import? " << endl;
    cin >> lines_for_import;

    // this block of code reads the passwords from the file up until the line the user specified
    ifstream infile(file);
    vector<string> passwords;
    string line;
    int count = 0;
    while (getline(infile,line) && count < lines_for_import) {
        passwords.push_back(line);
        count++;
    }
    infile.close();
    // this block intializes the map and heap
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
        int menu_option;
        int alg_option;
        cout << "Select an option: \n1. Search for password\n2. Return password by frequency\n3. End Program" << endl;
        cin >> menu_option;
        cout << "Which algorithm do you want to use?\n1. Map\n2. Heap" << endl;
        cin >> alg_option;
        if (alg_option == 1) {  //map
            if (menu_option == 1) { //search for password
                string pswrd;
                cout << "Enter password to search: " << endl;
                cin >> pswrd;
                auto start = chrono::high_resolution_clock::now();
                if (map.exists(pswrd)) {
                    cout << "Password found" << endl;
                }
                else {
                    cout << "Password not found" << endl;
                }
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                cout << "Duration: " << duration.count() << " milliseconds" << endl;
            }
            else if (menu_option == 2) { // return password by frequency
                int freq;
                cout << "Enter frequency of password you want to find: " << endl;
                cin >> freq;
                auto start = chrono::high_resolution_clock::now();
                string pswrd = map.findPassword(freq);
                auto end = chrono::high_resolution_clock::now();
                cout << "Password with frequency " << freq << ": " << pswrd << endl;
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                cout << "Duration: " << duration.count() << " milliseconds" << endl;
            }
        }
        else if (alg_option == 2) { //heap
            if (menu_option == 1) { //search for password
                string pswrd;
                cout << "Enter password to search: " << endl;
                cin >> pswrd;
                auto start = chrono::high_resolution_clock::now();
                if (findPassword(heap, pswrd)) {
                    cout << "Password found" << endl;
                }
                else {
                    cout << "Password not found" << endl;
                }
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                cout << "Duration: " << duration.count() << " milliseconds" << endl;
            }
            else if (menu_option == 2) { //return password by frequency
                int freq;
                cout << "Enter frequency of password you want to find: " << endl;
                cin >> freq;
                auto start = chrono::high_resolution_clock::now();
                MinHeap HeapCopy = heap;
                HeapNode result;
                for (int i = 0; i < freq; i++) {
                    result = HeapCopy.extractMin();
                }
                auto end = chrono::high_resolution_clock::now();
                cout << "Password with frequency " << freq << ": " << result.password << endl;
                auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
                cout << "Duration: " << duration.count() << " milliseconds" << endl;
            }
        }
        else {
            break; // ends program
        }
    }
    return 0;
}