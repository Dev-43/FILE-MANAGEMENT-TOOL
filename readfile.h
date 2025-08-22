#include "editfile.h"
#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

inline void read_file(const string& filename) {
    clearScreen();
    vector<string> lines;
    ifstream file(filename);
    string line;
    while (getline(file, line)) lines.push_back(line);
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << " " << i + 1 << "  " << lines[i] << endl;
    }
    cout << "Press any key to continue...\n";
    _getch();
}
