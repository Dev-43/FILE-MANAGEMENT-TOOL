#ifndef CHECKFILE_H
#define CHECKFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

// Functional API to search and create files. Keeps the last searched filename
// in a static local so callers (like main) can retrieve it.
inline void search_file();
inline string get_filename();
inline bool file_exists(const string& filename);
inline void new_file_if_missing(string& filename);

inline string& last_filename_storage() {
    static string last_filename;
    return last_filename;
}

inline string get_filename() { return last_filename_storage(); }

inline bool file_exists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

inline void new_file_if_missing(string& filename) {
    char ch;
    cout << "File does not exist: " << filename << endl;
    cout << "Want To create a new file? (Y/N): ";
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (ch == 'Y' || ch == 'y') {
        cout << "Want To change file name? (Y/N): ";
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ch == 'Y' || ch == 'y') {
            cout << "Enter New File Name: ";
            getline(cin, filename);
        }
    } else {
        cout << "Want To search another file? (Y/N): ";
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (ch == 'Y' || ch == 'y') {
            search_file();
            return;
        } else {
            cout << "Exiting..." << endl;
            return;
        }
    }

    ofstream newFile(filename);
    if (newFile.is_open()) {
        cout << "New file created successfully." << endl;
        newFile.close();
    } else {
        cerr << "Error creating file: " << filename << endl;
    }
}

inline void search_file() {
    string filename;
    cout << "Enter file name to search: ";
    getline(cin >> ws, filename);
    last_filename_storage() = filename;
    if (!file_exists(filename)) {
        new_file_if_missing(last_filename_storage());
    } else {
        cout << "File found: " << filename << endl;
    }
}

#endif