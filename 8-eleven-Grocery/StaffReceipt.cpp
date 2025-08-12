#include <iostream>
#include <iomanip>
#include <string>
#include "function.h"

using namespace std;

void receipt(const int numItem[], const int quantity[], int orderCount, double paid1, double change, int PayFunc, double totalpay, double sum, double serviceCharge, double Tax, int totalItem, const char category[]) {
    // Define payment methods and item names
    string payMet[4]{ " ", "Cash", "Credit Card/Debit Card", "Touch And Go/E-Wallet" };
    string itemName[10]{ "Milk (1 liter)", "Eggs (1 dozen)", "Butter (250 gram)", "Chicken Breasts (1 kilogram)", "Rice (10 kilograms)",
        "Olive oil (500 milliliters)", "Tomatoes (1 kilogram)", "Spinach (1 bunch)", "Apples (1 kilogram)", "Bread (1 loaf)" };
    double itemPrize[10]{ 15.75, 11.25, 13.50, 22.50, 45.00, 13.50, 13.50, 9.00, 18.00, 11.25 };

    // Check if PayFunc is within the valid range
    if (PayFunc < 1 || PayFunc > 3) {
        cout << "Error: Invalid payment method." << endl;
        return;
    }

    // Initialize an array to track printed items and their aggregated quantities
    bool itemPrinted[10] = { false };
    int aggregatedQuantity[10] = { 0 };

    // Aggregate quantities for each item
    for (int n = 0; n < orderCount; ++n) {
        if (!itemPrinted[numItem[n]]) {
            for (int m = 0; m < orderCount; ++m) {
                if (numItem[m] == numItem[n]) {
                    aggregatedQuantity[numItem[n]] += quantity[m];
                }
            }
            itemPrinted[numItem[n]] = true;
        }
    }

    // Print receipt
    cout << right << "." << setw(80) << setfill('_') << "." << endl;
    cout << setfill(' ') << "|" << setw(45) << "8-Eleven Store" << setw(35) << "|" << endl;
    cout << "|" << setw(47) << "xxxxxxxxxxxxxxxxxx" << setw(33) << "|" << endl;
    cout << "|" << setw(46) << "Tel: 03-12345678" << setw(34) << "|" << endl;
    cout << "|" << setw(80) << "|" << endl;
    cout << "|" << setw(45) << "Order Receipt" << setw(35) << "|" << endl;
    cout << "|" << setw(80) << "|" << endl;

    // Print aggregated items
    for (int n = 0; n < 10; ++n) {
        if (itemPrinted[n]) {
            cout << "|" << setw(2) << (n + 1) << ". " << left << setw(30) << itemName[n]
                << "( " << right << setw(3) << aggregatedQuantity[n] << " x " << setw(5) << itemPrize[n] << ")"
                << setw(22) << "RM" << setw(8) << fixed << setprecision(2) << aggregatedQuantity[n] * itemPrize[n] << " |" << endl;
        }
    }

    cout << "|" << setw(79) << "----------" << "|" << endl;
    cout << "|" << "Subtotal" << setw(62) << "RM" << setw(8) << fixed << setprecision(2) << sum << " |" << endl;
    cout << "|" << "Service Charges (5%)" << setw(50) << "RM" << setw(8) << fixed << setprecision(2) << serviceCharge << " |" << endl;
    cout << "|" << "Tax" << setw(67) << "RM" << setw(8) << fixed << setprecision(2) << Tax << " |" << endl;
    cout << "|" << setw(79) << "----------" << "|" << endl;
    cout << "|" << "Total items: " << left << setw(65) << totalItem << " |" << endl;
    cout << "|" << "Total payment: " << right << setw(55) << "RM" << setw(8) << fixed << setprecision(2) << totalpay << " |" << endl;

    if (PayFunc == 1) {
        cout << "|" << "Paid: RM " << left << setw(69) << fixed << setprecision(2) << paid1 << " |" << endl;
        cout << "|" << "Change: RM " << left << setw(67) << fixed << setprecision(2) << change << " |" << endl;
    }
    cout << "|" << setw(79) << "----------" << "|" << endl;
    cout << "|" << "Payment Method: " << left << setw(62) << payMet[PayFunc] << " |" << endl;
    cout << "|" << setw(79) << " " << "|" << endl;
    cout << "|" << setfill('_') << setw(79) << "_" << setfill(' ') << "|" << endl;
}
