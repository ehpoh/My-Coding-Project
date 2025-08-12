#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

// Validate if it's a leap year
bool isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Validate date
bool isValidDate(const string& date) {
    if (date.length() != 10) // Format check (DD-MM-YYYY)
    {
        return false;
    }

    // separate day, month, year from the date string
    int day = 0, month = 0, year = 0;

    // Check format and separate values
    if (date[2] != '-' || date[5] != '-') // Format check for the '-'
    {
        return false; 
    }

    // day
    day = (date[0] - '0') * 10 + (date[1] - '0');

    // month
    month = (date[3] - '0') * 10 + (date[4] - '0');

    // year
    year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    // Validate year
    if (year < 1900 || year > 2100) 
    {
        return false;
    }

    // Validate month
    if (month < 1 || month > 12) 
    {
        return false;
    }

    // Validate day based on month
    const int daysInMonth[] = { 31, 28, 31, 30, 31, 30,
                                31, 31, 30, 31, 30, 31 };

    // Leap year check and day validation
    if (month == 2) 
    {
        // Adjust for leap year
        if (isLeapYear(year)) 
        {
            if (day < 1 || day > 29) 
            {
                return false;
            }
        }
        else 
        {
            if (day < 1 || day > 28) 
            {
                return false;
            }
        }
    }
    else 
    {
        if (day < 1 || day > daysInMonth[month - 1]) 
        {
            return false;
        }
    }

    return true;
}