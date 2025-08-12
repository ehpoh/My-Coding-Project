#include <iostream>
#include<iomanip>
#include "function.h"
#include<string>
#include<cctype>
#include <cstring> 
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

string passwordverify(string password)
{
	//declare variable
	int i = 0;
	char c = ' ';
	int p = 0;		//number of punctuation character
	int u = 0;		//number of uppercase character
	int l = 0;		//number of lowercase character
	int d = 0;		//number of digit character
	string respond = " ";

	do {
		//for loop to check each character
		for (i = 0; i < password.length(); ++i) {
			c = password.at(i);		// character in password
			if (ispunct(c)) {		//is punctuation character?
				p++;

			}
			else if (isupper(c)) {		//is uppercase character?
				u++;

			}
			else if (islower(c)) {		//is lowercase character?
				l++;

			}
			else if (isdigit(c)) {		//is digit character?
				d++;

			}

		}


		if (p > 0 && u > 0 && l > 0 && d > 0 && password.length() >= 8) {   //ensure password have eight characters or more, a combination of letters, numbers, and symbols)

			break;

		}
		else {

			cout << setw(135) << " " << RED << "(Invalid password)" << RESET << endl << endl;
			respond = "Please Re-enter again";
			cout << RED << respond << RESET << endl << endl;
			cout << setw(10) << " " << "Password(Use eight characters or more, a combination of letters, numbers, and symbols.Example: ABCD1234! , please do not empty):";
			getline(cin, password);

		}

	} while (respond == "Please Re-enter again"); //repeat loop while respond == "Please Re-enter again"

	return password;
}

