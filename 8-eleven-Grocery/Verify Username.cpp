#include <iostream>
#include<iomanip>
#include "function.h"
#include<string>
#include<cctype>
#include <cstring> 
#include<fstream>
#define X -1
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

string usernameverify(string username)
{
    string header = "";
    string line = "";
    string respond = " ";
    string Fileusername = " ";
    int Firstcomma = 0;

    char c = ' '; // character

    // Open the file for reading
    ifstream file;
    file.open("customer.txt", ios::app);  // open the file in append mode
    if (!file.is_open()) {  // Check if the file was opened successfully
        cout << RED << "Error opening file." << RESET << endl;

    }

    getline(file, header); //read the first line header


    //format of line:username,password,phone

    getline(file, line);	//read the first line header


    while (getline(file, line)) {  // Read each line from the file
        // .find(character,start position)
        Firstcomma = line.find(',');		 //find the first position of ','


        if (Firstcomma != X) {               //If no comma is found, `firstcomma

            // .substr(start position,number of character)
            Fileusername = line.substr(0, Firstcomma);  // 0 is the starting point,position (firstcomma),extract substring username between starting point and first comma

            while (username.empty()) {
                cout << endl;
                cout << setw(10) << " " << RED << "(Invalid username)" << RESET << endl;
                respond = "Please Re-enter again";
                cout << RED << respond << RESET << endl << endl;
                cout << setw(10) << " " << "Username: ";
                getline(cin, username);
                username = usernameverify(username);

            }
            //for loop to check each character
            for (int i = 0; i < username.length(); ++i) {
                c = username.at(i);		// character in username
                if (!(isalpha(c))) {		//is uppercase character?

                    cout << setw(10) << " " << RED << "(Invalid username)" << RESET << endl << endl;
                    respond = "Please Re-enter again";
                    cout << RED << respond << RESET << endl << endl;
                    cout << setw(10) << " " << "Username: ";
                    getline(cin, username);
                    username = usernameverify(username);
                }


            }

            while (Fileusername == username) {          //repeat loop when the username=filename
                cout << endl;
                cout << setw(10) << " " << RED << "(Invalid Username)" << RESET << endl << endl;
                cout << RED << "Please Re-enter again" << RESET << endl;
                cout << endl;
                cout << setw(10) << " " << "Username: ";
                getline(cin, username);
                username = usernameverify(username);
            }
        }


    }



    file.close();   // Close the file

    return username;
}