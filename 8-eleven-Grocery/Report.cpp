#include <iostream>
#include <iomanip>
#include <string>
#include "Report.h"
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void reportingfunction() {
	int choice = 0;
	char option = 'Y';
	string input;
	// Loop until the user provides a valid input (1, 2, or 3)
	do {
		choice = 0;
		while (choice == 0) {
			cout << "===================================" << endl;
			cout << "|              Menu               |" << endl;
			cout << "===================================" << endl;
			cout << "| 1. Daily Sales Report           |" << endl;
			cout << "| 2. Monthly Sales Report         |" << endl;
			cout << "| 3. Yearly Sales Report          |" << endl;
			cout << "| 4. Yearly Sales Summary Report  |" << endl;
			cout << "| 5. Exit to Main Menu            |" << endl;
			cout << "===================================" << endl;
			cout << endl;
			cout << "Please enter your choice (1, 2, 3, 4 or 5): ";
			cin >> input;
			cout << endl;

			if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5") {
				choice = stoi(input);
				if (choice == 1) {
					displayDailySalesReport();
					cout << endl;
					cout << "Key in 'Y' to return back to Report Menu or other key to back to Main Menu: ";
					cin >> option;
					cout << endl;
				}
				else if (choice == 2) {
					displayMonthlySalesReport();
					cout << endl;
					cout << "Key in 'Y' to return back to Report Menu or other key to back to Main Menu: ";
					cin >> option;
					cout << endl;
				}
				else if (choice == 3) {
					displayYearlySalesReport();
					cout << endl;
					cout << "Key in 'Y' to return back to Report Menu or other key to back to Main Menu: ";
					cin >> option;
					cout << endl;
				}
				else if (choice == 4) {
					displayYearlySalesSummaryReport();
					cout << endl;
					cout << "Key in 'Y' to return back to Report Menu or other key to back to Main Menu: ";
					cin >> option;
					cout << endl;
				}
				else {
					option = 'N'; // Set option to 'N' to break out of the loop
				}

			}
			else {
				cout << RED << "Invalid input! Please try again." << RESET << endl;
				cout << endl;
			}

		}
	} while (option == 'Y' || option == 'y');
	cin.ignore();
}
