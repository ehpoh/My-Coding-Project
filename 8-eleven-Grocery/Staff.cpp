#include <iostream>
#include <string>
#include <limits>
#include "function.h"
#include "Staff.h"

using namespace std;

// ANSI escape code color
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Global Variable
int orderCount = 1;

bool isValidNumber(const string& str) {
    
    if (str.empty()) return false;
    
    for (char c : str) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

void stafforderfunction(const string& date) {
    
    // Fixed-size arrays for storing order details
    int numItem[MAX_ORDERS] = { 0 }; 
    int quantity[MAX_ORDERS] = { 0 }; 
    char category[MAX_ORDERS] = { 0 }; 

    char continueOrder = 'Y';

    while (continueOrder == 'Y' || continueOrder == 'y') {
        
        // Call order menu
        cout << endl;
        displaystaffmenu();

        // Display guide for ordering
        cout << "Order " << orderCount << endl;
        displayguide();

        // Variables for order input
        char Category = ' ';
        int item = 0;
        int quan = 0;
        string tempInput;

        // Validate Category
        while (true) {
            cout << "Enter Category >> ";
            getline(cin, tempInput);

            if (tempInput.length() == 1) 
            {
                Category = tempInput[0];
                if (Category == 'A' || Category == 'B' || Category == 'C' || Category == 'D' || Category == 'E') 
                {
                    category[orderCount-1] = Category;
                    break;
                }
                else
                {
                    cout << RED << "Invalid Category. Please enter A, B, C, D, or E." << RESET << endl;
                }
            }
            else 
            {
                cout << RED << "Please enter a single character." << RESET << endl;
            }
        }

        // Validate Item based on Category
        bool validItem = false;
        while (!validItem) {
            cout << "Enter Item >> ";
            getline(cin, tempInput);

            if (!isValidNumber(tempInput)) 
            {
                cout << RED << "Invalid Input. Please enter a number for the item." << RESET << endl;
                continue;
            }

            item = stoi(tempInput);

            // Check if item is valid based on the category
            switch (Category) {
            case 'A':
            case 'D':
            {
                if (item >= 1 && item <= 3)
                    validItem = true;
                break;
            }
            case 'B':
            case 'E':
            {
                if (item == 1) 
                    validItem = true;
                break;
            }
            case 'C':
            {
                if (item == 1 || item == 2)
                    validItem = true;
                break;
            }
            }

            if (!validItem) 
            {
                cout << RED << "Invalid Item for Category " << Category << ". Please enter a valid item number." << RESET << endl;
            }
        }

        // Validate Quantity
        while (true) {
            cout << "Enter Quantity >> ";
            getline(cin, tempInput);

            if (!isValidNumber(tempInput)) 
            {
                cout << RED << "Invalid Input. Please enter a positive number for quantity." << RESET << endl;
                continue;
            }

            quan = stoi(tempInput);

            if (quan > 0) 
            {
                break;
            }
            else 
            {
                cout << RED << "Quantity must be a positive number. Please re-enter again." << RESET << endl;
            }
        }

        // Confirm the entered order details
        cout << endl << "Order details:" << endl;
        cout << "Category >> " << Category << endl;
        cout << "Item >> " << item << endl;
        cout << "Quantity >> " << quan << endl;

        // Store in arrays
        quantity[orderCount - 1] = quan;
        int numItemValue = -1;

        switch (Category) {
        case 'A':
        {
            if (item == 1)
            {
                numItemValue = 0;
            }
            else if (item == 2)
            {
                numItemValue = 1;
            }
            else if (item == 3)
            {
                numItemValue = 2;
            }
            break;
        }
        case 'B':
        {
            numItemValue = 3;
            break;
        }
        case 'C':
        {
            if (item == 1)
            {
                numItemValue = 4;
            }
            else if (item == 2) 
            {
                numItemValue = 5;
            }
            break;
        }
        case 'D':
        {
            if (item == 1) 
            {
                numItemValue = 6;
            }
            else if (item == 2)
            {
                numItemValue = 7;
            }
            else if (item == 3)
            {
                numItemValue = 8;
            }
            break;
        }
        case 'E':
        {
            numItemValue = 9;
            break;
        }
        default:
        {
            cout << RED << "Invalid Category" << RESET << endl;
            break;
        }
        }

        numItem[orderCount - 1] = numItemValue;

        // Ask continue order or not
        while (true) {
            cout << endl << "Continue Order? (Y/N) >> ";
            getline(cin, tempInput);

            if (tempInput.length() == 1) 
            {
                continueOrder = tempInput[0];
                if (continueOrder == 'Y' || continueOrder == 'y' || continueOrder == 'N' || continueOrder == 'n')
                {
                    break;
                }
                else 
                {
                    cout << RED << "Invalid input. Please enter Y or N." << RESET << endl;
                }
            }
            else 
            {
                cout << RED << "Please enter a single character." << RESET << endl;
            }
        }

        // Increment order count
        if (continueOrder == 'Y' || continueOrder == 'y') 
        {
            ++orderCount;
            if (orderCount > MAX_ORDERS) 
            {
                cout << RED << "Order limit reached." << RESET << endl;
                break;
            }
        }
        else if (continueOrder == 'N' || continueOrder == 'n') 
        {
            // Call invoice function
            generateinvoice(numItem, quantity, orderCount, category, date);
            break;
        }
    }
}
