#include "deletefile.h"
#include "editfile.h"
#include "checkfile.h"
#include "readfile.h"

// Minimal, functional-style main that uses the free-function editor API.
static int get_choice() {
    string raw_input;
    cout << "Please enter your choice: ";
    getline(cin, raw_input);
    if (raw_input.size() != 1 || raw_input[0] < '1' || raw_input[0] > '4') {
        cout << "\nInvalid choice. Please enter a number from 1 to 4.\n";
        _getch();
        return -1;
    }
    return raw_input[0] - '0';
}

int main() {
    check chec_file;
    deletefile del;
    readfile reader;

    int choice = 0;
    string filename;
    while (true) {
        clearScreen();
        cout << "Welcome to the File Editor!\n";
        cout << "File Editor Menu:\n";
        cout << "1. Edit File\n";
        cout << "2. Read File\n";
        cout << "3. Delete File\n";
        cout << "4. Exit\n";

        choice = get_choice();
        if (choice == -1) continue;

        switch (choice) {
            case 1:
                chec_file.search();
                filename = chec_file.getfilename();
                edit_file(filename); // functional editor
                break;
            case 2:
                chec_file.search();
                filename = chec_file.getfilename();
                reader.read(filename);
                break;
            case 3:
                chec_file.search();
                filename = chec_file.getfilename();
                reader.read(filename);
                del.remove_file(filename);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}