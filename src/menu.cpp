#include "menu.hpp"
#include "util.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

Menu::Menu(): menuCount(0) {}

void Menu::AddMenu(const string& menuName, double price, const string ingredientList[], int ingredientCount){
    if(menuCount >= MAX_MENU){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add more Item. Temporary storage limit reached.");
        return;
    }

    if(menuName.empty() && menuName==""){
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("Cannot add Item without name.");
        return;
    }

    
    string lowerCategoryName = menuName;
    transform(lowerCategoryName.begin(), lowerCategoryName.end(), lowerCategoryName.begin(), ::tolower);

    for(int i = 0; i < menuCount; i++) {
        string lowerExistingName = menus[i];
        transform(lowerExistingName.begin(), lowerExistingName.end(), lowerExistingName.begin(), ::tolower);
        if(lowerExistingName == lowerCategoryName) {
            Utilities::clearScreen();
            Utilities::pressAnyKeyToContinue("Menu with this name already exists.");
            return;
        }
    }

    ids[menuCount] = menuCount+1;
    menus[menuCount] = menuName;
    prices[menuCount] = price;

    for (int i = 0; i < ingredientCount; ++i) {
        ingredients[menuCount][i] = ingredientList[i];
    }

    // Fill the remaining ingredients with empty strings
    for (int i = ingredientCount; i < MAX_INGREDIENT; ++i) {
        ingredients[menuCount][i] = "";
    }

    menuCount++;
    Utilities::pressAnyKeyToContinue("Item added successfully...");
}

void Menu::ViewMenus(int currentPage, int pageSize) {
    if (menuCount == 0) {
        Utilities::clearScreen();
        Utilities::pressAnyKeyToContinue("No menu items available.");
        return;
    }

    int totalPages = (menuCount + pageSize - 1) / pageSize;

    const int idWidth = 5;
    const int nameWidth = 30;
    const int priceWidth = 15;

    const int tableWidth = idWidth + nameWidth + priceWidth;

    cout << string(tableWidth + 3, '=') << endl;
    Utilities::printCenteredTitle("Menu Items", tableWidth + 3);
    cout << string(tableWidth + 3, '=') << endl;

    cout << "+" << string(idWidth, '-')
         << "+" << string(nameWidth, '-') 
         << "+" << string(priceWidth, '-') << "+" << endl;

    cout << "| " << setw(idWidth - 1) << left << "ID"
         << "| " << setw(nameWidth - 1) << left << "Name"
         << "| " << setw(priceWidth - 1) << left << "Price"
         << "|" << endl;

    cout << "+" << string(idWidth, '-')
         << "+" << string(nameWidth, '-') 
         << "+" << string(priceWidth, '-') << "+" << endl;

    for (int i = (currentPage - 1) * pageSize; i < currentPage * pageSize && i < menuCount; i++) {
        cout << "| " << setw(idWidth - 1) << left << ids[i]
             << "| " << setw(nameWidth - 1) << left << menus[i]
             << "| " << setw(priceWidth - 1) << fixed << setprecision(2) << left << prices[i]
             << "|" << endl;
    }

    cout << "+" << string(idWidth, '-')
         << "+" << string(nameWidth, '-') 
         << "+" << string(priceWidth, '-') << "+" << endl;

    cout << "Showing page " << currentPage << " of " << totalPages << endl;
}

std::string Menu::GetMenuName(int menuID) const {
    // Search for the categoryID in the ids array
    for (int i = 0; i < menuCount; ++i) {
        if (ids[i] == menuID) {
            return menus[i];
        }
    }
    // If not found, throw an exception
    throw std::out_of_range("Category ID is out of range");
}

double Menu::GetMenuPrice(int MenuID) {
    for (int i = 0; i < menuCount; ++i) {
        if (ids[i] == MenuID) {
            return prices[i];
        }
    }
    // If not found, throw an exception
    throw std::out_of_range("Category ID is out of range");
}

const string* Menu::GetIngredients(int MenuID) {
    for (int i = 0; i < menuCount; ++i) {
        if (ids[i] == MenuID) {
            return ingredients[i];
        }
    }
    return nullptr; // Return nullptr if MenuID is not found
}