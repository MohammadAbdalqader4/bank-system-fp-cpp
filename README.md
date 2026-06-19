# Bank Management System (C++)

An advanced, console-based Bank Management System developed in C++ using the Functional Programming paradigm. This project demonstrates robust problem-solving, structured data management, file-based data persistence, and an internal system permission mechanism.

## 📁 Project Structure
This repository contains the complete project solution, including Visual Studio build and configuration files (`.slnx`, `.vcxproj`, etc.) alongside the core source code for seamless execution and development in Windows environments.

## ✨ Core Features
- **Client Management (CRUD):** Full capability to Add, Find, Update, and Delete client records securely.
- **Advanced Permission System:** Implements user access control and authorization using **Bitwise Flags** (`enum` masks) to dynamically restrict or grant access to specific admin menus based on the logged-in user.
- **Data Persistence:** Fully integrated with external file storage (`ClientsFile.txt` and `Users.txt`) to save, parse, and retrieve client and user records in real-time.
- **Transactional Operations:** Supports core banking tasks including Deposits, Withdrawals, and comprehensive Total Balance tracking across all accounts.

## 🛠️ Concepts & Skills Demonstrated
- **Functional Programming:** Architecting modular, clean, and maintainable code using structured functions.
- **File I/O Handling:** Advanced reading, string parsing (splitting tokens), and updating text-based records.
- **Bitwise Logic:** Utilizing low-level bit manipulation for high-performance and lightweight authorization structures.

## 🚀 How to Run the Project

### Option 1: Using Visual Studio (Windows)
1. Open the `.slnx` or `.vcxproj` file directly inside Visual Studio.
2. Press `Ctrl + F5` to compile and launch the console application.

### Option 2: Using Standard C++ Compiler (Cross-Platform)
Navigate to the directory containing the source files and compile using any standard C++ compiler (e.g., g++):
```bash
# Compile the project
g++ BankProjectCourse8.cpp -o BankSystem

# Run the executable
./BankSystem
