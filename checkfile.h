#ifndef CHECKFILE_H
#define CHECKFILE_H
#include "editfile.h"
#include<filesystem>
#include <iostream>

class editfile;
class file_editor;
class check {
    friend class editfile;
    friend class file_editor;
    private:
        string filename;
    public:
   inline bool checkfile();
    inline void search();
    inline string getfilename()
    {
        return filename;
    }
    inline void newfile();
};

inline void check::search() {
    cin.clear();
    cout << "Enter file name to search: ";
     getline(cin >> ws, filename);


    if (!checkfile())
    {
        cout << "File not found: " << filename << endl;
        newfile(); // Create a new file if it doesn't exist
    }
    else
    {
        cout << "File found: " << filename << endl;
    }
}
inline bool check::checkfile() {
    ifstream file(filename);
        return file.good();
}

inline void check::newfile() {
    char ch;
    cout << "File does not exist." << endl;
    cout<<"Want To create a new file? (Y/N): ";
    cin>> ch;
    cin.ignore();
    if (ch == 'Y' || ch == 'y') {
        cout<<"Want To change file name? (Y/N): ";
        cin>>ch;
        cin.ignore();
        if(ch=='Y' || ch=='y'){
            cout<<"Enter New File Name: ";
            cin>>filename;
            checkfile();
        }   
    }

    else {
        cout<<"Want To search Another file? (Y/N)";
        cin>>ch;
        if (ch == 'Y' || ch == 'y') {
            search(); // Search for another file
        }
        else{
        cout << "Exiting..." << endl;
            return;
        }
    }
    
    ofstream newFile(filename);
    if (newFile.is_open()) {
        cout << "New file created successfully." << endl;
        newFile.close();
        checkfile(); // Check the new file

    } else {
        cerr << "Error creating file: " << filename << endl;
    }
}
#endif