#ifndef CUSTOMERMENU_H
#define CUSTOMERMENU_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Struct to represent an item in the customer menu
struct CustomerMenuItem {
    string category;
    string item;
    double cost;
};

// Function declarations
void customermenu();
void printcustomermenu(const CustomerMenuItem menuItems[], int size);

#endif // CUSTOMERMENU_H
