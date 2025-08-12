#include "function.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Global Variables
OrderItem orderList[MAX_ORDERS];
int CusorderCount = 0;

void customerfunction() {
    char continueOrder = 'Y';

    while (continueOrder == 'Y' || continueOrder == 'y') {
        
        // Header
        cout << setfill('-') << setw(50) << "-" << setfill(' ') << " 8-Eleven Menu " << setfill('-') << setw(55) << "-" << setfill(' ') << endl << endl;

        // Call customer menu
        customermenu();

        // Display customer count and date
        cout << "Customer " << setw(98) << " ";
        cout << "20/July/2024" << endl << endl;

        // Display guide for ordering
        cout << "Order " << (CusorderCount + 1) << endl;
        displayguide();

        // Variables for order input
        char category = ' ';
        int item = 0;
        int quantity = 0;
        string tempItem;
        string tempquantity;

        // Validate Category
        while (true) {
            cout << "Enter Category >> ";
            getline(cin, tempItem);

            if (tempItem.length() == 1) 
            {
                category = tempItem[0];

                if (category == 'A' || category == 'B' || category == 'C' || category == 'D' || category == 'E') 
                {
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
        while (true) {
            cout << "Enter Item >> ";
            getline(cin, tempItem);

            if (tempItem == "1" || tempItem == "2" || tempItem == "3") 
            {
                item = stoi(tempItem);

                // Check if item is valid based on the category
                bool validItem = false;

                switch (category) {
                case 'A':
                case 'D':
                {
                    if (item >= 1 && item <= 3)
                    {
                        validItem = true;
                    }
                    break;
                }
                case 'B':
                case 'E':
                {
                    if (item == 1)
                    {
                        validItem = true;
                    }
                    break;
                }
                case 'C':
                {
                    if (item >= 1 && item <= 2)
                    {
                        validItem = true;
                    }
                    break;
                }
                default:
                {
                    validItem = false;
                    break;
                }
                }

                if (validItem) 
                {
                    break;
                }
                else 
                {
                    cout << RED << "Invalid Item for Category " << category << ". Please enter a valid item number." << RESET << endl;
                }
            }
            else 
            {
                cout << RED << "Invalid Input. Please enter 1, 2, or 3." << RESET << endl;
            }
        }

        // Validate Quantity
        while (true) {
            cout << "Enter Quantity >> ";
            getline(cin, tempquantity);

            bool isValidQuantity = true;

            for (char c : tempquantity) {
                if (!isdigit(c)) 
                {
                    isValidQuantity = false;
                    break;
                }
            }

            if (isValidQuantity && !tempquantity.empty()) 
            {
                quantity = stoi(tempquantity);

                if (quantity > 0) 
                {
                    break;
                }
                else
                {
                    cout << RED << "Quantity must be a positive number. Please re-enter again." << RESET << endl;
                }
            }
            else 
            {
                cout << RED << "Invalid Input. Please enter a positive number for quantity." << RESET << endl;
            }
        }

        // Determine price based on the item and category
        double price = 0.00;
        string itemName;

        switch (category) {
        case 'A':
        {
            if (item == 1)
            {
                price = 15.75;
                itemName = "Milk (1 liter)";
            }
            else if (item == 2)
            {
                price = 11.25;
                itemName = "Eggs (1 dozen)";
            }
            else if (item == 3)
            {
                price = 13.50;
                itemName = "Butter (250 gram)";
            }
            break;
        }
        case 'B':
        {
            if (item == 1)
            {
                price = 22.50;
                itemName = "Chicken Breasts (1 kilogram)";
            }
            break;
        }
        case 'C':
        {
            if (item == 1)
            {
                price = 45.00; 
                itemName = "Rice (10 kilograms)";
            }
            else if (item == 2)
            {
                price = 13.50;
                itemName = "Olive oil (500 milliliters)";
            }
            break;
        }
        case 'D':
        {
            if (item == 1)
            {
                price = 13.50;
                itemName = "Tomatoes (1 kilogram)";
            }
            else if (item == 2)
            {
                price = 9.00;
                itemName = "Spinach (1 bunch)";
            }
            else if (item == 3)
            {
                price = 18.00;
                itemName = "Apples (1 kilogram)";
            }
            break;
        }
        case 'E':
        {
            if (item == 1) 
            {
                price = 11.25;
                itemName = "Bread (1 loaf)";
            }
            break;
        }
        default:
        {
            cout << RED << "Invalid Category" << RESET << endl;
            break;
        }
        }

        // Add the order into order list
        OrderItem itemDetails;
        itemDetails.name = itemName;
        itemDetails.quantity = quantity;
        itemDetails.price = price;

        if (CusorderCount < MAX_ORDERS) 
        {
            orderList[CusorderCount++] = itemDetails;
        }
        else 
        {
            cout << RED << "Maximum order limit reached." << RESET << endl;
            break;
        }

        // Ask to continue order or not
        while (true) {
            cout << endl << "Continue Order? (Y/N) >> ";
            getline(cin, tempItem);

            if (tempItem.length() == 1) 
            {
                continueOrder = tempItem[0];

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

        // Generate invoice and payment method
        if (continueOrder == 'N' || continueOrder == 'n') 
        {
            double serviceChargeRate = 0.05;

            // Call customer invoice
            customerinvoice(orderList, CusorderCount, serviceChargeRate);

            // Call customer payment method
            //CustomerPaymentmethod();

            // Reset order count
            CusorderCount = 0;

            // Clear item record
            for (int i = 0; i < MAX_ORDERS; ++i) {
                orderList[i] = { "", 0, 0.0 };
            }
            Tprintlogo();
            userroleselection();

            break;
        }
    }
}
