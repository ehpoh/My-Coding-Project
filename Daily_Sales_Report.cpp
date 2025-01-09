#include"function.h"
#include"main_function.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
using namespace std;

void displayDailySalesReport() {
    // Input validation
    string input;
    cout << "Please enter a date (yyyy-mm-dd): ";
    cin >> input;

    while (validateYearMonthDayInput(input) == false) {
        cout << "Invalid input! Please enter in format yyyy-mm-dd: ";
        cin >> input;
    }

    string year = input.substr(0, 4);
    string month = input.substr(5, 2);
    string day = input.substr(8, 2);

    ifstream file("TxTData_Files/Invoice_Line.txt");

    if (file.is_open() == false) {
        cout << "Error: File TxTData_Files/Invoice_Line.txt not found!" << endl;
 
    }

    // Skip the first line (header)
    string line;
    getline(file, line);

    map<string, string> itemCodeItemDesc;
    map<string, int> itemCodeUnitSold;
    map<string, double> itemCodeUnitPrice;
    map<string, double> itemCodeTotalSales;

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
        string fileLineDay = dateTime.substr(8, 2);
        // Check if the year and month match the input
        if (fileLineYear == year && fileLineMonth == month && fileLineDay == day) {
            double totalSalesByItem = stod(lineAmountStr);
            double unitPrice = stod(unitPriceStr);
            int unitSold = stoi(quantityStr);
            totalSales = totalSales + totalSalesByItem;
            totalUnitSold = totalUnitSold + unitSold;

            // find the item code in the itemCodeItemDesc
            if (itemCodeItemDesc.count(itemCode) > 0)
            {
                itemCodeUnitSold[itemCode] = itemCodeUnitSold[itemCode] + unitSold;
                itemCodeTotalSales[itemCode] = itemCodeTotalSales[itemCode] + totalSalesByItem;
            }
            else
            {
                itemCodeItemDesc.insert({ itemCode, itemDesc });
                itemCodeUnitSold.insert({ itemCode, unitSold });
                itemCodeUnitPrice.insert({ itemCode, unitPrice });
                itemCodeTotalSales.insert({ itemCode, totalSalesByItem });
            }
        }
    }

    // Close the file
    file.close();

    // Display the report
    string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    const int tableWidth = 139;
    cout << endl << "Daily Sales Report (" << day << " " << months[stoi(month) - 1] << " " << year << ")" << endl;
    cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;

    // Print table headers
    cout << left;  // Align text to the left
    cout << setw(12) << "[Item Code]" << setw(80) << "[Item Desc]";
    cout << right;
    cout << setw(12) << "[Unit Sold]" << setw(17) << "[Unit Price(RM)]" << setw(18) << "[Total Sales(RM)]" << endl;

    // Print a separator
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    for (auto items : itemCodeItemDesc) {
        // Print matched lines from the file
        cout << left;  // Align text to the left
        cout << setw(12) << items.first
            << setw(80) << items.second;
        cout << right;  // Align text to the right
        cout << setw(12) << itemCodeUnitSold[items.first]
            << setw(17) << fixed << setprecision(2) << itemCodeUnitPrice[items.first]
            << setw(18) << fixed << setprecision(2) << itemCodeTotalSales[items.first] << endl;
    }
    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    cout << left;  // Align text to the left
    cout << setw(92) << "Total";
    cout << right;
    cout << setw(12) << totalUnitSold
        << setw(35) << fixed << setprecision(2) << totalSales << endl;

    cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

    // clear the map
    itemCodeItemDesc.clear();
    itemCodeUnitSold.clear();
    itemCodeUnitPrice.clear();
    itemCodeTotalSales.clear();

}

