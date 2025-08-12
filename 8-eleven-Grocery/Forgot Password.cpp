#include <iostream>
#include<iomanip>
#include "function.h"
#include<string>
#include<cctype>
#include<cstring>
#include <ctime>
#include<cstdlib>
#include<fstream>
#define X -1
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void forgotpassword(string opt1) {

	int Firstcomma = 0;
	int Lastcomma = 0;
	int Nextcomma = 0;
	int Pos = 0;

	int t = -1;

	string inputusername = " ";
	string Fileusername = " ";

	string inputPhone = " ";
	string Filephonenum = " ";

	string name = " ";
	string phone = " ";

	string header = "";
	string line = " ";

	int usernamecount = 1;
	int passwordcount = 1;
	int u = 0;		//username
	int p = 0;		//phone

	char c = ' ';


	string Filepassword = " ";
	string password = " ";
	string newpassword = " ";
	string Repeat_password = " ";

	int randomnumber = 0;

	string verification_code = " ";
	int verificationcode = 0;

	string Respond = " ";
	string respond = " ";
	string responds = " ";

	string opt2 = " ";
	string opt3 = " ";

	string opt4 = " ";
	int option4 = 0;


	srand(static_cast<unsigned>(time(0)));		//seed function to be called once only



	cout << "Please Enter your username:";
	getline(cin, inputusername);

	while (inputusername.empty()) {
		cout << endl;
		cout << RED << "Invalid username." << RESET << endl;
		Respond = "Please Re-enter again";
		cout << RED << Respond << RESET << endl << endl;
		forgotpassword(opt1);

	}

	for (int i = 0; i < inputusername.length(); ++i) {
		c = inputusername.at(i);		// character in username

		if (!(isalpha(c))) {		//is uppercase character?

			cout << setw(25) << " " << RED << "(Invalid username)" << RESET << endl << endl;
			Respond = "Please Re-enter again";
			cout << RED << Respond << RESET << endl << endl;


			do {
				cout << endl;
				cout << "1.Forgot password" << endl;
				cout << "2.Forgot username" << endl << endl;
				cout << "Please Enter 1 if you want to continue or 2 if you want to forgot username:";
				getline(cin, opt2);
				cout << endl;
				if (opt2 == "1")
				{
					forgotpassword(opt1);
				}
				else if (opt2 == "2") {
					forgotusername(opt1);
				}
			} while (Respond == "Please Re-enter again");
		}


	}


	cout << "Please Enter your Phone:";
	getline(cin, inputPhone);

	while (inputPhone.empty()) {
		cout << setw(25) << " " << RED << "(Invalid Phone number)" << RESET << endl;
		responds = "Please Re-enter again";
		cout << RED << responds  << RESET << endl << endl;

		cout << "Please Enter your Phone:";
		getline(cin, inputPhone);
		cout << endl;


	}
	for (int i = 0; i < inputPhone.length(); i++) {				//verify so that fulfill format of phone number
		while (isalpha(inputPhone.at(i)) || isspace(inputPhone.at(i)) || inputPhone.length() < 9 || inputPhone.length() > 12 || inputPhone.at(0) != '0' || inputPhone.at(1) != '1' || inputPhone.at(3) != '-') {       //make sure phone number only contain number,must have this format:012-xxxxxxxx
			cout << setw(25) << " " << RED << "(Invalid Phone number)" << RESET << endl << endl;
			responds = "Please Re-enter again";
			cout << RED << responds << RESET << endl << endl;
			if (opt1 == "1")
			{
				do {
					cout << endl;
					cout << "1.Forgot password" << endl;
					cout << "2.Register" << endl << endl;
					cout << "Please Enter 1 if you want to continue or 2 if you want to register:";
					getline(cin, opt2);
					cout << endl;
					if (opt2 == "1")
					{
						forgotpassword(opt1);
					}
					else if (opt2 == "2") {
						Register(opt1);
					}
					else {
						respond = "Invalid.Please Re-enter again";
						cout << RED << respond << RESET;
					}
				} while (respond == "Invalid.Please Re-enter again");
			}
			else {
				forgotpassword(opt1);
			}
		}

	}


	ifstream file;
	if (opt1 == "1") {
		// Open the file for reading
		file.open("customer.txt", ios::in);
		if (!file.is_open()) {  // Check if the file was opened successfully
			cout << RED << "Error opening file." << RESET << endl;

		}

	}
	else {
		// Open the file for reading


		file.open("staff.txt", ios::in);
		if (!file.is_open()) {  // Check if the file was opened successfully
			cout << RED << "Error opening file." << RESET << endl;

		}
	}


	//format of line:username,password,phone

	getline(file, header);	//read the first line header


	while (getline(file, line)) {			 // Read each line from the file
		// .find(character,start position)
		Firstcomma = line.find(',');		 //find the first position of ','


		if (Firstcomma != X) {               //If no comma is found, `firstcomma

			Lastcomma = line.find(',', Firstcomma + 1);  // firstcomma +1 is start position,find ',' after first comma,assume that is last comma
			Pos = Lastcomma;		//store the last comma position

			//find the last comma until no comma found
			while (t == -1) {		//int t = -1, indicating that the loop should continue running.
				Nextcomma = line.find(',', Pos + 1);		//pos + 1 is start position,if find ',' after pos,as a next comma
				if (Nextcomma == X) {			//If no comma is found, `nextComma` will be `X` (which is -1).
					break;
				}
				Lastcomma = Nextcomma;		//assume nextcomma is last comma if have other comma found
				Pos = Nextcomma;			//nextcomma/lastcomma is store into pos,thus pos is last comma
			}

			// .substr(start position,number of character)
			Fileusername = line.substr(0, Firstcomma);  // 0 is the starting point,position (firstcomma),extract substring username between starting point and first comma
			Filepassword = line.substr(Firstcomma + 1, Lastcomma - Firstcomma - 1);  // firstcomma + 1 is the starting point,position (lastcomma - firstcomma - 1),-1 so that no include last comma,extract substring username between starting point and first comma
			Filephonenum = line.substr(Lastcomma + 1);  // Lastcomma +1 is the starting point,no character means substrate until the end of line/string


			if (Fileusername == inputusername && Filephonenum == inputPhone) {
				password = Filepassword;			//store into password if both password and username is same respectively
			}
			if (inputusername == Fileusername) {
				name = Fileusername;		//store into name so as to compared after
				u = usernamecount;				//store which line is the Fileusername=inputusername

			}
			if (inputPhone == Filephonenum) {
				phone = Filephonenum;		//store into phone so as to compared after
				p = passwordcount;		//store which line is the Filepassword=inputpassword

			}

		}
		usernamecount++;		//count number of line for username
		passwordcount++;		//count number of line for passowrd
	}

	if (u == p && u != 0 && p != 0) {			//ensure usernane and phone is one line so that can get the password in same line
		do {
			cout << endl;
			cout << "1.Retrieve password" << endl;
			cout << "2.Reset password" << endl;

			cout << endl;
			cout << "Please enter 1 to retrieve your password  or 2 to reset your password:";
			getline(cin, opt3);
			cout << endl;
			if (opt3 == "1")
			{
				cout << endl;
				randomnumber = rand() % 900000 + 100000;		//produce randomnumber number 
				cout << "Verification Code:" << randomnumber << endl << endl;
				cout << "Please Enter Verification Code:";
				getline(cin, verification_code);
				verificationcode = atoi(verification_code.c_str());	//convert string to int

				if (randomnumber == verificationcode) {
					cout << "Your password is:" << password << endl;
					cout << endl;
					login(opt1);
				}
				else {
					cout << endl;
					responds = "Invalid.Please Re-enter again";
					cout << RED << responds << RESET;
					cout << endl;
				}
			}
			else if (opt3 == "2") {
				cout << "Password(Use eight characters or more, a combination of letters, numbers, and symbols.Example: ABCD1234! , please do not empty):";
				getline(cin, newpassword);
				newpassword = passwordverify(newpassword);
				ResetPassword(inputusername, newpassword, opt1);
				cout << "Repeat New Password:";
				getline(cin, Repeat_password);
				login(opt1);

			}
			else {
				cout << endl;
				responds = "Invalid.Please Re-enter again";
				cout << RED << responds << RESET;
				cout << endl;
			}
		} while (responds == "Invalid.Please Re-enter again");

	}
	else {

		if (name != inputusername && phone != inputPhone) {
			cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Username)" << RESET << endl;
			cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Phone number)" << RESET << endl;
			cout << endl;
		}
		else if (name == inputusername && phone != inputPhone) {
			cout << setfill(' ') << setw(20) << " " << RED << "(Invalid Phone number)" << RESET << endl;
			cout << endl;

		}
		else if (name != inputusername && phone == inputPhone) {
			cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Username)" << RESET << endl;
			cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Phone number)" << RESET << endl;
			cout << endl;
		}
		do {
			cout << endl;
			cout << RED << "Username and phone are no match each other" << RESET << endl;
			cout << endl;
			cout << "1.Continue forgot passowrd process" << endl;
			cout << "2.Register New Account" << endl;		//for username and password both forgot
			cout << "3.Forgot username" << endl;		//for phone remember,username forgot
			cout << "4.Login" << endl;					//for who are suddenly remember username and phone
			cout << "Please Enter 1 to continue forgot passowrd process,enter 2 to register New Account,enter 3 for forgot username process or 4 for login:";
			getline(cin, opt4);
			cout << endl;

			if (opt4 == "1")
			{
				option4 = 1;
				forgotpassword(opt1);
			}
			else if (opt4 == "2") {
				option4 = 2;
				Register(opt1);

			}
			else if (opt3 == "3") {
				option4 = 3;
				forgotusername(opt1);
			}
			else if (opt3 == "4") {
				option4 = 4;
				login(opt1);
			}
			else {
				cout << RED << "Invalid.Please Re-enter again" << RESET;
			}
		} while (option4 < 1 || option4>4);

	}
	file.close();

}