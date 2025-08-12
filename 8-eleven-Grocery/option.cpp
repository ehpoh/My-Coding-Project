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

void option(string opt1)
{
	string opt2 = " ";

	cout << endl;
	cout << setfill(' ') << setw(10) << " " << "1:Login" << endl;
	cout << endl;
	cout << setfill(' ') << setw(10) << " " << "2:Register" << endl;
	cout << endl;
	cout << "Please enter 1 to login or 2 to register:";
	getline(cin, opt2);
	if (opt2 == "1") {

		login(opt1);
	}
	else if (opt2 == "2") {

		Register(opt1);
		cout << endl;
	}
	else
	{
		cout << endl;
		cout << RED << "Invalid.Please Re-enter again" << RESET << endl;
		option(opt1);
	}

}