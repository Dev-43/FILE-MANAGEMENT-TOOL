#ifndef DELETEFILE_H
#define DELETEFILE_H
#include "editfile.h"
#include <fstream>
#include <cstdio>

class file_editor;

class deletefile{
    friend class file_editor;

    inline void delete_file(const string& filename);
        
};

void deletefile::delete_file(const string& filename) {
    char confirm;
        cout << "Are you sure you want to delete '" << filename << "'? (y/n): ";
        cin >> confirm;
        cin.ignore();

        if (confirm == 'y' || confirm == 'Y') {           
            if (remove(filename.c_str())== 0)
                    cout << " File deleted successfully.\n";
            else
                 cerr << "Could not delete file.\n";
             
        }
        else
            cout << "Cancelled deletion.\n";
        
}
#endif
