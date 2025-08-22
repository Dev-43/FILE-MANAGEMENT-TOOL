#include "deletefile.h"
#include "editfile.h"
#include "checkfile.h"
#include "readfile.h"

// Functional menu-driven entry point. Uses stateless functions from the headers.
static int get_choice() {
    string raw_input;
    cout << "Please enter your choice: ";
    getline(cin, raw_input);
    if (raw_input.length() != 1 || raw_input[0] < '1' || raw_input[0] > '4') {
        cout << "\nInvalid choice. Please enter a number from 1 to 4.\n";
        _getch();
        return -1;
    }
    return raw_input[0] - '0';
}

int main() {
    int choice;
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
                search_file();
                filename = get_filename();
                edit_file(filename);
                break;
            case 2:
                search_file();
                filename = get_filename();
                read_file(filename);
                break;
            case 3:
                search_file();
                filename = get_filename();
                read_file(filename);
                delete_file(filename);
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