#include"Report.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void displayMonthlySalesReport() {
    // Input validation
    string input;
    cout << "Please enter a date (yyyy-mm): ";
    cin >> input;

    while (validateYearMonthInput(input) == false) {
        cout << RED << "Invalid input! Please enter in format yyyy-mm: " << RESET;
        cin >> input;
    }

    string year = input.substr(0, 4);
    string month = input.substr(5, 2);

    int totalUnitSold = 0;
    double totalSales = 0;
    int totalTransactions = 0;

    int daysUnitSold[31] = { 0 };
    double daysSales[31] = { 0.0 };
    int daysTransaction[31] = { 0 };

    const string fileName = "TxTData_Files/Invoice_Line.txt";
    ifstream file(fileName);

    if (file.is_open() == false) {
        cout << RED << "Error: File TxTData_Files/Invoice_Line.txt not found!" << RESET << endl;

    }
    // Skip the first line (header)
    string line = "";
    getline(file, line);

    // Process each row of the file
    while (getline(file, line)) {

        int pos = 0, prevPos = 0;
        string invoiceNumber, itemCode, itemDesc, unitPriceStr, quantityStr, category, lineAmountStr, dateTime;
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
        lineAmountStr = line.substr(prevPos, pos - prevPos);
        prevPos = pos + 1;

        // Get date time
        dateTime = line.substr(prevPos);

        string fileLineYear = dateTime.substr(0, 4);  // Get first 4 characters: "2024"
        string fileLineMonth = dateTime.substr(5, 2); // Get 2 characters starting at index 5: "09"
        string fileLineDay = dateTime.substr(8, 2);

        // Check if the year and month match the input
        if (fileLineYear == year && fileLineMonth == month)
        {

            int lineUnitSold = stoi(quantityStr);
            double lineSales = stod(lineAmountStr);
            int lineDay = stoi(fileLineDay);
            daysUnitSold[lineDay - 1] = daysUnitSold[lineDay - 1] + lineUnitSold;
            daysSales[lineDay - 1] = daysSales[lineDay - 1] + lineSales;
            daysTransaction[lineDay - 1] = daysTransaction[lineDay - 1] + 1;
            totalUnitSold = totalUnitSold + lineUnitSold;
            totalSales = totalSales + lineSales;
            totalTransactions = totalTransactions + 1;
        }

    }

    // Close the file
    file.close();

    // Days in each month
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int yearInt = stoi(year);
    int monthInt = stoi(month);

    // Display the report
    const string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    const int tableWidth = 63;
    cout << endl;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;
    cout << "Monthly Sales Report (" << months[monthInt - 1] << " " << year << ")" << endl;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;

    // Print summary header
    cout << left;  // Align text to the left
    cout << setw(8) << "[Date]";
    cout << right;
    cout << setw(23) << "[No. of Transactions]" << setw(13) << "[Unit Sold]" << setw(19) << "[Total Sales(RM)]" << endl;
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    // leap year check (year is divisible by 4 AND not divisible by 100) OR (year is divisible by 400)
    if (month == "02" && ((yearInt % 4 == 0 && yearInt % 100 != 0) || yearInt % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    int numberOfDaysForEnteredMonth = daysInMonth[monthInt - 1];

    // Print table content
    for (int i = 0; i < numberOfDaysForEnteredMonth; i++)
    {
        cout << setw(2) << setfill('0') << i + 1 << "" << setfill(' ');
        cout << right;
        cout << setw(29) << daysTransaction[i] << setw(13) << daysUnitSold[i] << setw(19) << fixed << setprecision(2) << daysSales[i] << endl;
    }

    // Print total footer
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
    cout << left;  // Align text to the left
    cout << setw(8) << "Total";
    cout << right;
    cout << setw(23) << totalTransactions << setw(13) << totalUnitSold << setw(19) << fixed << setprecision(2) << totalSales << endl;

    double avarageDailySales = totalSales / daysInMonth[monthInt - 1];

    // Print summary footer	
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
    cout << left;
    cout << setw(tableWidth) << "Summary:" << endl;
    cout << left;
    cout << "Average Daily Sales: RM " << avarageDailySales << endl;
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
}

