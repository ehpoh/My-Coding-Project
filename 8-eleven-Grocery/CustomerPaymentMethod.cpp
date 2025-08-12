#include "function.h"
#include <iostream>
#include <string>

using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void CustomerPaymentmethod(string &paymentType) {
    string TempChoice = " ";
    int Choice = 0;
	
    // Header
    cout << "Select a Payment Method:" << endl;
    cout << "[1] E-Wallet" << endl;
    cout << "[2] Credit Card" << endl;
    cout << "[3] Debit Card" << endl << endl;

    // Validate Payment Method
    while (true) {
        
        // Input Choice
        cout << "Enter a Payment Method >> ";
        getline(cin, TempChoice);

        // Check valid choice
        if (TempChoice == "1") 
        {
	    paymentType = "eWallet";
            Choice = 1;
            break;
        }
        else if (TempChoice == "2") 
        {
            paymentType = "Credit Card";
            Choice = 2;
            break;
        }
        else if (TempChoice == "3") 
        {
	    paymentType = "Debit Card";
            Choice = 3;
            break;
        }
        else
        {
            cout << RED << "Invalid Input. Please re-enter again..." << RESET << endl;
        }
    }

	// Print thank you message
    cout << "Thank you for your order! Your payment has been processed.\n\n";

}
