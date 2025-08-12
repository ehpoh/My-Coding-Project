#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
using namespace std;

// Constants
const int MAX_ORDERS = 100;

// Struct to represent an order item
struct OrderItem {
    string name;
    int quantity;
    double price;
};

// Function declarations
void customerfunction();
void customerinvoice(const OrderItem orderList[], int numOrders, double serviceChargeRate);
void CustomerPaymentmethod(string& paymentType);
void displayguide();
void stafforderdetails(char category, int item, int quantity);
void generateinvoice(const int numItem[], const int quantity[], int orderCount, const char category[], const string& date);
void customermenu();
void Tprintlogo();
void displayoption();
bool isLeapYear(int year);
bool isValidDate(const string& date);
void stafforderfunction(const string& date);
void receipt(const int numItem[], const int quantity[], int orderCount, double paid1, double change, int PayFunc, double totalpay, double sum, double serviceCharge, double Tax, int totalItem, const char category[]);
void reportingfunction();
void userroleselection();
void option(string opt1);
void optional(string remainder, string opt1);
string usernameverify(string username);
string verifyphone(string phone);
string passwordverify(string password);
void ResetPassword(string username, string newpassword, string opt1);
void Register(string opt1);
void forgotusername(string opt1);
void forgotpassword(string opt1);
void login(string opt1);
int main();
void Exitfunction();
void writeInvoiceToHeader(const string& invoiceNumber, const string& amount, const string& datetime, const string& paymentType, const string& paymentNumber);
void writeInvoiceToLine(const string& invoiceNumber, const string itemCodes[], const string descriptions[], const string prices[], const string qtys[], const string categories[], const string lineAmounts[], const string dateTimes[], int numEntries); 

#endif // FUNCTION_H
