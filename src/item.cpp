#include "item.hpp"
#include "util.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <regex>

using namespace std;

Item::Item(): itemCount(0) {}

bool Item::Validation(const string& input) {
    regex validRegex("^[a-zA-Z0-9 ]+$"); // Allows only letters, digits, and spaces
    return regex_match(input, validRegex);
}

void Item::AddItem(const string& itemName){
    if(itemCount >= MAX_ITEM){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add more Item. Temporary storage limit reached.");
        return;
    }

    if(itemName.empty() && itemName==""){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add Item without name.");
        return;
    } else if(itemName.length()<3){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add Item name less then 3 character.");
        return;
    } else if (!Validation(itemName)){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Item name cannot include special item.");
        return;
    }
       
    string lowerCategoryName = itemName;
    transform(lowerCategoryName.begin(), lowerCategoryName.end(), lowerCategoryName.begin(), ::tolower);

    for(int i = 0; i < itemCount; i++) {
        string lowerExistingName = names[i];
        transform(lowerExistingName.begin(), lowerExistingName.end(), lowerExistingName.begin(), ::tolower);
        if(lowerExistingName == lowerCategoryName) {
            Utilities::clearScreen();
            Utilities::pressAnyKeyToContinue("Item with this name already exists.");
            return;
        }
    }

    ids[itemCount] = itemCount+1;
    names[itemCount] = itemName;
    quantities[itemCount] = 0;

    itemCount++;
    Utilities::pressAnyKeyToContinue("Item added successfully...");
}

void Item::ViewItems(int currentPage, int pageSize){
    if(itemCount == 0) {
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("No categories available");
        return;
    }

    int totalPages = (itemCount + pageSize - 1) / pageSize;

    const int idWidth = 5;
    const int nameWidth = 30;
    const int quantityWidth = 15;

    const int tableWidth = idWidth+nameWidth+quantityWidth;

    cout << string(tableWidth+3, '=') << endl;
    Utilities::printCenteredTitle("Items", tableWidth+3);
    cout << string(tableWidth+3, '=') << endl;

    cout << "+" << string(idWidth, '-')
         << "+" << string(nameWidth, '-') << "+"
         << string(quantityWidth, '-') << "+" << endl;

    cout << "| " << setw(idWidth - 1) << left << "ID"
         << "| " << setw(nameWidth -1 ) << left << "Item Name"
         << "| " << setw(quantityWidth -1 ) << left << "Quantity"
         << "|" << endl;
    cout << "+" << string(idWidth, '-')
         << "+" << string(nameWidth, '-') << "+"
         << string(quantityWidth, '-') << "+" << endl;

    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < itemCount; i++) {
        cout << "| " << setw(idWidth - 1) << left << ids[i]
             << "| " << setw(nameWidth - 1) << left << names[i]
             << "| " << setw(quantityWidth - 1) << left << quantities[i]
             << "|" << endl;
    }

    cout << "+" << string(idWidth, '-')
         << "+" << string(nameWidth, '-') << "+"
         << string(quantityWidth, '-') << "+" << endl;
    
    cout << "Showing page " << currentPage << " of " << totalPages << "\n";
}


void Item::UpdateItemsQuantity(int itemID,  int itemQTY){
    for(int i=0;i<itemCount;i++){
        if(ids[i] == itemID) {
            quantities[i] += itemQTY;

            if(quantities[i] < 0){
                Utilities::clearScreen();
                Utilities::pressAnyKeyToContinue("Warning: Item Quantity cannot be negative. Adjusted to 0.");
                quantities[i] = 0;
            }

            Utilities::clearScreen();
            // string message = "Updated stock for " + names[i] + ": " + to_string(quantities[i]);
            // Utilities::pressAnyKeyToContinue(message);
            return;
        }
    }
    Utilities::clearScreen();
    Utilities::pressAnyKeyToContinue("Product ID " + to_string(itemID) + " not found!");
}

std::string Item::GetItemName(int itemID) {
    for (int i = 0; i < itemCount; ++i) {
        if (ids[i] == itemID) {
            return names[i];
        }
    }
    return "Item not found"; // Return a default message if itemID is not found
}
int Item::GetItemID(string itemName, int subtraction) {
    for (int i = 0; i < itemCount; ++i) {
        if (names[i] == itemName) {
            if (quantities[i] < subtraction) {
                return -1;
            } else {
                return ids[i];
            }
        }
    }
    return -1;
}
