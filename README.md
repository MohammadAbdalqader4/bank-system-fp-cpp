# Bank Management System (C++)

An advanced, console-based Bank Management System developed in C++ using the Functional Programming paradigm. This project demonstrates robust problem-solving, structured data management, file-based data persistence, and an internal system permission mechanism.

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
This repository contains the clean source code. You can easily compile and run it using any standard C++ compiler (like `g++`).

1. Clone the repository to your local machine.
2. Open your terminal or command prompt in the project directory.
3. Compile the code using the following command:
   ```bash
   g++ bank-system-fp-cpp.cpp -o BankSystem
