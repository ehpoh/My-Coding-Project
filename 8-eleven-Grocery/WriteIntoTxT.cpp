#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "function.h"

using namespace std;

// Function to append a new line to the txt file
void writeInvoiceToHeader(const string& invoiceNumber, const string& amount, const string& datetime, const string& paymentType, const string& paymentNumber) {
    // Open the file in append mode (ios::app)
    ofstream file("TxtData_Files/invoice_header.txt", ios::app);

    // Check if the file was opened successfully
    if (file.is_open() == false) {
        cout << "Error: Could not open the file!" << endl;
        return;
    }

    // Write the new line to the file
    file << invoiceNumber << "," << amount << "," << datetime << "," << paymentType << "," << paymentNumber << endl;

	
    // Close the file
    file.close();

    //cout << "Invoice added successfully!" << endl;
}

void writeInvoiceToLine(const string& invoiceNumber, const string itemCodes[], const string descriptions[], const string prices[], const string qtys[], const string categories[],
    const string lineAmounts[], const string dateTimes[], int numEntries) {
    // Open the file in append mode (ios::app)
    ofstream file("TxtData_Files/invoice_line.txt", ios::app);

    // Check if the file was opened successfully
    if (file.is_open() == false) {
        cout << "Error: Could not open the file!" << endl;
        return;
    }

    // Write each entry to the file
    for (int i = 0; i < numEntries; i++) {
        file << invoiceNumber << "," << itemCodes[i] << "," << descriptions[i] << ","
            << prices[i] << "," << qtys[i] << "," << categories[i] << "," << lineAmounts[i] <<  "," << dateTimes[i] << endl;
    }

    // Close the file
    file.close();

    //cout << "Invoice lines added successfully!" << endl;
}
