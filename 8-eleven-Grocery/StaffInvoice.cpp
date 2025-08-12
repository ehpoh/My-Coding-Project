#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>  // For round function
#include <ctime> 
#include <limits> // For numeric_limits
#include "function.h"

using namespace std;

// Define constants
const int MAX_ITEMS = 10;
const double SERVICE_CHARGE_RATE = 0.05;
const double TAX_RATE = 0.05;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Example item data
string itemName[MAX_ITEMS]{
    "Milk (1 liter)", "Eggs (1 dozen)", "Butter (250 gram)", "Chicken Breasts (1 kilogram)", "Rice (10 kilograms)",
    "Olive oil (500 milliliters)", "Tomatoes (1 kilogram)", "Spinach (1 bunch)", "Apples (1 kilogram)", "Bread (1 loaf)"
};

double itemPrice[MAX_ITEMS]{
    15.75, 11.25, 13.50, 22.50, 45.00,
    13.50, 13.50, 9.00, 18.00, 11.25
};
string itemCode[MAX_ITEMS] { "1001","1002","1003","1004","1005","1006","1007","1008","1000","1010" };
string itemCategory[MAX_ITEMS]{
	"beverages","food","frozen food","produce","food","food","produce","produce","produce","bakery"
};

// Function to check if a string is a valid integer
bool isValidInteger(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

// Function to check if a string is a valid double
bool isValidDouble(const string& str) {
    bool dotEncountered = false;
    if (str.empty()) return false;
    for (char c : str) {
        if (c == '.') {
            if (dotEncountered) return false; // More than one dot is invalid
            dotEncountered = true;
        }
        else if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

// Function to get a valid integer input from the user
int getValidIntegerInput() {
    string input;
    int value;
    while (true) {
        cout << endl;
        cout << "Choose the payment method:" << endl;
        cout << "1. Cash" << endl;
        cout << "2. Credit Card/Debit Card" << endl;
        cout << "3. Touch And Go/E-Wallet" << endl;
        cout << "Choose the number: ";
        getline(cin, input);
        if (isValidInteger(input)) {
            value = stoi(input);
            return value;
        }
        else {
            cout << RED << "Invalid input. Please enter a valid integer." << RESET << endl;
        }
    }
}

// Function to get a valid double input from the user
double getValidDoubleInput() {
    string input;
    double value;
    while (true) {
        cout << "Paid: RM ";
        getline(cin, input);
        if (isValidDouble(input)) {
            // Convert to double manually
            size_t i = 0;
            value = 0.0;
            bool isNegative = false;
            if (input[0] == '-') {
                isNegative = true;
                ++i;
            }
            while (i < input.length() && input[i] != '.') {
                value = value * 10 + (input[i] - '0');
                ++i;
            }
            if (i < input.length() && input[i] == '.') {
                ++i;
                double decimalPlace = 0.1;
                while (i < input.length()) {
                    value += (input[i] - '0') * decimalPlace;
                    decimalPlace *= 0.1;
                    ++i;
                }
            }
            if (isNegative) value = -value;
            return value;
        }
        else {
            cout << RED << "Invalid input. Please enter a valid number." << RESET << endl;
        }
    }
}

// Function to print the invoice
void invoice(const int numItem[], const int quantity[], int orderCount, const char category[], const string& date) {

    double sum = 0;
    int totalItems = 0;
    bool itemPrinted[MAX_ITEMS] = { false };  // To keep track of items that have already been printed

	time_t timestamp = time(NULL);
    struct tm* timeinfo;
    char invNoTimeStampStr[15];  
	char dateTimeStampStr[20]; 
	char displayDateStr[11]; 
    timeinfo = localtime(&timestamp);
    // Format the invNoTimeStampStr into yyyymmddHHmmss format
    strftime(invNoTimeStampStr, sizeof(invNoTimeStampStr), "%Y%m%d%H%M%S", timeinfo);
    // Format the dateTimeStampStr into yyyy-mm-dd HH:mm:ss format
    strftime(dateTimeStampStr, sizeof(dateTimeStampStr), "%Y-%m-%d %H:%M:%S", timeinfo);
    // Format the displayDateStr into dd/mm/yyyy format
    strftime(displayDateStr, sizeof(displayDateStr), "%d/%m/%Y", timeinfo);
	string invoiceNo = invNoTimeStampStr;
	string dateTime = dateTimeStampStr;
	string displayDate = displayDateStr;
	string* itemDescs = new string[orderCount];
	string* itemPrices = new string[orderCount];
	string* itemQuantities = new string[orderCount];
	string* itemAmounts = new string[orderCount];
	string* itemCodes = new string[orderCount];
	string* itemCategories = new string[orderCount];
	string* itemDateTimes = new string[orderCount];
	ostringstream oss;
	double lineAmount;
	int newLineCount = 0;
	
	cout << right << "." << setfill('_') << setw(80) << "." << setfill(' ') << endl;
	cout << "|" << setw(40) << "INVOICE" << setw(40) << "|" << endl;
	cout << "|" << setw(45) << "8-Eleven Store" << setw(35) << "|" << endl;
	cout << "|" << setw(44) << "Tel: 03-12345678" << setw(36) << "|" << endl;
	cout << "|" << setw(80) << "|" << endl;

	cout << "|" << "Invoice No: " << invoiceNo;
	cout << right << setw(52) << displayDate << " |" << endl;
	
    // Print order items and calculate sum
    for (int n = 0; n < orderCount; ++n) {
        if (numItem[n] < 0 || numItem[n] >= MAX_ITEMS) {
            cout << RED << "Error: Invalid item number " << numItem[n] << RESET << endl;
            return;
        }
        if (!itemPrinted[numItem[n]]) {
            // Calculate the total quantity of this item
            int totalQuantity = 0;
            for (int m = 0; m < orderCount; ++m) {
                if (numItem[m] == numItem[n]) {
                    totalQuantity += quantity[m];
                }
            }
        	lineAmount = totalQuantity * itemPrice[numItem[n]];
			oss.str("");  // Set the buffer to an empty string
			oss.clear();  // Clear any error flags
			// Set fixed format and precision to 2 decimal places
			oss << fixed << setprecision(2) << lineAmount;
			// Convert the stream to a string
			itemAmounts[newLineCount] = oss.str();
		
           		
            // Print item
			cout << "|" << setw(2) << (newLineCount + 1) << ". " << left << setw(30) << itemName[numItem[n]] 
		     << "( " << right << setw(3) << totalQuantity << " x " << setw(5) << itemPrice[numItem[n]] << " )"
			 << setw(21) << "RM" << setw(8) << itemAmounts[newLineCount] << " |" << endl;


            // Mark item as printed
            itemPrinted[numItem[n]] = true;
			
			sum += lineAmount;
			totalItems += totalQuantity;
			itemDescs[n] = itemName[numItem[n]];
			
			oss.str("");  // Set the buffer to an empty string
			oss.clear();  // Clear any error flags
			// Set fixed format and precision to 2 decimal places
			oss << fixed << setprecision(2) << itemPrice[numItem[n]];
			// Convert the stream to a string
			itemPrices[newLineCount] = oss.str();
		
			itemQuantities[newLineCount] = to_string(totalQuantity);
			itemCategories[newLineCount] = itemCategory[newLineCount];
			itemCodes[newLineCount] = itemCode[newLineCount];
			itemDateTimes[newLineCount] = dateTime;
			newLineCount = newLineCount + 1;
        }
    }

    if (orderCount > 0) {  // Check if there were any orders
        cout << "|" << setw(79) << "----------" << "|" << endl;
        double serviceCharge = sum * SERVICE_CHARGE_RATE;
        double tax = sum * TAX_RATE;
        double totalPay = sum + serviceCharge + tax;

        // Round total pay to the nearest 5 cents
        totalPay = round(totalPay * 20) / 20.0;

        cout << "|" << "Subtotal" << setw(62) << "RM" << setw(8) << fixed << setprecision(2) << sum << " |" << endl;
        cout << "|" << "Service Charges (5%)" << setw(50) << "RM" << setw(8) << fixed << setprecision(2) << serviceCharge << " |" << endl;
        cout << "|" << "Tax" << setw(67) << "RM" << setw(8) << fixed << setprecision(2) << tax << " |" << endl;
        cout << "|" << setw(79) << "----------" << "|" << endl;
        cout << "|" << "Total items: " << left << setw(65) << totalItems << " |" << endl;

        cout << "|" << "Total payable: " << right << setw(55) << "RM" << setw(8) << fixed << setprecision(2) << totalPay << " |" << endl;
        cout << "|" << setw(80) << " |" << endl;
        cout << "|" << setfill('_') << setw(79) << "_" << setfill(' ') << "|" << endl;
    }
    else {
        cout << RED << "No orders to display." << RESET << endl;
    }

    // Payment method selection
    int paymentMethod = 0;
	string paymentType;
    string confirmation;
    while (true) {
        cout << endl;
        paymentMethod = getValidIntegerInput();

        if (paymentMethod >= 1 && paymentMethod <= 3) {
            break;
        }
        cout << RED << "Invalid input. Please enter 1, 2, or 3." << RESET << endl;
    }

    // Confirm payment
    while (true) {
        cout << "Confirm payment? (Y/N): ";
        getline(cin, confirmation);
        if (confirmation == "Y" || confirmation == "y" || confirmation == "N" || confirmation == "n") {
            break;
        }
        cout << RED << "Invalid input. Please enter 'Y' or 'N'." << RESET << endl;
    }

    if (confirmation == "N" || confirmation == "n") {
        return; // Exit if payment is not confirmed
    }

    // Handle payment
    double paidAmount = 0;
    double change = 0;

    double totalPay = sum + (sum * SERVICE_CHARGE_RATE) + (sum * TAX_RATE); // Calculate total pay

    if (paymentMethod == 1) {  // Cash
        while (true) {
            paidAmount = getValidDoubleInput();

            if (paidAmount >= totalPay) {
                break;
            }
            cout << RED << "Paid amount is insufficient. Please enter a value greater than or equal to the total payable." << RESET << endl;
        }
        change = paidAmount - totalPay;
        cout << "Success" << endl;
        cout << "Total payable: RM" << setw(8) << fixed << setprecision(2) << totalPay << endl;
        cout << "Paid: RM" << setw(8) << fixed << setprecision(2) << paidAmount << endl;
        cout << "Change: RM" << setw(8) << fixed << setprecision(2) << change << endl;
        paymentType = "Cash";
    }
    else if (paymentMethod == 2 || paymentMethod == 3) {  // Credit/Debit Card or E-Wallet
        cout << "Success" << endl;
        cout << "Total payment: RM" << setw(8) << fixed << setprecision(2) << totalPay << endl;
        paymentType = "eWallet";    
     }

    if (paymentMethod == 2) paymentType = "Credit Card";

    oss.str("");  // Set the buffer to an empty string
    oss.clear();  // Clear any error flags	
    // Set fixed format and precision to 2 decimal places
    oss << fixed << setprecision(2) << totalPay;
    // Convert the stream to a string
    string totalpayStr = oss.str();
	
    writeInvoiceToHeader(invoiceNo, totalpayStr, dateTime, paymentType, "");
    writeInvoiceToLine(invoiceNo, itemCodes, itemDescs, itemPrices, itemQuantities, itemCategories, itemAmounts, itemDateTimes, newLineCount);


    // Call receipt function
    receipt(numItem, quantity, orderCount, paidAmount, change, paymentMethod, totalPay, sum, SERVICE_CHARGE_RATE * sum, TAX_RATE * sum, totalItems, category);
}

void generateinvoice(const int numItem[], const int quantity[], int orderCount, const char category[], const string& date) {
    invoice(numItem, quantity, orderCount, category, date);
}
