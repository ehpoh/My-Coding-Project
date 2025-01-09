#include"function.h"
#include"main_function.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <unordered_map>
using namespace std;

void displaySalesByCategoryReport() {
    // Input validation
    string input;
    cout << "Please enter year and month (yyyy-mm): ";
    cin >> input;

    while (validateYearMonthInput(input) == false) {
        cout << "Invalid input! Please enter in format yyyy-mm: ";
        cin >> input;
    }

    string year = input.substr(0, 4);
    string month = input.substr(5, 2);

    ifstream file("TxTData_Files/Invoice_Line.txt");

    if (file.is_open() == false) {
        cout << "Error: File TxTData_Files/Invoice_Line.txt not found!" << endl;

    }

    // Skip the first line (header)
    string line;
    getline(file, line);


    unordered_map<string, int> categoryUnitSold;
    unordered_map<string, double> categoryTotalSales;

    double totalSales = 0;
    int totalUnitSold = 0;

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

        // Check if the year and month match the input
        if (fileLineYear == year && fileLineMonth == month) {
            double totalSalesByItem = stod(lineAmountStr);
            int unitSold = stoi(quantityStr);
            totalSales = totalSales + totalSalesByItem;
            totalUnitSold = totalUnitSold + unitSold;

            if (categoryUnitSold.count(category) > 0)
            {
                categoryUnitSold[category] = categoryUnitSold[category] + unitSold;
                categoryTotalSales[category] = categoryTotalSales[category] + totalSalesByItem;
            }
            else
            {
                categoryUnitSold.insert({ category, unitSold });
                categoryTotalSales.insert({ category, totalSalesByItem });
            }
        }
    }

    // Close the file
    file.close();

    // Display the report
    string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    const int tableWidth = 115;
    cout << endl << "Sales By Category Summary Report (" << months[stoi(month) - 1] << " " << year << ")" << endl;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;

    // Print table headers
    cout << left;  // Align text to the left
    cout << setw(80) << "[Category]";
    cout << right;
    cout << setw(15) << "[Unit Sold]"
        << setw(20) << "[Total Sales(RM)]" << endl;

    // Print a separator
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    for (auto items : categoryUnitSold) {
        // Print matched lines from the file
        cout << left;  // Align text to the left
        cout << setw(80) << items.first;
        cout << right;  // Align text to the right
        cout << setw(15) << items.second
            << setw(20) << fixed << setprecision(2) << categoryTotalSales[items.first] << endl;
    }
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    cout << left;  // Align text to the left
    cout << setw(80) << "Total";
    cout << right;
    cout << setw(15) << totalUnitSold
        << setw(20) << fixed << setprecision(2) << totalSales << endl;

    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    // clear the unordered_map
    categoryUnitSold.clear();
    categoryTotalSales.clear();

}

