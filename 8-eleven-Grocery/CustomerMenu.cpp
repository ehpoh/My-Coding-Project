#include "Customer.h"

// Define the array of customer menu items
CustomerMenuItem customerMenuItems[] = {
    {"[A] Dairy & Eggs",   "[1] Milk (1 liter) (x1)              ", 15.75},
    {"[A] Dairy & Eggs",   "[2] Eggs (1 dozen) (x1)              ", 11.25},
    {"[A] Dairy & Eggs",   "[3] Butter (250 gram) (x1)           ", 13.50},
    {"[B] Protein",        "[1] Chicken Breasts (1 kilogram) (x1)", 22.50},
    {"[C] Pantry Staples", "[1] Rice (10 kilograms) (x1)         ", 45.00},
    {"[C] Pantry Staples", "[2] Olive oil (500 milliliters) (x1) ", 13.50},
    {"[D] Produce",        "[1] Tomatoes (1 kilogram) (x1)       ", 13.50},
    {"[D] Produce",        "[2] Spinach (1 bunch) (x1)           ", 9.00},
    {"[D] Produce",        "[3] Apples (1 kilogram) (x1)         ", 18.00},
    {"[E] Bakery",         "[1] Bread (1 loaf) (x1)              ", 11.25}
};

// Number of items in the customer menu
const int NUM_CUSTOMER_MENU_ITEMS = sizeof(customerMenuItems) / sizeof(CustomerMenuItem);

// Print the customer menu
void customermenu() {
    cout << setw(5) << " " << "Category" << setw(45) << " " << "Cost(RM)" << endl;
    cout << setw(3) << " " << setfill('-') << setw(70) << "-" << setfill(' ') << endl;

    // Print menu items based on their category
    printcustomermenu(customerMenuItems, NUM_CUSTOMER_MENU_ITEMS);

    cout << endl << endl;
}

// Print customer menu items
void printcustomermenu(const CustomerMenuItem menuItems[], int size) {
    string currentCategory;

    for (int i = 0; i < size; ++i) {
        if (menuItems[i].category != currentCategory) 
        {
            if (!currentCategory.empty()) 
            {
                // Print a blank line before the next category
                cout << endl;
            }
            
            // Print the new category header
            cout << setw(5) << " " << menuItems[i].category << ":" << endl;
            
            // Update the current category
            currentCategory = menuItems[i].category;
        }
        
        // Print the item
        cout << setw(7) << " " << menuItems[i].item
            << setw(20) << fixed << setprecision(2) << menuItems[i].cost
            << endl;
    }
}
