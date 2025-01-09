#include "main_function.h"
#include <iostream>
using namespace std;

int main() {
	int choice = 0;
	char option = 'Y';
	string input;
	// Loop until the user provides a valid input (1, 2, or 3)
	do {
		choice = 0;
		while (choice == 0) {
			cout << "=================================" << endl;
			cout << "|             Menu              |" << endl;
			cout << "=================================" << endl;
			cout << "| 1. Daily Sales Report         |" << endl;
			cout << "| 2. Yearly Sales Report        |" << endl;
			cout << "| 3. Sales By Category Report   |" << endl;
			cout << "| 4. Exit to Main Menu          |" << endl;
			cout << "=================================" << endl;
			cout << endl;
			cout << "Please enter your choice (1, 2, 3 or 4): ";
			cin >> input;
			cout << endl;

			if (input == "1" || input == "2" || input == "3" || input == "4"){
				choice = stoi(input);
				if (choice == 1) {
					displayDailySalesReport();
					cout << endl;
				}
				else if (choice == 2) {
					displayYearlySalesReport();
					cout << endl;
				}
				else if (choice == 3) {
					displaySalesByCategoryReport();
					cout << endl;
				}
				else if (choice == 4) {
					option = 'N'; // Set option to 'N' to break out of the loop
				}

				if (choice != 4) {
					cout << endl;
					cout << "Key in 'Y' to return back to Report Menu or other key to back to Main Menu: ";
					cin >> option;
				}
				
			}
			else {
				cout << "Invalid input! Please try again." << endl;
				cout << endl;
			}

		}
	} while (option == 'Y' || option == 'y');
	
	
	

	return 0;

}

