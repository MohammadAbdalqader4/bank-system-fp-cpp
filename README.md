# Bank Management System (C++)

An advanced console-based Bank Management System developed in C++ using the Functional Programming paradigm. The project demonstrates structured software design, file-based data persistence, and a role-based permission system using bitwise logic.

## ✨ Core Features

* **Client Management (CRUD):** Add, search, update, and delete client records efficiently and securely.
* **Permission System:** Role-based access control using **bitwise flags (enum masks)** to manage admin privileges dynamically.
* **Data Persistence:** Uses external files (`ClientsFile.txt`, `Users.txt`) to store and retrieve client and user data.
* **Banking Operations:** Supports deposits, withdrawals, and real-time total balance tracking across all accounts.

## 🛠️ Concepts & Skills Demonstrated

* **Functional Programming:** Modular and structured function-based architecture.
* **File I/O Handling:** Reading, parsing, and updating structured text data.
* **Bitwise Logic:** Efficient permission handling using bitmask operations.
* **Data Structures:** Organized handling of client and user records.

## 📁 Project Structure

* `bank-system-fp-cpp.cpp` → Main source code containing the full system logic.
* `ClientsFile.txt` → Client database file storing account information and balances.
* `Users.txt` → User accounts file used for login authentication and permission control.

## 🚀 How to Run

1. Clone or download the repository.
2. Open a terminal in the project directory.
3. Compile the program:

```bash id="run1"
g++ bank-system-fp-cpp.cpp -o BankSystem
```

4. Run the program:

* Windows:

```bash id="run2"
BankSystem.exe
```

* Linux / macOS:

```bash id="run3"
./BankSystem
```

## 🧑‍💻 Developer

Developed by **Mohammad Abdalqader**.
