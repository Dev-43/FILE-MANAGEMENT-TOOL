#ifndef EDITFILE_H
#define EDITFILE_H
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <algorithm>

using namespace std;

// Small autosave context passed explicitly to the editor functions
struct AutosaveContext {
    thread worker;
    mutex mtx;
    condition_variable cv;
    atomic<bool> running{false};
    atomic<bool> dirty{false};
    string filename;
};

inline void clearScreen() {
    // Fallback portable clear for Windows consoles. Using system('cls') keeps
    // this header free of heavy Windows headers that can conflict with C++
    // standard headers in some toolchains.
    system("cls");
}

inline string cursor_position(const string& line, int pos) {
    if (pos >= 0 && static_cast<size_t>(pos) <= line.length())
        return line.substr(0, pos) + "|" + line.substr(pos);
    else
        return line + "|";
}

inline void display(const vector<string>& lines, int currentline, int cursor, const string& filename, bool modified) {
    clearScreen();
    cout << "Editing: " << filename;
    if (modified) cout << " *";
    cout << "  |  Ctrl+S = Save, ESC = Exit\n\n";

    for (size_t i = 0; i < lines.size(); ++i) {
        if (static_cast<int>(i) == currentline)
            cout << ">" << i + 1 << "  " << cursor_position(lines[i], cursor) << endl;
        else
            cout << " " << i + 1 << "  " << lines[i] << endl;
    }
}

inline bool save_file_to_disk(const string& filename, const vector<string>& lines) {
    ofstream file(filename);
    if (!file.is_open()) return false;
    for (const auto& ln : lines) file << ln << '\n';
    file.close();
    return true;
}

// Start autosave thread; it watches the `dirty` flag in context and writes when set.
inline void start_autosave(AutosaveContext& ctx, vector<string>* lines_ptr) {
    ctx.running.store(true);
    ctx.worker = thread([&ctx, lines_ptr]() {
        unique_lock<mutex> lk(ctx.mtx);
        while (ctx.running.load()) {
            ctx.cv.wait_for(lk, chrono::milliseconds(200)); // wake every 200ms or when notified
            if (!ctx.running.load()) break;
            if (ctx.dirty.load()) {
                // copy for thread-safety
                vector<string> snapshot = *lines_ptr;
                string fname = ctx.filename;
                // release lock while writing
                lk.unlock();
                save_file_to_disk(fname, snapshot);
                ctx.dirty.store(false);
                lk.lock();
            }
        }
    });
}

inline void stop_autosave(AutosaveContext& ctx) {
    ctx.running.store(false);
    ctx.cv.notify_all();
    if (ctx.worker.joinable()) ctx.worker.join();
}

// The main functional editor: stateless in that it operates on local data and
// passes the autosave context explicitly.
inline void edit_file(const string& filename_in) {
    string filename = filename_in;
    vector<string> lines;
    string line;
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    while (getline(infile, line)) lines.push_back(line);
    infile.close();
    if (lines.empty()) lines.push_back("");

    int currentline = static_cast<int>(lines.size()) - 1;
    int cursor = static_cast<int>(lines[currentline].length());
    bool modified = false;

    AutosaveContext autosave_ctx;
    autosave_ctx.filename = filename;
    start_autosave(autosave_ctx, &lines);

    display(lines, currentline, cursor, filename, modified);

    while (true) {
        unsigned char ch = _getch();
        bool redraw = false;

        if (ch == 19) { // CTRL+S manual save
            save_file_to_disk(filename, lines);
            modified = false;
            autosave_ctx.dirty.store(false);
            redraw = true;
        } else if (ch == 9) { // TAB
            lines[currentline].insert(cursor, "    ");
            cursor += 4;
            modified = true;
            autosave_ctx.dirty.store(true);
            autosave_ctx.cv.notify_one();
            redraw = true;
        } else if (ch == 27) { // ESC
            stop_autosave(autosave_ctx);
            if (modified) {
                cout << "\nYou have unsaved changes. Do you want to save before exiting? (Y/N): ";
                char choice;
                cin >> choice;
                if (choice == 'Y' || choice == 'y') {
                    save_file_to_disk(filename, lines);
                    cout << "File saved successfully. Exiting...\n";
                } else {
                    cout << "Exiting without saving changes.\n";
                }
            }
            return;
        } else if (ch == 13) { // ENTER
            string newLine = "";
            int len = static_cast<int>(lines[currentline].length());
            if (cursor <= len) newLine = lines[currentline].substr(cursor);
            lines[currentline] = lines[currentline].substr(0, min(cursor, len));
            lines.insert(lines.begin() + currentline + 1, newLine);
            currentline++;
            cursor = 0;
            modified = true;
            autosave_ctx.dirty.store(true);
            autosave_ctx.cv.notify_one();
            redraw = true;
        } else if (ch == 8) { // BACKSPACE
            if (cursor > 0) {
                lines[currentline].erase(cursor - 1, 1);
                cursor--;
            } else if (currentline > 0) {
                int prevLen = static_cast<int>(lines[currentline - 1].length());
                lines[currentline - 1] += lines[currentline];
                lines.erase(lines.begin() + currentline);
                currentline--;
                cursor = prevLen;
            }
            modified = true;
            autosave_ctx.dirty.store(true);
            autosave_ctx.cv.notify_one();
            redraw = true;
        } else if (ch == 224) {
            unsigned char arrow = _getch();
            if (arrow == 72 && currentline > 0) { // UP
                currentline--;
                cursor = min<int>(cursor, static_cast<int>(lines[currentline].length()));
                redraw = true;
            } else if (arrow == 80 && currentline + 1 < static_cast<int>(lines.size())) { // DOWN
                currentline++;
                cursor = min<int>(cursor, static_cast<int>(lines[currentline].length()));
                redraw = true;
            } else if (arrow == 75) { // LEFT
                if (cursor > 0) cursor--;
                else if (currentline > 0) {
                    currentline--;
                    cursor = static_cast<int>(lines[currentline].length());
                }
                redraw = true;
            } else if (arrow == 77) { // RIGHT
                if (cursor < static_cast<int>(lines[currentline].length())) cursor++;
                else if (currentline + 1 < static_cast<int>(lines.size())) {
                    currentline++;
                    cursor = 0;
                }
                redraw = true;
            } else if (arrow == 83) { // DELETE
                if (cursor > 0) {
                    lines[currentline].erase(cursor - 1, 1);
                    cursor--;
                } else if (currentline > 0) {
                    int prevLen = static_cast<int>(lines[currentline - 1].length());
                    lines[currentline - 1] += lines[currentline];
                    lines.erase(lines.begin() + currentline);
                    currentline--;
                    cursor = prevLen;
                }
                modified = true;
                autosave_ctx.dirty.store(true);
                autosave_ctx.cv.notify_one();
                redraw = true;
            }
        } else if (ch >= 32 && ch <= 126) {
            if (cursor <= static_cast<int>(lines[currentline].length())) {
                lines[currentline].insert(cursor, 1, ch);
                cursor++;
            } else {
                lines[currentline].push_back(ch);
                cursor = static_cast<int>(lines[currentline].length());
            }
            modified = true;
            autosave_ctx.dirty.store(true);
            autosave_ctx.cv.notify_one();
            redraw = true;
        }

        if (redraw) display(lines, currentline, cursor, filename, modified);
    }
}
#endif 