#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime> 
#include <cmath>
#include <limits> // For numeric_limits
#include "function.h"
using namespace std;

void customerinvoice(const OrderItem orderList[], int numOrders, double serviceChargeRate) {
    double subtotal = 0.00;
    double serviceCharge = 0.00;
    double total = 0.00;

    // Create a temporary list to store items
    OrderItem NumSameOrders[MAX_ORDERS];
    int numsameorders = 0;

    string itemCode[MAX_ORDERS] { "1001","1002","1003","1004","1005","1006","1007","1008","1000","1010" };
    string itemCategory[MAX_ORDERS]{
		"beverages","food","frozen food","produce","food","food","produce","produce","produce","bakery"
	};


    // Check if there are same orders
    for (int i = 0; i < numOrders; ++i) {
        bool found = false;

        for (int j = 0; j < numsameorders; ++j) {
            if (NumSameOrders[j].name == orderList[i].name) 
            {
                // If item already exists, add quantity and price
                NumSameOrders[j].quantity += orderList[i].quantity;
                NumSameOrders[j].price += orderList[i].price * orderList[i].quantity;
                found = true;
                break;
            }
        }
        if (!found) 
        {
            // If item does not exist in NumSameOrders store, add it
            NumSameOrders[numsameorders] = orderList[i];
            NumSameOrders[numsameorders].price = orderList[i].price * orderList[i].quantity;
            ++numsameorders;
        }
    }

    time_t timestamp = time(NULL);
    struct tm* timeinfo;
    char invNoTimeStampStr[15];  
    char dateTimeStampStr[20]; 
    char displayDateStr[11]; 
    timeinfo = localtime(&timestamp);
    // Format the invNoTimeStampStr into yyyymmddHHmmss format
    strftime(invNoTimeStampStr, sizeof(invNoTimeStampStr), "%Y%m%d%H%M%S", timeinfo);
    // Format the dateTimeStampStr into yyyy-mm-dd HH:mm:ss format
    strftime(dateTimeStampStr, sizeof(dateTimeStampStr), "%Y-%m-%d %H:%M:%S", timeinfo);
    // Format the displayDateStr into dd/mm/yyyy format
    strftime(displayDateStr, sizeof(displayDateStr), "%d/%m/%Y", timeinfo);
    string invoiceNo = invNoTimeStampStr;
    string dateTime = dateTimeStampStr;
    string displayDate = displayDateStr;
    string* itemDescs = new string[numsameorders];
    string* itemPrices = new string[numsameorders];
    string* itemQuantities = new string[numsameorders];
    string* itemAmounts = new string[numsameorders];
    string* itemCodes = new string[numsameorders];
    string* itemCategories = new string[numsameorders];
    string* itemDateTimes = new string[numsameorders];
    ostringstream oss;
    double lineAmount;
	
    // Header for Customer Invoice
    cout << endl << "Order Summary:" << endl;

    // Print details like name, quantity, and price
    for (int i = 0; i < numsameorders; ++i) {
        cout << NumSameOrders[i].name << " (x" << NumSameOrders[i].quantity << ") - RM "
            << fixed << setprecision(2) << NumSameOrders[i].price << endl;
        subtotal += NumSameOrders[i].price;
		
	    lineAmount = NumSameOrders[i].quantity * NumSameOrders[i].price;
	    oss.str("");  // Set the buffer to an empty string
	    oss.clear();  // Clear any error flags
	    // Set fixed format and precision to 2 decimal places
	    oss << fixed << setprecision(2) << lineAmount;
	    // Convert the stream to a string
	    itemAmounts[i] = oss.str();
	    itemDescs[i] = NumSameOrders[i].name;
			
	    oss.str("");  // Set the buffer to an empty string
	    oss.clear();  // Clear any error flags
	    // Set fixed format and precision to 2 decimal places
	    oss << fixed << setprecision(2) << NumSameOrders[i].price;
	    // Convert the stream to a string
	    itemPrices[i] = oss.str();
	
	    itemQuantities[i] = to_string(NumSameOrders[i].quantity);
	    itemCategories[i] = itemCategory[i];
	    itemCodes[i] = itemCode[i];
	    itemDateTimes[i] = dateTime;		
    }

    // Calculate service charge and total
    serviceCharge = subtotal * serviceChargeRate;
    total = subtotal + serviceCharge;

    // Round values to the nearest cent
    total = round(total * 10) / 10;

    // Print last part of Customer Invoice
    cout << "Subtotal: RM " << fixed << setprecision(2) << subtotal << endl;
    cout << "Service Charge (" << (serviceChargeRate * 100) << "%): RM "
        << fixed << setprecision(2) << serviceCharge << endl;
    cout << "Total: RM " << fixed << setprecision(2) << total << endl << endl;
	
    string paymentType;
	
    // Call customer payment method
    CustomerPaymentmethod(paymentType);
		
    oss.str("");  // Set the buffer to an empty string
    oss.clear();  // Clear any error flags	
    // Set fixed format and precision to 2 decimal places
    oss << fixed << setprecision(2) << total;
    // Convert the stream to a string
    string totalpayStr = oss.str();
	
    writeInvoiceToHeader(invoiceNo, totalpayStr, dateTime, paymentType, "");
    writeInvoiceToLine(invoiceNo, itemCodes, itemDescs, itemPrices, itemQuantities, itemCategories, itemAmounts, itemDateTimes, numsameorders);


}
