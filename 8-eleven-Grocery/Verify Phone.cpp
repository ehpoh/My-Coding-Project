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

string verifyphone(string phone)
{
    string header = "";
    string line = "";
    string respond = " ";




    int t = -1;

    int Firstcomma = 0;
    int Lastcomma = 0;
    int Pos = 0;
    int Nextcomma = 0;

    string Fileusername = " ";
    string Filepassword = " ";
    string Filephonenum = " ";


    // Open the file for reading
    ifstream file;
    file.open("customer.txt", ios::in);
    if (!file.is_open()) {  // Check if the file was opened successfully
        cout << RED << "Error opening file." << RESET << endl;

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

            do {


                while (phone.empty()) {
                    cout << endl;
                    cout << RED << "Invalid phone number." << RESET << endl;
                    respond = "Please Re-enter again";
                    cout << RED << respond << RESET << endl << endl;
                    cout << setw(10) << " " << "Phone:";
                    getline(cin, phone);
                    verifyphone(phone);
                    cout << endl;


                }
                for (int i = 0; i < phone.length(); i++) {				//verify so that fulfill format of phone number
                    while (isalpha(phone.at(i)) || isspace(phone.at(i)) || phone.length() < 10 || phone.length() > 13 || phone.at(0) != '0' || phone.at(1) != '1' || phone.at(3) != '-') {       //make sure phone number only contain number,must have this format:012-xxxxxxxx
                        cout << endl;
                        cout << RED << "Invalid phone number." << RESET << endl;
                        respond = "Please Re-enter again";
                        cout << RED << respond << RESET << endl << endl;
                        cout << setw(10) << " " << "Phone number:";
                        getline(cin, phone);
                        verifyphone(phone);
                        cout << endl;

                    }

                }

                while (Filephonenum == phone) {

                    cout << RED << "Phone number already exist." << RESET << endl << endl;
                    respond = "Please Re-enter again";
                    cout << RED << respond << RESET << endl << endl;
                    cout << setw(10) << " " << "Phone:";
                    getline(cin, phone);
                    verifyphone(phone);
                    cout << endl;
                }
            } while (respond == "Invalid.Please Re-enter again");



        }



    }
    file.close();   // Close the file
    return phone;
}