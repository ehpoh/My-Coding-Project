#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

// Function to validate input format of yyyy
bool validateYearInput(const string& input) {
    if (input.length() != 4 || input[0] == '0') {
        return false;
    }

    // Check if the year part (first 4 characters) are digits
    for (int i = 0; i < 4; i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }

    return true;
}


// Function to validate input format of yyyy-mm
bool validateYearMonthInput(const string& input) {
    if (input.length() != 7 || input[4] != '-' || input[0] == '0') {
        return false;
    }

    // Check if the year part (first 4 characters) are digits
    for (int i = 0; i < 4; i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }
    string month = input.substr(5, 2);
    // Check if the month is valid (01-12)
    if (month != "01" && month != "02" && month != "03" && month != "04" &&
        month != "05" && month != "06" && month != "07" && month != "08" &&
        month != "09" && month != "10" && month != "11" && month != "12") {
        return false;
    }

    return true;
}

// Function to validate input format of yyyy-mm-dd
bool validateYearMonthDayInput(const string& input) {
    if (input.length() != 10 || input[4] != '-' || input[7] != '-' || input[0] == '0') {
        return false;
    }

    // Check if the year part (first 4 characters) are digits
    for (int i = 0; i < 4; i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }

    string month = input.substr(5, 2);
    // Check if the month is valid (01-12)
    if (month != "01" && month != "02" && month != "03" && month != "04" && month != "05" && month != "06" &&
        month != "07" && month != "08" && month != "09" && month != "10" && month != "11" && month != "12") {
        return false;
    }

    string day = input.substr(8, 2);
    // Check if the day is valid (01-31)
    if (day != "01" && day != "02" && day != "03" && day != "04" && day != "05" && day != "06" && day != "07" && day != "08" &&
        day != "09" && day != "10" && day != "11" && day != "12" && day != "13" && day != "14" && day != "15" && day != "16" &&
        day != "17" && day != "18" && day != "19" && day != "20" && day != "21" && day != "22" && day != "23" && day != "24" &&
        day != "25" && day != "26" && day != "27" && day != "28" && day != "29" && day != "30" && day != "31") {
        return false;
    }

    string year = input.substr(0, 4);
    int dayInt = stoi(day);
    int monthInt = stoi(month);
    int yearInt = stoi(year);

    // Days in each month
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // leap year check (year is divisible by 4 AND not divisible by 100) OR (year is divisible by 400)
    if (month == "02" && ((yearInt % 4 == 0 && yearInt % 100 != 0) || yearInt % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    // Check if month and day are within valid ranges
    if (dayInt > daysInMonth[monthInt - 1]) {
        return false;
    }

    return true;
}