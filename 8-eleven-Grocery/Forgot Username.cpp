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

void forgotusername(string opt1) {

	int Firstcomma = 0;
	int Lastcomma = 0;
	int Nextcomma = 0;
	int Pos = 0;

	int t = -1;

	string inputPhone = " ";

	string header = " ";
	string line = " ";

	string Fileusername = " ";

	string Filephonenum = " ";
	string Filepassword = " ";

	string phone = " ";



	string username = " ";

	int randomnumber = 0;

	string verification_code = " ";
	int verificationcode = 0;

	string respond = " ";
	string responds = " ";

	string opt2 = " ";
	int option2 = 0;
	string opt3 = " ";
	string opt4 = " ";

	srand(static_cast<unsigned>(time(0)));		//seed function to be called once only


	cout << endl;


	cout << "Please Enter your Phone number:";
	getline(cin, inputPhone);
	while (inputPhone.empty()) {			//no empty
		cout << endl;
		cout << RED << "Invalid phone number." << RESET << endl;
		responds = "Please Re-enter again";
		cout << RED << responds << RESET << endl << endl;

		forgotusername(opt1);
		cout << endl;


	}
	for (int i = 0; i < inputPhone.length(); i++) {				//verify so that fulfill format of phone number
		while (isalpha(inputPhone.at(i)) || isspace(inputPhone.at(i)) || inputPhone.length() < 10 || inputPhone.length() > 13 || inputPhone.at(0) != '0' || inputPhone.at(1) != '1' || inputPhone.at(3) != '-') {       //make sure phone number only contain number,must have this format:01x-xxxxxxxx
			cout << endl;
			cout << RED << "Invalid Phone number." << RESET;
			responds = "Please Re-enter again";
			cout << endl;
			cout << RED << responds << RESET << endl << endl;
			do {
				cout << endl;
				cout << "1.Forgot username" << endl;
				cout << "2.Forgot password" << endl;
				cout << "3.Register" << endl;
				cout << "4.Login" << endl;
				cout << "Please Enter 1 if you want to continue, 2 if you want to go to forgot password,3 if you want to register or 4 if you want to login:";
				getline(cin, opt2);
				cout << endl;
				if (opt2 == "1")
				{
					option2 = 1;
					forgotusername(opt1);
				}
				else if (opt2 == "2") {
					option2 = 2;
					forgotpassword(opt1);
				}
				else if (opt2 == "3") {
					option2 = 3;
					Register(opt1);
				}
				else if (opt2 == "4") {
					option2 = 4;
					login(opt1);
				}
				else {
					cout << RED << "Invalid.Please Re-enter again" << RESET;
				}
			} while (option2 < 1 || option2>4);

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


	while (getline(file, line)) {  // Read each line from the file
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


			if (inputPhone == Filephonenum) {
				username = Fileusername;		//copy fileusername into username if inputPhone == Filephone
				phone = Filephonenum;				//copy Filephonenum into phone if inputPhone == Filephone
				cout << endl;
				do {

					cout << endl;
					randomnumber = rand() % 900000 + 100000;		//produce randomnumber number 
					cout << "Verification Code:" << randomnumber << endl << endl;
					cout << "Please Enter Verification Code:";
					getline(cin, verification_code);
					verificationcode = atoi(verification_code.c_str());	//convert string to int

					if (randomnumber == verificationcode) {
						cout << "Your username is:" << username << endl << endl;
						do {
							cout << "1.Login" << endl;
							cout << "2.Forgot Password" << endl;
							cout << endl;
							cout << "Please Enter 1 if you want to login,2 if you want jump to forgot password interface:";
							getline(cin, opt3);
							if (opt3 == "1")
							{
								login(opt1);

							}
							else if (opt3 == "2") {
								forgotpassword(opt1);
							}
							else {
								cout << endl;
								responds = "Invalid.Please Re-enter again";
								cout << RED << responds << RESET;
								cout << endl << endl;

							}
						} while (responds == "Invalid.Please Re-enter again");
					}
					else {
						cout << endl;
						responds = "Invalid.Please Re-enter again";
						cout << RED << responds << RESET;
						cout << endl;
					}
				} while (responds == "Invalid.Please Re-enter again");
			}

		}

	}

	if (inputPhone != Filephonenum) {
		cout << endl;
		respond = "Invalid.Please Re-enter again";
		cout << RED << "Invalid.Please Re-enter again" << RESET << endl;
		cout << endl;
		do {
			cout << "1.Forgot username" << endl;
			cout << "2.Forgot password" << endl << endl;
			cout << "Please enter 1 if want continue to forgot username process or 2 go to forgot password process:";
			getline(cin, opt4);
			cout << endl;
			if (opt4 == "1")
			{
				forgotusername(opt1);
			}
			else if (opt4 == "2") {
				forgotpassword(opt1);
			}
			else {
				respond = "Invalid.Please Re-enter again";
				cout << RED << respond << RESET << endl;
			}
		} while (respond == "Invalid.Please Re-enter again");
	}


	file.close();
}