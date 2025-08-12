#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include "function.h"
using namespace std;
#define X -1

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void login(string opt1) {

	string date;

	string header = " ";
	string line = " ";

	string inputName = " ";
	string inputPass = " ";
	string name = " ";
	string pass = " ";
	string Fileusername = " ";
	string Filepassword = " ";


	string Warning1 = " ";
	string Warning2 = " ";
	string remainder = " ";

	int t = -1;
	int Firstcomma = 0;		//comma
	int Lastcomma = 0;		//remaining part
	int Pos = 0;
	int NextComma;

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


	cout << endl;
	cout << "Login" << endl;
	cout << setw(10) << " " << "Username: ";
	getline(cin, inputName);

	cout << setw(10) << " " << "Password: ";
	getline(cin, inputPass);

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
				NextComma = line.find(',', Pos + 1);		//pos + 1 is start position,if find ',' after pos,as a next comma
				if (NextComma == X) {			//If no comma is found, `nextComma` will be `X` (which is -1).
					break;
				}
				Lastcomma = NextComma;		//assume nextcomma is last comma if have other comma found
				Pos = NextComma;			//nextcomma/lastcomma is store into pos,thus pos is last comma
			}

			// .substr(start position,number of character)
			Fileusername = line.substr(0, Firstcomma);  // 0 is the starting point,position (firstcomma),extract substring username between starting point and first comma
			Filepassword = line.substr(Firstcomma + 1, Lastcomma - Firstcomma - 1);  // firstcomma + 1 is the starting point,position (lastcomma - firstcomma - 1),-1 so that no include last comma,extract substring username between starting point and first comma



			// Check if the input credentials match the file data
			if (inputName == Fileusername && inputPass == Filepassword) {
				if (opt1 == "1") {
					cout << setw(10) << " " << "(Login sucessfully)" << endl;
					cout << endl;
					customerfunction();
					name = Fileusername;
					pass = Filepassword;
				}
				else {
					cout << setw(10) << " " << "(Login sucessfully)" << endl;
					cout << endl;
					displayoption; //staffmenu();

					name = Fileusername;
					pass = Filepassword;
				}
			}
			else if (inputName == Fileusername) {
				name = Fileusername;		//store into name so as to compared after



			}
			else if (inputPass == Filepassword) {

				pass = Filepassword;		//store into pass so as to compared after

			}
		}
	}

	if (inputName != name && inputPass != pass) {
		cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Username)" << RESET << endl;
		cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Password)" << RESET << endl;
		cout << endl;
		remainder = "Please re-enter again";
		optional(remainder, opt1);

		cout << endl;


	}
	else if (inputName == name && inputPass != pass) {
		cout << setfill(' ') << setw(20) << " " << RED << "(Invalid Password)" << RESET << endl;
		cout << endl;
		remainder = "Please re-enter again";
		optional(remainder, opt1);

		cout << endl;

	}
	else if (inputName != name && inputPass == pass) {
		cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Username)" << RESET << endl;
		cout << setfill(' ') << setw(10) << " " << RED << "(Invalid Password)" << RESET << endl;
		cout << endl;
		remainder = "Please re-enter again";
		optional(remainder, opt1);

		cout << endl;

	}




	file.close();   // Close the file

}







