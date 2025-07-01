#ifndef EDITFILE_H
#define EDITFILE_H
#include <cstddef>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<process.h> 
#include <windows.h>
using namespace std;

class file_editor;
class editfile{
    friend class file_editor;
    public:
    void edit(const string& filename);
    void clearScreen();
    string cursor_position(const string& line, int pos);
    inline void display(const vector<string>& lines, int currentline,int cursor,
                 const string& filename = "Untitled.txt");
    bool modified = false; // Track if the file has been modified
};


inline void editfile::clearScreen() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);

    DWORD count;
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    COORD homeCoords = { 0, 0 };

    FillConsoleOutputCharacter(hOut, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hOut, homeCoords);
}


// Insert Cursor
inline string editfile::cursor_position(const string& line, int pos) {
    if (pos >= 0 && static_cast<size_t>(pos) <= line.length())
        return line.substr(0, pos) + "|" + line.substr(pos);
    else
        return line + "|";
}

// Display full file with highlight on current line
inline void editfile::display(const vector<string>& lines, int currentline,int cursor,
                              const string& filename) {
    clearScreen();
    cout << "Editing: " << filename;
    if (modified) cout << " *"; // Show unsaved mark
    cout << "  |  Ctrl+S = Save, ESC = Exit\n\n";

    for (size_t i = 0; i < lines.size(); ++i) {
        if (static_cast<int>(i) == currentline)
            cout << ">" << i + 1 << "  " << cursor_position( lines[i], cursor ) << endl; // Highlight current line
        else
            cout << " " << i + 1 << "  " << lines[i] << endl;
    }
}
inline void editfile::edit(const string& filename) {
    vector <string> lines;
    string line;
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    while (getline(file, line)) {
        lines.push_back(line);
    }
     file.close();

    if (lines.empty())
        lines.push_back(""); // Ensure at least one editable line

    unsigned char ch;
    int currentline = lines.size() - 1; // Start at the last line
    int cursor = lines[currentline].length(); // Start at the end of the last line
    display(lines, currentline,cursor, filename);
    while(true){
        ch = _getch(); // Get input character
        switch (ch) {
            case 19: // CTRL+S
            {
                ofstream file(filename);
                for (const auto& line : lines)
                file << line << '\n';
                file.close();
                modified = false;
            }
            break;

            case 9: // TAB
                lines[currentline].insert(cursor, "    ");
                cursor += 4;
                modified = true;
            break;

            case 27: // ESC
            {
                if (modified) {
                char choice;
                cout << "\nYou have unsaved changes. Do you want to save before exiting? (Y/N): ";
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    ofstream file(filename);
                    for (const auto& line : lines)
                        file << line << '\n';
                    file.close();
                    cout << "File saved successfully. Exiting...\n";
                } else {
                    cout << "Exiting without saving changes.\n";
                }
            }
            return;
            }

            case 13: // ENTER
            {
                string newLine = "";
                int len = static_cast<int>(lines[currentline].length());
                if (cursor <= len)
                    newLine = lines[currentline].substr(cursor);
                lines[currentline] = lines[currentline].substr(0, min(cursor, len));
                lines.insert(lines.begin() + currentline + 1, newLine);
                currentline++;
                cursor = 0;
                modified = true;
            }
            break;

            case 8: // BACKSPACE
                if (cursor > 0) {
                    lines[currentline].erase(cursor - 1, 1);
                    cursor--;
                } 
                else if (currentline > 0) {
                    int prevLen = lines[currentline - 1].length();
                lines[currentline - 1] += lines[currentline];
                lines.erase(lines.begin() + currentline);
                currentline--;
                cursor = prevLen;
                }
                modified = true;
            break;

            case 224: 
            {
                unsigned char arrow = _getch();
                switch (arrow) {
                    case 72: // UP
                        if (currentline > 0) {
                            currentline--;
                            cursor = min<int>(cursor, lines[currentline].length());
                        }
                    break;

                    case 80: // DOWN
                    if (currentline + 1 < static_cast<int>(lines.size())) {
                        currentline++;
                        cursor = min<int>(cursor, lines[currentline].length());
                    }
                    break;

                    case 75: // LEFT
                     if (cursor > 0) {
                        cursor--;
                    } else if (currentline > 0) {
                        currentline--;
                        cursor = lines[currentline].length();
                    }
                    break;

                    case 77: // RIGHT
                        if (cursor < static_cast<int>(lines[currentline].length())) {
                            cursor++;
                        } 
                        else if (currentline + 1 < static_cast<int>(lines.size())) {
                         currentline++;
                         cursor = 0;
                        }
                    break;

                    case 83: // DELETE
                        if (cursor > 0) {
                           lines[currentline].erase(cursor - 1, 1);
                            cursor--;
                        }
                        else if (currentline > 0) {
                            int prevLen = lines[currentline - 1].length();
                            lines[currentline - 1] += lines[currentline];
                            lines.erase(lines.begin() + currentline);
                            currentline--;
                            cursor = prevLen;
                            }
                        modified = true;
                    break;
                 }
            }
        break;

            default:
                if (ch >= 32 && ch <= 126) {
                    if (cursor <= static_cast<int>(lines[currentline].length())) {
                    lines[currentline].insert(cursor, 1, ch);
                    cursor++;
                        }
                    else {
                    lines[currentline].push_back(ch);
                    cursor = lines[currentline].length();
                    }
                modified = true;
            }
            break;
        }

        display(lines, currentline, cursor, filename);
    }
}

#endif