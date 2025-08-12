#include <iostream>
#include <fstream>
#include <string>
#define X -1
using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Function to update the password for a specific user
void ResetPassword(string username, string newpassword, string opt1) {

    int Firstcomma = 0;
    int Lastcomma = 0;
    int Nextcomma = 0;
    int Pos = 0;

    int t = -1;

    string Fileusername = " ";

    string Filephonenum = " ";
    string Filepassword = " ";

    string header = "";

    string updatedContent = "";
    string line = "";

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


    // Temporary storage for updated file content


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

            // Check if this is the user we want to update.if yes,change the password to new password
            if (Fileusername == username) {
                Filepassword = newpassword;

            }

            // Append the line to the updated content
            updatedContent += Fileusername + "," + Filepassword + "," + Filephonenum + "\n";
        }



    }
    file.close();
    ofstream outFile;
    // Write the updated content back to the original file
    if (opt1 == "1") {
        outFile.open("customer.txt");  // Open file for writing (overwrite)
        if (!outFile.is_open()) {
            cout << RED << "Error opening file for writing." << RESET << endl;
            return;
        }
    }
    else {

        outFile.open("staff.txt");  // Open file for writing (overwrite)
        if (!outFile.is_open()) {
            cout << RED << "Error opening file for writing." << RESET << endl;
            return;
        }
    }
    outFile << header << endl;
    outFile << updatedContent;
    outFile.close();
}


