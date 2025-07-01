#include "editfile.h"
#include <cstddef>
#include <iostream>

class file_editor;

class readfile {
    friend class file_editor;
    public:
    inline void read(const string& filename);
    inline void clearScreen();
};

inline void readfile::clearScreen() {
    // This works on Windows
    system("cls");
}

inline void readfile::read(const string& filename) {   
    clearScreen();
    // Assuming lines is a vector of strings that should be read from the file
    vector<string> lines;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    for (size_t i = 0; i < lines.size(); ++i) {
            cout << " " << i + 1 << "  " << lines[i] << endl;
    }
    cout << "Press any key to continue...\n";
    _getch();
}
