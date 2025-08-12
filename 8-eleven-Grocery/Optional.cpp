#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include "function.h"

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

using namespace std;
void optional(string remainder, string opt1) {

	string opt = " ";
	while (remainder == "Please re-enter again") {
		// Handle user options
		if (opt1 == "1")
		{
			cout << "1. Continue login" << endl;
			cout << "2. Register new account" << endl;
			cout << "3. Forgot password" << endl;
			cout << "4. Forgot username" << endl;
			cout << "Please enter an option (1 to continue login, 2 to register, 3 for forgot password,4 for forgot username ): ";
			getline(cin, opt);
			cout << endl;
			if (opt == "1") {
				login(opt1); // Retry login
			}
			else if (opt == "2") {
				Register(opt1); // Register new account

			}
			else if (opt == "3") {
				forgotpassword(opt1); // Handle retrieve password and reset password

			}
			else if (opt == "4") {
				forgotusername(opt1); // Handle retrieve username
			}
			else {
				cout << endl;
				cout << RED << "Invalid option. Please try again." << RESET << endl << endl;;
				optional(remainder, opt1);
			}

		}
		else {

			cout << "1. Continue login" << endl;
			cout << "2. Forgot password" << endl;
			cout << "3. Forgot username" << endl;
			cout << "Please enter an option (1 to continue login,2 for forgot password,3 for forgot username ): ";
			getline(cin, opt);
			cout << endl;
			if (opt == "1") {
				login(opt1); // Retry login
			}
			else if (opt == "2") {
				forgotpassword(opt1); // Handle retrieve password and reset password

			}
			else if (opt == "3") {
				forgotusername(opt1); // Handle retrieve username
			}
			else {
				cout << endl;
				cout << RED << "Invalid option. Please try again." << RESET << endl << endl;;
				optional(remainder, opt1);
			}
		}
		break;
	}
}