# FILE-MANAGEMENT-TOOL

*COMPANY*:CODTECH IT SOLUTIONS

*NAME*:DEVESH LAXMAN DOLAS

*INTERN ID*:CT04DG2484

*DOMAIN*:C++ Programming

*DURATION*: 4 WEEKS

*MENTER*:NEELA SANTOSH

#  Console-Based File Editor – C++ Application

This is a terminal-native text editor built in **C++** using low-level console APIs. It's designed to allow direct line-by-line editing of text files within a Windows command-line environment. Lightweight, intuitive, and modular—perfect for quick modifications, config tuning, or as a foundational tool for systems developmen

---

##  Features Summary

- Interactive console-based editing experience
- Visible in-text cursor (`|`) at the editing point
- Arrow key navigation across lines and characters
- Smart Backspace and Delete behaviors for accurate removal
- `Tab` inserts four spaces for indentation
- `Enter` creates a new line preserving content
- `Ctrl + S` for instant saving
- `ESC` triggers a save confirmation before exiting
- Modular class architecture for easy extension
- Flicker-free screen rendering with WinAPI
- Supports all ASCII printable characters (32–126)
-  Works for any `.txt` or text-based file (UTF-8 recommended)

---

##  Development Environment

**Programming Language**:  
- C++17 (Standard-compliant)

**Libraries & Headers**:
- `<conio.h>` → Raw keyboard input (`_getch()`), extended key parsing
- `<windows.h>` → Console buffer control, cursor manipulation
- `<fstream>` → File I/O stream handling
- `<vector>`, `<string>`, `<iostream>` → Core logic and buffer management

**Recommended IDEs**:  
- Code::Blocks  
- Visual Studio  
- VS Code with MinGW or MSVC

**Target Platform**:  
- Windows Terminal or CMD (PowerShell also supported)

---

##  Applicability

This editor is built for environments where graphical text editors are not available or practical. It's best suited for:

- Embedded firmware development
- Terminal-based log or config editing
- Lightweight deployment on developer systems
- Educational demonstrations of C++ input handling and buffer logic

Its minimal dependencies and robust input handling make it ideal for constrained setups and raw file manipulation tasks.

---

## 🛠️ Methodology for Usage

1. **Compilation**  
   Compile the code using your preferred C++ compiler:

   ```bash
   g++ -o file_editor main.cpp
2.**Direct Running .exe File**  
   Can be used Directly without any compiler by the .exe file:
   
    File_Editor.exe

## Output Screenshots

Here are visual previews of the editor in action:

- **Startup View**  
 ![Image](https://github.com/user-attachments/assets/5663fab8-c865-4028-b9f3-019c311d40d4)

- **Live Editing Example**  
  ![Editing](screenshots/editor_typing.png)

- **Exit with Save Prompt**  
  ![Exit Prompt](screenshots/editor_exit.png)
