#include "Report.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void displayYearlySalesReport() {

    // Input validation
    string input;
    cout << "Please enter year (yyyy): ";
    cin >> input;

    while (validateYearInput(input) == false) {
        cout << RED << "Invalid input! Please enter in format yyyy: " << RESET;
        cin >> input;
    }

    string year = input.substr(0, 4);

    ifstream file("TxTData_Files/Invoice_Header.txt");

    if (file.is_open() == false) {
        cout << RED << "Error: File TxTData_Files/Invoice_Header.txt not found!" << RESET << endl;

    }

    // Skip the first line (header)
    string line;
    getline(file, line);

    // Sales array to store monthly sales (index 0 for Jan, index 11 for Dec)
    double monthSale[12] = { 0.0 };
    double totalSales = 0;

    // Process each row of the file
    while (getline(file, line)) {

        int pos = 0;
        int prevPos = 0;
        string invoiceNumber, amountStr, datetime, paymentType, paymentNumber;

        // Get invoice number
        pos = line.find(',', prevPos);
        invoiceNumber = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get amount
        pos = line.find(',', prevPos);
        amountStr = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get datetime
        pos = line.find(',', prevPos);
        datetime = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get payment type
        pos = line.find(',', prevPos);
        paymentType = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get payment number
        paymentNumber = line.substr(prevPos);

        string fileYear = datetime.substr(0, 4);  // Get first 4 characters: "2024"
        string fileMonth = datetime.substr(5, 2); // Get 2 characters starting at index 5: "09"

        // Check if the year matches the input
        if (fileYear == year) {
            double amount = stod(amountStr); // Convert amount to double
            int month = stoi(fileMonth);     // Convert month to integer

            monthSale[month - 1] = monthSale[month - 1] + amount;  // Store the sales in the corresponding month
            totalSales = totalSales + amount;
        }
    }

    // Close the file
    file.close();

    // Display the report
    const string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                              "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    const int tableWidth = 30;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;
    cout << endl << "Yearly Sales Report (Year: " << year << ")" << endl;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;

    // Print table headers
    cout << left;  // Align text to the left
    cout << setw(10) << "[Month]";
    cout << right;
    cout << setw(20) << "[Total Sales(RM)]" << endl;

    // Print a separator
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    // Output the sales report
    for (int i = 0; i < 12; i++) {
        cout << left;  // Align text to the left
        cout << setw(10) << months[i];
        cout << right;  // Align text to the right
        cout << setw(20) << fixed << setprecision(2) << monthSale[i] << endl;
    }

    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    cout << left;  // Align text to the left    
    cout << setw(10) << "Total";
    cout << right;
    cout << setw(20) << fixed << setprecision(2) << totalSales << endl;

    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

}