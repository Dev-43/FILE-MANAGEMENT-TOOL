#include "deletefile.h"
#include "editfile.h"
#include "checkfile.h"
#include "readfile.h"

class file_editor{
    private:
    editfile editor;
    deletefile delete_file;
    check chec_file;
    readfile read_file;
    char choice_handling();
    public:
    void menu();
};

char file_editor::choice_handling() {
    string raw_input;
    cout<< "Please enter your choice:";
    getline(cin, raw_input);

    // Accept only single characters: '1', '2', '3', or '4'
    if (raw_input.length() != 1 || raw_input[0] < '1' || raw_input[0] > '4') {
       cout << "\nInvalid choice. Please enter a number from 1 to 4.\n";
       _getch();
    }   

    return raw_input[0] - '0'; // safe conversion for switch
}

void file_editor::menu() {
    int choice;
    string filename;
    while (true) {
        editor.clearScreen();
        cout << "Welcome to the File Editor!\n";
        cout << "File Editor Menu:\n";
        cout << "1. Edit File\n";
        cout << "2. Read File\n";
        cout << "3. Delete File\n";
        cout << "4. Exit\n";
        choice= choice_handling();


        switch (choice) {
            case 1:
                chec_file.search();
                filename = chec_file.getfilename();
                editor.edit(filename);
                break;
            case 2:
                chec_file.search();
                filename = chec_file.getfilename();
                read_file.read(filename);
                break;
            case 3:
                chec_file.search();
                filename = chec_file.getfilename();
                read_file.read(filename);
                delete_file.delete_file(filename);
                break;
            case 4:
                cout << "Exiting...\n";
                return; // Exit the menu
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
}
int main(){
    file_editor edit;
    edit.menu();
    return 0; 
}