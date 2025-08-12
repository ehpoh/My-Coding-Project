#ifndef STAFFMENU_H
#define STAFFMENU_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Struct to represent an item in the menu
struct MenuItem {
    string category;
    string item;
    int quantity;
    double cost;
};

// Function declarations
void displaystaffmenu();
void printrow(const MenuItem& item);

// Define a constant for the number of menu items
const int NUM_MENU_ITEMS = 10;

#endif // STAFFMENU_H
