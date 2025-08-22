📂 FILE EDITOR – Command-Line File Management Tool
--------------------------------------------------

📌 DESCRIPTION
A lightweight, user-friendly C++ console application designed for editing, reading, and managing text files right from the terminal. Built with modular header files and a clean UI flow, this tool is ideal for small tasks, project notes, or learning file system handling in C++.

👨‍💻 AUTHOR
DEVESH

📦 FEATURES
- ✅ Edit existing text files line-by-line
- 📖 Read and display file content with proper formatting
- 🗑️ Preview before delete: Safety-first deletion with confirmation
- 🎯 Robust input validation and clean menu interface
- 💡 Statically linked – requires no compiler or DLLs

🛠 HOW TO USE
1. **Launch** the editor by double-clicking `File_Editor.bat`  
   (Or open `CMD` and run `File_Editor.exe`)

2. **Menu Options:**
   - `1. Edit File` – Search and modify contents interactively
   - `2. Read File` – Display any file's contents
   - `3. Delete File` – Review and confirm deletion
   - `4. Exit` – Close the application

3. **Editing Controls:**
   - ⬆️/⬇️ Arrow keys: Move cursor up/down lines
   - ⬅️/➡️ Arrow keys: Move cursor within a line
   - 📝 Type to insert or edit content at the current cursor position
   - ❌ `Backspace`: Remove characters
   - 💾 `Ctrl + S`: Save your changes
   - 🔙 `Esc`: Exit editing mode (you’ll be prompted to save if needed)

4. **Read Mode:**  
   Simply displays content—no accidental editing, safe for reviewing.

5. **Delete Mode:**  
   Lets you preview before confirming deletion—no file is lost without explicit confirmation.

⚠️ THINGS TO KNOW WHILE EDITING
- All edits are **in-memory** until saved
- You can navigate freely using arrow keys
- Use `Ctrl + S` anytime to save progress immediately
- Exiting without saving will discard your changes
- File path errors (nonexistent or invalid names) will show prompts—just follow on-screen guidance
- The editor only works with **plain text files**

📁 INCLUDED FILES
- `File_Editor.exe` – The statically compiled executable
- `File_Editor.bat` – Double-click launcher for convenience
- `README.txt` – This instruction manual
- (Optional) Sample `.txt` files or folders you want to include

🚀 TROUBLESHOOTING
If you see a console flash and close immediately:
- Open `CMD`
- Navigate to this folder using `cd`
- Run `File_Editor.exe` manually to view any error messages

---

Enjoy editing with precision and peace of mind!
