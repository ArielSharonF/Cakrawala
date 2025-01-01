#include "transaction.hpp"

#include <iomanip>
#include <iostream>

Transaction::Transaction(): transactionCount(0) {}

void Transaction::AddTransaction(const std::string& description, int quantity, double cost) {
    if (transactionCount >= MAX_TRANSACTION) {
        std::cerr << "Error: Maximum transaction limit reached.\n";
        return;
    }

    ids[transactionCount] = transactionCount + 1; // Assign a unique ID to the transaction
    descriptions[transactionCount] = description;
    quantities[transactionCount] = quantity;
    costs[transactionCount] = cost;

    ++transactionCount; // Increment the transaction count

    std::cout << "Transaction added successfully!\n";
}

void Transaction::ViewTransactions(int currentPage, int pageSize) {
    if (transactionCount == 0) {
        // Utilities::clearScreen();
        // Utilities::pressAnyKeyToContinue("No transactions available");
        cout << "No transactions available.\n";
        return;
    }

    int totalPages = (transactionCount + pageSize - 1) / pageSize;

    // Sort the transactions by ID in descending order using Bubble Sort
    for (int i = 0; i < transactionCount - 1; i++) {
        for (int j = 0; j < transactionCount - 1 - i; j++) {
            if (ids[j] < ids[j + 1]) {
                // Swap the IDs
                std::swap(ids[j], ids[j + 1]);
                // Swap the corresponding values in the other arrays
                std::swap(descriptions[j], descriptions[j + 1]);
                std::swap(quantities[j], quantities[j + 1]);
                std::swap(costs[j], costs[j + 1]);
            }
        }
    }

    const int idWidth = 5;
    const int descriptionWidth = 30;
    const int quantityWidth = 15;
    const int costWidth = 15;

    const int tableWidth = idWidth + descriptionWidth + quantityWidth + costWidth;

    cout << string(tableWidth + 3, '=') << endl;
    cout << "| " << setw(tableWidth + 1) << left << "Transactions" << " |" << endl;
    cout << string(tableWidth + 3, '=') << endl;

    cout << "+" << string(idWidth, '-') 
         << "+" << string(descriptionWidth, '-')
         << "+" << string(quantityWidth, '-')
         << "+" << string(costWidth, '-') << "+" << endl;

    cout << "| " << setw(idWidth - 1) << left << "ID"
         << "| " << setw(descriptionWidth - 1) << left << "Description"
         << "| " << setw(quantityWidth - 1) << left << "Quantity"
         << "| " << setw(costWidth - 1) << left << "Cost"
         << "|" << endl;

    cout << "+" << string(idWidth, '-')
         << "+" << string(descriptionWidth, '-')
         << "+" << string(quantityWidth, '-')
         << "+" << string(costWidth, '-') << "+" << endl;

    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < transactionCount; i++) {
        cout << "| " << setw(idWidth - 1) << left << ids[i]
             << "| " << setw(descriptionWidth - 1) << left << descriptions[i]
             << "| " << setw(quantityWidth - 1) << left << quantities[i]
             << "| " << fixed << setprecision(2) << setw(costWidth - 1) << left << costs[i]
             << "|" << endl;
    }

    cout << "+" << string(idWidth, '-')
         << "+" << string(descriptionWidth, '-')
         << "+" << string(quantityWidth, '-')
         << "+" << string(costWidth, '-') << "+" << endl;

    cout << "Showing page " << currentPage << " of " << totalPages << "\n";
}

double Transaction::GetSUMCost() {
    double totalCost = 0.0;
    for (int i = 0; i < transactionCount; i++) {
        totalCost += costs[i];
    }
    return totalCost;
}

double Transaction::GetExpenses() {
    double totalExpenses = 0.0;
    for (int i = 0; i < transactionCount; ++i) {
        if (quantities[i] == 0){
            totalExpenses += costs[i];  // Add cost to total
        }
    }

    return totalExpenses;
}

void Transaction::AddExpenses(const std::string& description, double cost) {
    if (transactionCount >= MAX_TRANSACTION) {
        std::cerr << "Error: Maximum transaction limit reached.\n";
        return;
    }

    ids[transactionCount] = transactionCount + 1; // Assign a unique ID to the transaction
    descriptions[transactionCount] = description;
    quantities[transactionCount] = 0;
    costs[transactionCount] = cost;

    ++transactionCount; // Increment the transaction count

    std::cout << "Transaction added successfully!\n";
}