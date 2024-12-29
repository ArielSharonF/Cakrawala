#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>

using namespace std;

class Menu {
    public:
        static const int MAX_MENU = 100;
        static const int MAX_INGREDIENT = 20;
        int menuCount;

        Menu();
        void AddMenu(const string& menu, double price, const string ingredientList[], int ingredientCount);
        void ViewMenus(int currentPage, int pageSize);
        string GetMenuName(int MenuID) const;
        double GetMenuPrice(int MenuID);
        const string* GetIngredients(int MenuID);
        
    private:
        int ids[MAX_MENU];
        string menus[MAX_MENU];
        double prices[MAX_MENU];
        string ingredients[MAX_MENU][MAX_INGREDIENT];
};

#endif