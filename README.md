# 🗂️ FILE-MANAGEMENT-TOOL

**COMPANY**: CODTECH IT SOLUTIONS  
**NAME**: DEVESH LAXMAN DOLAS  
**INTERN ID**: CT04DG2484  
**DOMAIN**: C++ Programming  
**DURATION**: 4 WEEKS  
**MENTOR**: NEELA SANTOSH  

---

# 📝 Console-Based File Editor – C++ Application

A comprehensive console-native file editing and management tool written in **C++**, featuring real-time in-text editing, file search, file creation, and deletion. Designed for Windows terminals, it delivers powerful interaction through low-level APIs and efficient file handling through modular architecture.

---

## ✨ Features Summary

- ✅ Full-screen interactive text editing in terminal
- ✅ Live visible cursor (`|`) with accurate placement
- ✅ Arrow key navigation, tabbing, indentation
- ✅ Smart backspace/delete operations
- ✅ Line-by-line editing and insertion logic
- ✅ `Ctrl + S` to save instantly
- ✅ `ESC` to exit with save prompt
- ✅ Smooth, flicker-free rendering using WinAPI
- ✅ Search & create file if missing (`checkfile.h`)
- ✅ Delete file with confirmation (`deletefile.h`)
- ✅ Supports all printable ASCII characters (32–126)
- ✅ Modular, extendable class-based design

---

## 🛠️ Technology Stack

- **Language**: C++17
- **Platform**: Windows (CMD/PowerShell)
- **Compiler**: MinGW / MSVC / Code::Blocks / Visual Studio

### 📚 Key Libraries

| Header        | Purpose                              |
|---------------|--------------------------------------|
| `<windows.h>` | Screen control and cursor management |
| `<conio.h>`   | Keyboard event handling              |
| `<fstream>`   | File read/write                      |
| `<vector>`, `<string>`, `<iostream>` | Logic & structure |
---

## 🔍 Additional Utilities

### `checkfile.h` – Search & Create File
- Prompts user to search a file.
- If not found, allows creating a new file with rename option.

### `deletefile.h` – File Deletion Tool
- Prompts confirmation before removing a file.
- Uses C++ `remove()` function.

These tools make the editor more than just a viewer—it becomes a full management solution.

---

## 📁 Use Cases

- Terminal-based config editing
- Working in embedded or minimal environments
- Learning and teaching C++ I/O handling
- Developer productivity in CLI-based workflows
- Portable file manipulation tool

---

## 🚀 How to Use

### Option 1: Compile from Source
```bash
g++ -o file_editor main.cpp
./file_editor
```

### Option 2: Run Executable (No Compilation Needed)
```
File_Editor.exe
```

---

## 🖼️ Output Screenshots

### 🔹 Startup Interface  
![Image](https://github.com/user-attachments/assets/5663fab8-c865-4028-b9f3-019c311d40d4)

### 🔹 Real-time Text Editing  
![Image](https://github.com/user-attachments/assets/deef1ea8-d03d-48df-99fa-a381af2f0858)

### 🔹 Exit & Save Prompt  
![Image](https://github.com/user-attachments/assets/b517c744-2377-4c92-a20d-d5056eef87f9)

---

# ⚠️ Limitations – Console-Based File Editor

This document outlines the known limitations and constraints of the console-based file editor developed using C++ for Windows.

---

## ❌ No Mouse Support
- Only keyboard input is supported.
- Mouse interactions such as clicking or selecting text are not available.

## 📄 Line-Based Navigation Only
- Editor operates on a line-by-line basis.
- There is no scrolling or paging through content beyond console window size.

## 🧠 No Undo/Redo Functionality
- Once edits are made, they cannot be reverted.
- No history tracking of user changes.

## 📂 Single File Only
- Only one file can be opened and edited at a time.
- No multi-tab or multi-document support.

## ⛔ ASCII Only
- Only standard ASCII printable characters (32–126) are reliably supported.
- Unicode and UTF-8 multibyte characters may not render or save properly.

## 🗃️ Full File in Memory
- Entire file content is loaded into RAM.
- May struggle with very large files depending on system memory.

## 🖍️ No Syntax Highlighting
- Text appears as plain monochrome characters.
- No visual distinction for programming syntax.

## 📋 No Clipboard Integration
- Copy/Cut/Paste operations are not supported.
- Users must type all input manually.

## 🪟 Windows-Only
- Depends on `windows.h` and `conio.h`.
- Not compatible with Linux/macOS without rewriting.

## 🔐 No File Locking
- Does not detect or prevent concurrent edits from other applications.
- May lead to data loss if a file is edited in multiple places simultaneously.

## ⚠️ Minimal Error Handling
- Crashes or undefined behavior may occur for corrupted files or invalid inputs.
- Lacks robust exception handling or input validation.

## 🧾 No Line Wrapping
- Long lines extend beyond console width without wrapping.
- Requires horizontal navigation to view full line content.

---

## 💡 Suggestions for Future Improvements
- Add undo/redo system with history stack.
- Implement clipboard support and copy/paste shortcuts.
- Improve Unicode handling and cross-platform compatibility.
- Add syntax highlighting for common file types.
- Introduce file-size optimizations for large files.

---




## 📝 Future Improvements

- Add GUI support using Qt or Dear ImGui.
- Add encryption support for secure `.huff` files.
- Add decompression support for external Huffman files.
- Cross-platform support for Linux/macOS.



## 🙌 Credits

Built by Devesh Dolas for educational and practical demonstration of FileHandling in C++.

---

## 💬 Contact

For suggestions, bugs, or collaboration:  
**Email:** deveshdolas9@gmail.com 
