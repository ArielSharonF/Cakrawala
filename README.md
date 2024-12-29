
# 📦 Management System - Simple Financial and Inventory Management System

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [User Roles and Functionalities](#user-roles-and-functionalities)
  - [Manager](#manager)
  - [Staff](#staff)
- [System Requirements](#system-requirements)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)

---

## 📖 Introduction
**Finance and Inventory Monitoring** is a simple management system designed to streamline transaction and stock management processes. This project allows **Manager** to manage product menu and stock inventory, while **Staff** can Place Order and Pay for Operational Expenses. It serves as a comprehensive yet straightforward solution for small-scale monitoring management.

This project is developed as part of **Kelompok 3 Algo 05**'s final assignment for (Algoritma dan Pemrograman) and is implemented in **C++** for its efficiency and versatility in handling structured data.

**Kelompok 3 Algo05**
1. Ariel Sharon Ferdinandus (24130500007)
2. Vienna Anselia Christie

---

## ✨Features
### Manager Features
1. **Add Stock**
   - Add new stock for the product.
   - View a list of stock.
   - Restock.
2. **Product Management**
   - Add new products with details such as price, and ingredients.
3. **Finance**
   - Monitoring Transaction.
   - Monitoring Profit
   - Monitoring Operational Expenses

### Staff Features
1. **Place Order**
   - Record an order for a product with available ingredients.
2. **Pay Operational**.
   - Record expanses for operational purposes.

---

## 👤 User Roles and Functionalities

### Manager
- **Inventory Management:**
  - Add new stock and Restocking.
- **Product Management:**
  - Add new products with details such as price, and ingredients.
- **Finance Management:**
  - Monitor and review all transactions.
  - View profit and expanses.

### Staff
- **Order:**
  - Record an order for a product with available ingredients.
- **Operational Payment:**
  - Record expanses for operational purposes.

---

## 🛠 System Requirements
- **Programming Language:** C++
- **Compiler:** Any C++ compiler that supports C++11 or higher (e.g., GCC, Clang, MSVC)
- **Operating System:** Windows, macOS, or Linux

---

## ⚙️ Setup and Installation
1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/ArielSharonF/Cakrawala_Algo5.git
   cd Cakrawala_Algo5
2. Compile the source code using your preferred C++ compiler. For example:
   ``` bash
   g++ -std=c++17 -Wall -Wextra -Werror -I./include -o build/RMS src/main.cpp src/item.cpp src/util.cpp src/transaction.cpp src/menu.cppsrc/main.cpp src/category.cpp src/product.cpp src/utilities.cpp
2. Run the compiled program
   ``` bash
   ./RMS

---

## 🚀 Usage
-   Launch the program and log in as either **Admin** or **Staff**.
-   Follow the interactive menu options to perform tasks based on your role:
    -   **Manager** can manage inventory, product, and monitoring transactions.
    -   **Staff** can do orders and pay operationals.
-   Use the corresponding menu options to input, view, and manage inventory data.


