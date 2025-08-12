#include "function.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Display order guide
void displayguide() {
    cout << setfill('-') << setw(64) << "-" << setfill(' ') << endl;
    cout << "Guide   : When entering the order refer to the code in the [ ].\n";
    cout << "Example : Enter Category >> A\n"
        << "          Enter Item >> 1\n"
        << "          Enter Quantity >> 1\n";
    cout << setfill('-') << setw(64) << "-" << setfill(' ') << endl << endl;
}
