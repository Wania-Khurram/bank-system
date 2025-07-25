# 🏦 Bank Management System in C++

This is a simple **Bank Management System** built using **Object-Oriented Programming** in C++. It demonstrates dynamic memory allocation, inheritance, encapsulation, and basic banking operations such as deposit, withdraw, and money transfer.

---

## 📌 Features

- 📁 Base class: `bank` - Stores bank-level info (name, code, address)
- 🏢 Derived class: `branch` - Stores branch info (name, location)
- 👨‍💼 Class: `branchemployee` - Stores branch employee details
- 👤 Class: `customer` - Handles customer info and account operations
- 💸 Class: `transaction` - Represents transaction data
- 🔁 Dynamic memory allocation for customers and employees
- 💳 Banking operations:
  - Deposit
  - Withdraw
  - Transfer between customers

---
## 🖥️ How to Run

1. **Copy the Code**: Save it in a `.cpp` file, e.g., `bank_system.cpp`
2. **Compile**:
   ```bash
   g++ -o bank_system bank_system.cpp
