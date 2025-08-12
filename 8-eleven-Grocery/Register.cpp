#include <iostream>
#include<iomanip>
#include "function.h"
#include<string>
#include<fstream>		// add file stream header file
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void Register(string opt1)
{



	string opt3 = " ";
	string opt4 = " ";


	string username = "";
	string password = "";
	string Repeat_password = "";
	string Phone = "";


	cout << endl;
	cout << "Register" << endl;
	ofstream outFile;		// declare file stream variable
	outFile.open("customer.txt", ios::app);  // open the file in append mode
	if (!outFile) {
		cout << RED << "Error opening file" << RESET << endl;

	}



	cout << endl;
	cout << setw(10) << " " << "Username: ";
	getline(cin, username);
	username = usernameverify(username);		//vertfy username in usernameverify by passing username



	cout << setw(10) << " " << "Password(Use eight characters or more, a combination of letters, numbers, and symbols.Example: ABCD1234! , please do not empty):";
	getline(cin, password);
	password = passwordverify(password);	//vertfy password in usernameverify by passing password



	cout << setw(10) << " " << "Repeat Password:";
	getline(cin, Repeat_password);



	if (Repeat_password == password) {

		cout << setw(10) << " " << "Phone number:";
		getline(cin, Phone);
		Phone = verifyphone(Phone);				//vertfy Phone in usernameverify by passing Phone

		outFile << username << "," << password << "," << Phone << endl;  //update the information into user.txt file



		do {
			cout << endl;
			cout << setw(10) << setfill(' ') << " " << "(Register successfullly)" << endl;
			cout << endl;
			cout << setw(10) << setfill(' ') << " " << "1.login" << endl << endl;
			cout << setw(10) << setfill(' ') << " " << "2.user role selection screen" << endl << endl;
			cout << "Please Enter 1 if you want to login,2 if back to the user role selection screen:";
			getline(cin, opt3);
			cout << endl;
			if (opt3 == "1")
			{

				login(opt1);

			}
			else if (opt3 == "2") {

				userroleselection();


			}
			else
			{
				cout << endl;
				cout << RED << "Invalid.Please Re-enter again" << RESET << endl;
				Register(opt1);
			}

		} while (opt3 != "1" && opt3 != "2");
	}
	else {
		do {
			cout << endl;
			cout << RED << "Password and Repeat password are not same" << RESET << endl << endl;
			cout << setw(10) << setfill(' ') << " " << "1.user role selection screen" << endl << endl;
			cout << setw(10) << setfill(' ') << " " << "2.register" << endl << endl;
			cout << "Please Enter 1 if you want to back to user role selection screen,2 if continue register :";
			getline(cin, opt4);

			cout << endl;
			if (opt4 == "1")
			{

				userroleselection();

			}
			else if (opt4 == "2") {

				Register(opt1);


			}
			else
			{
				cout << endl;
				cout << RED << "Invalid.Please Re-enter again" << RESET << endl;
			}

		} while (opt4 != "1" && opt4 != "2");
	}





	outFile.close();

}
