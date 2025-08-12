#include "Report.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void displayYearlySalesSummaryReport() {

    // Input validation
    string input;
    cout << "Please enter year (yyyy): ";
    cin >> input;

    while (validateYearInput(input) == false) {
        cout << RED << "Invalid input! Please enter in format yyyy: " << RESET;
        cin >> input;
    }

    string year = input.substr(0, 4);

    cout << "Please enter item code: ";
    cin >> input;

    string inputItemCode = input;
    ifstream file("TxTData_Files/Invoice_Line.txt");

    if (file.is_open() == false) {
        cout << RED << "Error: File TxTData_Files/Invoice_Line.txt not found!" << RESET << endl;

    }

    // Skip the first line (header)
    string line;
    getline(file, line);

    // Sales array to store monthly sales (index 0 for Jan, index 11 for Dec)
    double monthSale[12] = { 0.0 };
    double totalSales = 0;
    int monthUnitSold[12] = { 0 };
    int totalUnitSold = 0;
    int monthTransaction[12] = { 0 };
    int totalTransactions = 0;
    bool foundItemCode = false;
    string matchedCategory;
    string matchedItemDesc;

    // Process each row of the file
    while (getline(file, line)) {

        int pos = 0, prevPos = 0;
        string invoiceNumber, itemCode, itemDesc, unitPriceStr, quantityStr, category, amountStr, dateTime;
        // Get invoice number
        pos = line.find(',', prevPos);
        invoiceNumber = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get item code
        pos = line.find(',', prevPos);
        itemCode = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get item desc
        pos = line.find(',', prevPos);
        itemDesc = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get unit price
        pos = line.find(',', prevPos);
        unitPriceStr = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get quantity
        pos = line.find(',', prevPos);
        quantityStr = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get category
        pos = line.find(',', prevPos);
        category = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;


        // Get line amount
        pos = line.find(',', prevPos);
        amountStr = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get date time
        dateTime = line.substr(prevPos);

        string fileYear = dateTime.substr(0, 4);  // Get first 4 characters: "2024"
        string fileMonth = dateTime.substr(5, 2); // Get 2 characters starting at index 5: "09"

        // Check if the year matches the input
        if (fileYear == year && inputItemCode == itemCode) {
            double amount = stod(amountStr); // Convert amount to double
            int lineUnitSold = stoi(quantityStr);
            int month = stoi(fileMonth);     // Convert month to integer
            monthUnitSold[month - 1] = monthUnitSold[month - 1] + lineUnitSold;
            monthSale[month - 1] = monthSale[month - 1] + amount;  // Store the sales in the corresponding month
            totalUnitSold = totalUnitSold + lineUnitSold;
            totalSales = totalSales + amount;
            monthTransaction[month - 1] = monthTransaction[month - 1] + 1;
            totalTransactions = totalTransactions + 1;
            matchedCategory = category;
            matchedItemDesc = itemDesc;
            foundItemCode = true;
        }
    }

    // Close the file
    file.close();

    // Display the report
    const string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

    const int tableWidth = 65;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;
    cout << "Yearly Sales Summary Report for Item [" << inputItemCode << "] (Year: " << year << ")" << endl;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;

    if (foundItemCode == true)
    {
        // Print table headers
        cout << "Category: [" << matchedCategory << "]" << endl;
        cout << "Desc: [" << matchedItemDesc << "]" << endl;
        cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;

        cout << left;  // Align text to the left
        cout << setw(10) << "[Month]";
        cout << right;
        cout << setw(23) << "[No. of Transactions]" << setw(13) << "[Unit Sold]" << setw(19) << "[Total Sales(RM)]" << endl;
        // Print a separator
        cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

        // Output the report content
        for (int i = 0; i < 12; i++) {
            cout << left;  // Align text to the left
            cout << setw(10) << months[i];
            cout << right;  // Align text to the right
            cout << setw(23) << monthTransaction[i] << setw(13) << monthUnitSold[i] << setw(19) << fixed << setprecision(2) << monthSale[i] << endl;
        }

        cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

        cout << left;  // Align text to the left
        cout << setw(10) << "Total";
        cout << right;
        cout << setw(23) << totalTransactions << setw(13) << totalUnitSold << setw(19) << fixed << setprecision(2) << totalSales << endl;

        double avarageMonthlySales = totalSales / 12;

        // Print summary footer	
        cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
        cout << left;
        cout << setw(tableWidth) << "Summary:" << endl;
        cout << left;
        cout << "Average Monthly Sales: RM " << avarageMonthlySales << endl;
        cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
    }
    else
    {
        cout << RED << "Item Code [" << inputItemCode << "] not found in year [" << year << "] transactions." << RESET << endl;
        cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
    }
}