# Pharmacy-Inventory-Management-System

A system designed to efficiently manage pharmacy operations, utilizing core Data structures and Algorithms concepts to handle patient registration, drug inventory and search operations.

# Features

- **Patient Management**: Register patients and manage queue for service.
- **Drug Inventory**: Register new drugs and track existing stock.
- **Expiry Management**: Identify and delete expired drugs from the system.
- **Reporting**:
    * Show the number of available drugs in a specific catagory.
    * Display total number of drugs and registerd patients.

# Data Structures Used

- **Binary Search Tree(BST)**: Used for fast insertion, deletion, and searching of drugs ($O(\log n)$ complexity)
- **Queue**: Used for managing patients in a First-In-First-Out(FIFO) basis.

# How to run the file

## Prerequisits
A C++ compiler (GCC/G++) is needed to run the following files.

## Windows
Open powershell in the project folder and run the following command
 ```powershell
 ./build.ps1
 ```

## Unix systems
Open terminal in the project folder and run the following commands.
```bash
chmod +x build.sh
./build.sh
```

