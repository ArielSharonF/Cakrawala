#ifndef TRANSACTION_HPP
#define TRANASCTION_HPP

#include <iostream>
#include <string>

using namespace std;

class Transaction {
    public:
        static const int MAX_TRANSACTION = 200;
        int transactionCount;

        Transaction();
        void AddTransaction(const string& description, int quantity, double costs);
        void ViewTransactions(int currentPage, int pageSize);
        double GetSUMCost();
        double GetExpenses();
        void AddExpenses(const string& description, double costs);

    private:
        int ids[MAX_TRANSACTION];
        string descriptions[MAX_TRANSACTION];
        int quantities[MAX_TRANSACTION];
        double costs[MAX_TRANSACTION];
};

#endif