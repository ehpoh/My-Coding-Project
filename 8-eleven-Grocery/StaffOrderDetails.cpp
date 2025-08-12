#include "function.h"
#include <iostream>
#include <string>
using namespace std;

void stafforderdetails(char category, int item, int quantity) {
    
    string categoryname = " ";
    string itemname = " ";

    // category details
    switch (category) {
    case 'A':
    {
        categoryname = "Dairy & Eggs";

        switch (item) {
        case 1:
        {
            itemname = "Milk (1 liter)";
            break;
        }
        case 2:
        {
            itemname = "Eggs (1 dozen)";
            break;
        }
        case 3:
        {
            itemname = "Butter (250 grams)";
            break;
        }
        default:
        {
            itemname = "Unknown";
            break;
        }
        }
        break;
    }
    case 'B':
    {
        categoryname = "Protein";
        itemname = (item == 1) ? "Chicken Breasts (1 kilogram)" : "Unknown";
        break;
    }
    case 'C':
    {
        categoryname = "Pantry Staples";

        switch (item) {
        case 1:
        {
            itemname = "Rice (10 kilograms)";
            break;
        }
        case 2:
        {
            itemname = "Olive Oil (500 milliliters)";
            break;
        }
        default:
        {
            itemname = "Unknown";
            break;
        }
        }
        break;
    }
    case 'D':
    {
        categoryname = "Produce";

        switch (item) {
        case 1:
        {
            itemname = "Tomatoes (1 kilogram)";
            break;
        }
        case 2:
        {
            itemname = "Spinach (1 bunch)";
            break;
        }
        case 3:
        {
            itemname = "Apples (1 kilogram)";
            break;
        }
        default:
        {
            itemname = "Unknown";
            break;
        }
        }
        break;
    }
    case 'E':
    {
        categoryname = "Bakery";
        itemname = (item == 1) ? "Bread (1 loaf)" : "Unknown";
        break;
    }
    default:
    {
        categoryname = "Unknown";
        itemname = "Unknown";
        break;
    }
    }
    
    cout << endl << "Order details:" << endl;
    cout << "Category >> " << categoryname << endl;
    cout << "Item >> " << itemname << endl;
    cout << "Quantity >> " << quantity << endl;
}
