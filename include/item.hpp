#ifndef STOCK_HPP
#define STOCK_HPP

#include <iostream>
#include <string>

using namespace std;

class Item {
    public:
        static const int MAX_ITEM = 100;
        int itemCount;

        Item();
        void AddItem(const std::string& name);
        void ViewItems(int currentPage, int pageSize);
        void UpdateItemsQuantity(int itemID, int itemQty);
        string GetItemName(int itemID);
        int GetItemID(std::string itemName, int subtraction);

    private:
        int ids[MAX_ITEM];
        string names[MAX_ITEM];
        int quantities[MAX_ITEM];

        bool Validation(const string& input);
};

#endif