#include "goods-transaction.hpp"
#include "util.hpp"

#include <iomanip>
#include <iostream>
#include <ctime>
#include <sstream>
#include <string>

GoodsTransaction::GoodsTransaction(): goodsTransactionCount(0) {}

// Helper function to get current date and time
string GoodsTransaction::getCurrentDate() {
    time_t t = std::time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << (now->tm_year + 1900) << "-"
    << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
    << setw(2) << setfill('0') << now->tm_mday;
    return ss.str();
}

string GoodsTransaction::getCurrentTime() {
    time_t t = std::time(nullptr);
    tm* now = localtime(&t);
    stringstream ss;
    ss << setw(2) << setfill('0') << now->tm_hour << ":"
    << setw(2) << setfill('0') << now->tm_min << ":"
    << setw(2) << setfill('0') << now->tm_sec;
    return ss.str();
}

void GoodsTransaction::AddGoodsTransaction(const std::string& good, int alter, std::string& desc) {
    if (goodsTransactionCount >= MAX_GOODS_TRANSACTION) {
        std::cerr << "Error: Maximum transaction limit reached.\n";
        return;
    }

    ids[goodsTransactionCount] = goodsTransactionCount + 1; // Assign a unique ID to the transaction
    date[goodsTransactionCount] = getCurrentDate();
    time[goodsTransactionCount] = getCurrentTime();
    goods[goodsTransactionCount] = good;
    alteration[goodsTransactionCount] = alter;
    description[goodsTransactionCount] = desc;

    ++goodsTransactionCount; // Increment the transaction count

    std::cout << "Transaction added successfully!\n";
}

void GoodsTransaction::ViewGoodsTransaction(int currentPage, int pageSize) {
    if (goodsTransactionCount == 0) {
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("No transactions available");
        return;
    }

    int totalPages = (goodsTransactionCount + pageSize - 1) / pageSize;

    // Manually sort the transactions by ID in descending order using Bubble Sort
    for (int i = 0; i < goodsTransactionCount - 1; i++) {
        for (int j = 0; j < goodsTransactionCount - 1 - i; j++) {
            if (ids[j] < ids[j + 1]) {
                // Swap the IDs
                std::swap(ids[j], ids[j + 1]);
                // Swap the corresponding values in the other arrays
                std::swap(date[j], date[j + 1]);
                std::swap(time[j], time[j + 1]);
                std::swap(goods[j], goods[j + 1]);
                std::swap(alteration[j], alteration[j + 1]);
                std::swap(description[j], description[j + 1]);
            }
        }
    }

    const int idWidth = 5;
    const int dateWidth = 13;
    const int timeWidth = 13;
    const int goodsWidth = 20;
    const int alterationWidth = 12;
    const int descWidth = 30;

    const int tableWidth = idWidth + dateWidth + timeWidth + goodsWidth + alterationWidth + descWidth;

    cout << string(tableWidth + 3, '=') << endl;
    Utilities::printCenteredTitle("Goods Transactions", tableWidth + 3);
    cout << string(tableWidth + 3, '=') << endl;

    cout << "+" << string(idWidth, '-') 
         << "+" << string(dateWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(goodsWidth, '-') 
         << "+" << string(alterationWidth, '-') 
         << "+" << string(descWidth, '-') << "+" << endl;

    cout << "| " << setw(idWidth - 1) << left << "ID"
         << "| " << setw(dateWidth - 1) << left << "Date"
         << "| " << setw(timeWidth - 1) << left << "Time"
         << "| " << setw(goodsWidth - 1) << left << "Goods"
         << "| " << setw(alterationWidth - 1) << left << "Alteration"
         << "| " << setw(descWidth - 1) << left << "Description"
         << "|" << endl;

    cout << "+" << string(idWidth, '-')
         << "+" << string(dateWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(goodsWidth, '-') 
         << "+" << string(alterationWidth, '-') 
         << "+" << string(descWidth, '-') << "+" << endl;

    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < goodsTransactionCount; i++) {
        cout << "| " << setw(idWidth - 1) << left << ids[i]
             << "| " << setw(dateWidth - 1) << left << date[i]
             << "| " << setw(timeWidth - 1) << left << time[i]
             << "| " << setw(goodsWidth - 1) << left << goods[i]
             << "| " << setw(alterationWidth - 1) << left << alteration[i]
             << "| " << setw(descWidth - 1) << left << description[i]
             << "|" << endl;
    }

    cout << "+" << string(idWidth, '-')
         << "+" << string(dateWidth, '-') 
         << "+" << string(timeWidth, '-') 
         << "+" << string(goodsWidth, '-') 
         << "+" << string(alterationWidth, '-') 
         << "+" << string(descWidth, '-') << "+" << endl;

    cout << "Showing page " << currentPage << " of " << totalPages << "\n";
}