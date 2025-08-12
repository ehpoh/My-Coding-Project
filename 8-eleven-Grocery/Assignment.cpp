#include <iostream>
#include "function.h"
#include <string>
#include <iomanip>
#include "Report.h"
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

int main() {
    
    // Login or sign in
    Tprintlogo();
    userroleselection();

    // Declare variables
    string Tempoption = " ";
    int option = 0;
    string cont = "y";
    int customerCount = 1;
    string Tempuser = " ";
    char user = ' ';
    string date = " ";

    
    // Selection for staff
    while (cont == "y" || cont == "Y") {
        Tprintlogo();
        displayoption();

        while (true) {
            cout << "Enter your option >> ";
            getline(cin, Tempoption);

            // Validate the Input
            if (Tempoption == "1")
            {
                option = 1;
            }
            else if (Tempoption == "2")
            {
                option = 2;
            }
            else if (Tempoption == "3")
            {
                option = 3;
            }
            else 
            {
                option = -1;
            }

            if (option < 1 || option > 3) 
            {
                cout << RED << "Invalid option. Please enter a number between 1 and 3." << RESET << endl;
            }
            else 
            {
                break;
            }
        }

        // Call staff order menu
        if (option == 1) 
        {                                 
            cout << endl;

            while (true) {
                cout << "Enter Date (DD-MM-YYYY) >> ";
                getline(cin, date);

                // Validate the date
                if (isValidDate(date)) 
                {
                    break;
                }
                else 
                {
                    cout << RED << "Invalid date. Please enter a valid date in the format DD-MM-YYYY." << RESET << endl;
                }
            }

            // Display customer count and date
            cout << endl;
            cout << "Customer " << customerCount << setw(98) << " ";
            cout << date << endl << endl;

            stafforderfunction(date);
            customerCount++;
        }
        
        // Call report function
        else if (option == 2) 
        {                                 
            cout << endl;
            reportingfunction();
        }
        
        // Exit function
        else if (option == 3) 
        {                         
            cout << endl;
            Exitfunction();
        }

        // Want to continue or don't want
        cout << endl << endl;
        cout << "Continue Next Customer? (Y/N) >> ";                
        getline(cin,cont);

        // Validate Check
        while (cont != "Y" && cont != "y" && cont != "N" && cont != "n") {
            cout << RED << "Invalid input. Please enter 'Y' or 'N'." << RESET << endl;
            cout << "Continue Next Customer? (Y/N) >> ";
            cin >> cont;
            cin.ignore();
        }

        cout << endl << endl;
    }

    // Output if no
    cout << "Have a nice day...\n\n";                       
    // Back to login page for here
    return 0;
}