#include "util.hpp"
#include "item.hpp"
#include "transaction.hpp"
#include "menu.hpp"

#include <iostream>
#include <limits>

using namespace std;

int main(){
    Item item;
    Transaction transaction;
    Menu menu;
    string role;

    bool running = true;
    int currentItemPage = 1;
    int currentTransactionPage = 1;
    int currentMenuPage = 1;
    int pageSize = 5;

    while (running)
    {
        start:
        cout << "Who are you?(manager/staff):";
        cin >> role ;  

        while (running)
        {   
            if (role=="manager"){
            //show transaction table
            transaction.ViewTransactions(currentTransactionPage, pageSize);
            
            //show sum of transaction(gain/loss)
            double total;
            total = transaction.GetSUMCost();
            cout << "\nTotal Keuntungan: " << total << endl;

            //show sum of Operational Expenses(qty==0)
            double expenses;
            expenses = transaction.GetExpenses();
            cout << "\nTotal Pengeluaran Operasional: " << expenses << endl;

            cout << "\nManager Menu:" << endl;
            cout << "1. Add New Item\n";
            cout << "2. Monitoring Stock\n";
            cout << "3. Stock In Items\n";
            cout << "4. Add Menu\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            char choice;
            cin >> choice;

            switch (choice){
                case '1': {
                    cout << string(30, '=') << endl;
                    Utilities::printCenteredTitle("Adding New Item", 30);
                    cout << string(30, '=') << endl;

                    string itemName;
                    cout << "Enter Item Name: ";
                    cin.ignore();
                    getline(cin, itemName);
                    item.AddItem(itemName);
                    Utilities::clearScreen();
                    break; 
                }   
                case '2':
                    do {
                        Utilities::clearScreen();

                        if(item.itemCount == 0){
                            Utilities::pressAnyKeyToContinue("No Items available to display.");
                            break;
                        }

                        item.ViewItems(currentItemPage, pageSize);

                        cout << "Navigate (n: next, p: previous, q: quit): ";
                        cin >> choice;

                        if (choice == 'n') {
                            if (currentItemPage < (item.itemCount + pageSize - 1) / pageSize) {
                                currentItemPage++;
                            } else {
                                Utilities::pressAnyKeyToContinue("You are already on the last page.");
                            }
                        } else if (choice == 'p') {
                            if (currentItemPage > 1) {
                                currentItemPage--;
                            } else {
                                Utilities::pressAnyKeyToContinue("You are already on the first page.");
                            }
                        }
                    } while (choice != 'q');
                    currentItemPage =1;
                    Utilities::clearScreen();
                    break;
                case '3': {
                    cout << "\nRecord Stock In:\n";
                    int itemID, itemQTY;
                    double cost;

                    do {
                        Utilities::clearScreen();
                        item.ViewItems(currentItemPage, pageSize);

                        cout << "Navigate (n: next, p: previous, q: quit)" << endl;
                        cout << "Select a product ID to Record Stock In: ";
                        cin >> choice;

                        if (choice == 'n') {
                            if (currentItemPage < (item.itemCount + pageSize - 1) / pageSize) {
                                currentItemPage++;
                            } else {
                                Utilities::pressAnyKeyToContinue("You are already on the last page.");
                            }
                        } else if (choice == 'p') {
                            if (currentItemPage > 1) {
                                currentItemPage--;
                            } else {
                                Utilities::pressAnyKeyToContinue("You are already on the first page.");
                            }
                        } else if (choice == 'q') {
                            break;
                        } else {
                            cin.putback(choice);
                            cin >> itemID;  
                            if(cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                Utilities::pressAnyKeyToContinue("Invalid Category ID. Try again.");
                                continue;
                            }
                            break;      
                        }
                    } while (true);
                    cout << "Enter quantity to add: ";
                    cin >> itemQTY;
                    cout << "Enter cost: ";
                    cin >> cost;
                    item.UpdateItemsQuantity(itemID, itemQTY);

                    string Desc = item.GetItemName(itemID);
                    cost = -std::abs(cost); // Convert cost to negative value
                    transaction.AddTransaction(Desc, itemQTY, cost);
                    break;
                }
                case '4': {
                    string menuName;
                    double price;
                    string ingredients[Menu::MAX_INGREDIENT];
                    int ingredientCount = 0;

                    cout << "Enter menu name: ";
                    cin.ignore();
                    getline(cin, menuName);

                    cout << "Enter menu price: ";
                    cin >> price;

                    for (int i = 0; i < Menu::MAX_INGREDIENT; i++) {
                        cout << "Enter ingredient " << i + 1 << " (or press Enter to finish): ";
                        cin.ignore();
                        getline(cin, ingredients[i]);

                        // Check if the user enters an empty string (finish input)
                        if (ingredients[i].empty()) {
                            break;  // Exit the loop if the user doesn't want to add more ingredients
                        }
                        ingredientCount++;
                    }
                
                    if (ingredientCount > Menu::MAX_INGREDIENT) {
                        cout << "Too many ingredients! Limit is " << Menu::MAX_INGREDIENT << ". Only the first " << Menu::MAX_INGREDIENT << " will be used." << endl;
                        ingredientCount = Menu::MAX_INGREDIENT;
                        break;
                    }
                    menu.AddMenu(menuName, price, ingredients, ingredientCount);
                    break;
                }
                case '0':
                    cout << "Exiting...\n";
                    goto start;
                
                default: 
                    cout << "Invalid choice, please try again.\n";
            }
        } else if (role=="staff"){

            cout << "\nStaff Menu:\n";
            cout << "1. Place Order\n";
            cout << "2. Pay Operational Expense\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            char choice;
            cin >> choice;

            switch (choice){
                case '1': {
                    cout << "\nSelect Menu:\n";
                    int menuID, orderQTY;
                    double cost;

                    do {
                        Utilities::clearScreen();
                        menu.ViewMenus(currentMenuPage, pageSize);

                        cout << "Navigate (n: next, p: previous, q: quit)" << endl;
                        cout << "Select a product ID to Order: ";
                        cin >> choice;

                        if (choice == 'n') {
                            if (currentMenuPage < (menu.menuCount + pageSize - 1) / pageSize) {
                                currentItemPage++;
                            } else {
                                Utilities::pressAnyKeyToContinue("You are already on the last page.");
                            }
                        } else if (choice == 'p') {
                            if (currentMenuPage > 1) {
                                currentMenuPage--;
                            } else {
                                Utilities::pressAnyKeyToContinue("You are already on the first page.");
                            }
                        } else if (choice == 'q') {
                            break;
                        } else {
                            cin.putback(choice);
                            cin >> menuID;  
                            if(cin.fail()) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                Utilities::pressAnyKeyToContinue("Invalid Category ID. Try again.");
                                continue;
                            }
                            break;      
                        }
                    } while (true);
                    cout << "Enter quantity order: ";
                    cin >> orderQTY;

                    string Order = menu.GetMenuName(menuID);
                    cost = std::abs(menu.GetMenuPrice(menuID));
                    const std::string* ingredientList = menu.GetIngredients (menuID);

                    if (ingredientList) { // Check if the pointer is not null
                        for (int i = 0; i < Menu::MAX_INGREDIENT; ++i) {
                            if (!ingredientList[i].empty()) {
                                int itemID = item.GetItemID(ingredientList[i], orderQTY);
                                if (itemID == -1){
                                    cout << "Bahan tidak tersedia!";
                                    break;
                                } else {
                                    int decrease = -std::abs(orderQTY);
                                    item.UpdateItemsQuantity(itemID, decrease);
                                }
                                std::cout << ingredientList[i] << std::endl; // Print or process the ingredient
                            } else {
                                break; // Stop when an empty slot is encountered
                            }
                        }
                    } else {
                        std::cout << "Invalid Menu ID." << std::endl;
                    }
                    // for (i = 0; i < /*jumlah array*/; i++){
                    //     int itemID = item.GetItemID(ingredients[i], orderQTY);
                    //     if (itemID == -1){
                    //         cout << "Bahan tidak tersedia!";
                    //         break;
                    //     } else {
                    //         int decrease = -std::abs(orderQTY);
                    //         item.UpdateItemsQuantity(itemID, decrease);
                    //     }
                    // }
                    
                    transaction.AddTransaction(Order, orderQTY, cost);

                    break;    
                }
                case '2':{
                    cout << "\nPay Operational Expenses:\n";
                    string operational;
                    double cost;

                    cout << "Enter The Operational: ";
                    cin.ignore();
                    getline(cin, operational);
                    cout << "Enter cost: ";
                    cin >> cost;
                    cost = -std::abs(cost); // Convert cost to negative value
                    transaction.AddExpenses(operational, cost);
                    break;
                }
                case '0':
                    cout << "Saving data and exiting...\n";
                    goto start;
                
                default: 
                    cout << "Invalid choice, please try again.\n";
                }
            } else {
                return 0;
            }
        }
    }
    return 0;
}
