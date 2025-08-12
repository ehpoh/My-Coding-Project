#include <iostream>
#include<iomanip>
#include "function.h"
#include<string>
#include<cctype>
#include<cstring>
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

// user role selection
void userroleselection() {

	string opt1 = " ";
	cout << "8-Eleven Ordering System" << endl;
	cout << endl << endl;
	cout << "user role selection screen";
	cout << endl << endl;
	cout << "Please select your role";
	cout << endl << endl;
	cout << setfill(' ') << setw(10) << " " << "1:Customer" << endl;
	cout << endl;
	cout << setfill(' ') << setw(10) << " " << "2:Staff" << endl;
	cout << endl;
	cout << "Please enter 1 if you are a Customer or 2 if you are a staff:";

	getline(cin, opt1);
	if (opt1 == "1") {
		option(opt1);		//customer can choose wtether want register or login in
	}
	else if (opt1 == "2") {
		login(opt1);		//staff only can login
	}
	else {
		cout << endl;
		cout << RED << "Invalid.Please Re-enter again" << RESET << endl << endl << endl;
		userroleselection();		//repeat the action if wrong
	}


}