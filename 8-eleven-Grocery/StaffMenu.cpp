#include "Staff.h"

// Define the array of menu items
MenuItem menuItems[NUM_MENU_ITEMS] = {
    {"[A] Dairy & Eggs", "  [1] Milk (1 liter)              ", 1, 15.75},
    {"[A] Dairy & Eggs", "  [2] Eggs (1 dozen)              ", 1, 11.25},
    {"[A] Dairy & Eggs", "  [3] Butter (250 gram)           ", 1, 13.50},
    {"[B] Protein", "       [1] Chicken Breasts (1 kilogram)", 1, 22.50},
    {"[C] Pantry Staples", "[1] Rice (10 kilograms)         ", 1, 45.00},
    {"[C] Pantry Staples", "[2] Olive oil (500 milliliters) ", 1, 13.50},
    {"[D] Produce", "       [1] Tomatoes (1 kilogram)       ", 1, 13.50},
    {"[D] Produce", "       [2] Spinach (1 bunch)           ", 1,  9.00},
    {"[D] Produce", "       [3] Apples (1 kilogram)         ", 1, 18.00},
    {"[E] Bakery ", "       [1] Bread (1 loaf)              ", 1, 11.25}
};

// Print a single row for a menu item
void printrow(const MenuItem& item) {
    cout << left << setw(17) << " " << item.category
        << left << setw(10) << " " << item.item
        << "     " << item.quantity
        << setw(10) << " " << fixed << setprecision(2) << item.cost
        << endl;
}

// Display the staff menu
void displaystaffmenu() {
    
    // Print table header
    cout << setw(20) << " " << left << setw(20) << "Category"
        << left << setw(5) << " " << "Item"
        << setw(30) << " " << "Quantity"
        << setw(5) << " " << "Cost (RM)"
        << endl;

    // Print separator
    cout << setw(17) << " " << string(20 + 35 + 15 + 15, '-') << endl;

    // Print each item in the menu
    for (int i = 0; i < NUM_MENU_ITEMS; ++i) {
        printrow(menuItems[i]);
    }

    cout << endl << endl;
}
