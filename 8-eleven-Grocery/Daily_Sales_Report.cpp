#include"Report.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// ANSI escape codes for colors
const string RED = "\033[31m";
const string RESET = "\033[0m";

void displayDailySalesReport() {
	// Input validation
	string input;
	cout << "Please enter a date (yyyy-mm-dd): ";
	cin >> input;

	while (validateYearMonthDayInput(input) == false) {
		cout << RED << "Invalid input! Please enter in format yyyy-mm-dd: " << RESET;
		cin >> input;
	}

	string year = input.substr(0, 4);
	string month = input.substr(5, 2);
	string day = input.substr(8, 2);

	// assume daily transaction limit will be below 1000
	const int lineCount = 1000;

	int totalUnitSold = 0;
	double totalSales = 0;
	int totalTransactions = 0;
	int lineIndex = 0;

	int stationeryCategoryQuantity[lineCount] = { 0 }; double stationeryCategorySales[lineCount] = { 0.0 };
	int foodCategoryQuantity[lineCount] = { 0 }; double foodCategorySales[lineCount] = { 0.0 };
	int bathCategoryQuantity[lineCount] = { 0 }; double bathCategorySales[lineCount] = { 0.0 };
	int haircareCategoryQuantity[lineCount] = { 0 }; double haircareCategorySales[lineCount] = { 0.0 };
	int cleaningCategoryQuantity[lineCount] = { 0 }; double cleaningCategorySales[lineCount] = { 0.0 };
	int beveragesCategoryQuantity[lineCount] = { 0 }; double beveragesCategorySales[lineCount] = { 0.0 };
	int laundryCategoryQuantity[lineCount] = { 0 }; double laundryCategorySales[lineCount] = { 0.0 };
	int skincareCategoryQuantity[lineCount] = { 0 }; double skincareCategorySales[lineCount] = { 0.0 };
	int oralCareCategoryQuantity[lineCount] = { 0 }; double oralCareCategorySales[lineCount] = { 0.0 };
	int meatCategoryQuantity[lineCount] = { 0 }; double meatCategorySales[lineCount] = { 0.0 };
	int seafoodCategoryQuantity[lineCount] = { 0 }; double seafoodCategorySales[lineCount] = { 0.0 };
	int pantryCategoryQuantity[lineCount] = { 0 }; double pantryCategorySales[lineCount] = { 0.0 };
	int dairyCategoryQuantity[lineCount] = { 0 }; double dairyCategorySales[lineCount] = { 0.0 };
	int frozenFoodCategoryQuantity[lineCount] = { 0 }; double frozenFoodCategorySales[lineCount] = { 0.0 };
	int produceCategoryQuantity[lineCount] = { 0 }; double produceCategorySales[lineCount] = { 0.0 };
	int bakeryCategoryQuantity[lineCount] = { 0 }; double bakeryCategorySales[lineCount] = { 0.0 };
	int snacksCategoryQuantity[lineCount] = { 0 }; double snacksCategorySales[lineCount] = { 0.0 };
	int otherCategoryQuantity[lineCount] = { 0 }; double otherCategorySales[lineCount] = { 0.0 };
	string categoryValues[] = { "stationery", "food", "bath", "haircare", "cleaning", "beverages", "laundry", "skincare", "oral care", "meat", "seafood", "pantry",
"dairy", "frozen food", "produce", "bakery", "snacks", "others" };
	int categoryTotalUnitSold[18] = { 0 };
	double categoryTotalSales[18] = { 0.0 };

	const string fileName = "TxTData_Files/Invoice_Line.txt";
	ifstream file(fileName);

	if (file.is_open() == false) {
		cout << RED << "Error: File TxTData_Files/Invoice_Line.txt not found!" << RESET << endl;

	}
	// Skip the first line (header)
	string line = "";
	getline(file, line);

	// Process each row of the file
	while (getline(file, line)) {

		int pos = 0, prevPos = 0;
		string invoiceNumber, itemCode, itemDesc, unitPriceStr, quantityStr, category, lineAmountStr, dateTime;
		// Get invoice number
		pos = line.find(',', prevPos);
		invoiceNumber = line.substr(prevPos, pos - prevPos);
		prevPos = pos + 1;

		// Get item code
		pos = line.find(',', prevPos);
		itemCode = line.substr(prevPos, pos - prevPos);
		prevPos = pos + 1;

		// Get item desc
		pos = line.find(',', prevPos);
		itemDesc = line.substr(prevPos, pos - prevPos);
		prevPos = pos + 1;

		// Get unit price
		pos = line.find(',', prevPos);
		unitPriceStr = line.substr(prevPos, pos - prevPos);
		prevPos = pos + 1;

		// Get quantity
		pos = line.find(',', prevPos);
		quantityStr = line.substr(prevPos, pos - prevPos);
		prevPos = pos + 1;

		// Get category
		pos = line.find(',', prevPos);
		category = line.substr(prevPos, pos - prevPos);
		prevPos = pos + 1;


		// Get line amount
		pos = line.find(',', prevPos);
		lineAmountStr = line.substr(prevPos, pos - prevPos);
		prevPos = pos + 1;

		// Get date time
		dateTime = line.substr(prevPos);

		string fileLineYear = dateTime.substr(0, 4);  // Get first 4 characters: "2024"
		string fileLineMonth = dateTime.substr(5, 2); // Get 2 characters starting at index 5: "09"
		string fileLineDay = dateTime.substr(8, 2);

		// Check if the year and month match the input
		if (fileLineYear == year && fileLineMonth == month && fileLineDay == day)
		{
			int categoryUnitSold = stoi(quantityStr);
			double categorySales = stod(lineAmountStr);
			if (category == "stationery")
			{
				stationeryCategoryQuantity[lineIndex] = categoryUnitSold;
				stationeryCategorySales[lineIndex] = categorySales;
			}
			else if (category == "food")
			{
				foodCategoryQuantity[lineIndex] = categoryUnitSold;
				foodCategorySales[lineIndex] = categorySales;
			}
			else if (category == "bath")
			{
				bathCategoryQuantity[lineIndex] = categoryUnitSold;
				bathCategorySales[lineIndex] = categorySales;
			}
			else if (category == "haircare")
			{
				haircareCategoryQuantity[lineIndex] = categoryUnitSold;
				haircareCategorySales[lineIndex] = categorySales;
			}
			else if (category == "cleaning")
			{
				cleaningCategoryQuantity[lineIndex] = categoryUnitSold;
				cleaningCategorySales[lineIndex] = categorySales;
			}
			else if (category == "beverages")
			{
				beveragesCategoryQuantity[lineIndex] = categoryUnitSold;
				beveragesCategorySales[lineIndex] = categorySales;
			}
			else if (category == "laundry")
			{
				laundryCategoryQuantity[lineIndex] = categoryUnitSold;
				laundryCategorySales[lineIndex] = categorySales;
			}
			else if (category == "skincare")
			{
				skincareCategoryQuantity[lineIndex] = categoryUnitSold;
				skincareCategorySales[lineIndex] = categorySales;
			}
			else if (category == "oral care")
			{
				oralCareCategoryQuantity[lineIndex] = categoryUnitSold;
				oralCareCategorySales[lineIndex] = categorySales;
			}
			else if (category == "meat")
			{
				meatCategoryQuantity[lineIndex] = categoryUnitSold;
				meatCategorySales[lineIndex] = categorySales;
			}
			else if (category == "seafood")
			{
				seafoodCategoryQuantity[lineIndex] = categoryUnitSold;
				seafoodCategorySales[lineIndex] = categorySales;
			}
			else if (category == "pantry")
			{
				pantryCategoryQuantity[lineIndex] = categoryUnitSold;
				pantryCategorySales[lineIndex] = categorySales;
			}
			else if (category == "dairy")
			{
				dairyCategoryQuantity[lineIndex] = categoryUnitSold;
				dairyCategorySales[lineIndex] = categorySales;
			}
			else if (category == "frozen food")
			{
				frozenFoodCategoryQuantity[lineIndex] = categoryUnitSold;
				frozenFoodCategorySales[lineIndex] = categorySales;
			}
			else if (category == "produce")
			{
				produceCategoryQuantity[lineIndex] = categoryUnitSold;
				produceCategorySales[lineIndex] = categorySales;
			}
			else if (category == "bakery")
			{
				bakeryCategoryQuantity[lineIndex] = categoryUnitSold;
				bakeryCategorySales[lineIndex] = categorySales;
			}
			else if (category == "snacks")
			{
				snacksCategoryQuantity[lineIndex] = categoryUnitSold;
				snacksCategorySales[lineIndex] = categorySales;
			}
			else
			{
				otherCategoryQuantity[lineIndex] = categoryUnitSold;
				otherCategorySales[lineIndex] = categorySales;
			}
			totalTransactions = totalTransactions + 1;
		}

		lineIndex = lineIndex + 1;
	}

	// Close the file
	file.close();

	//Sum total quantities and sales by categories
	for (int i = 0; i < lineCount; i++)
	{
		categoryTotalUnitSold[0] = categoryTotalUnitSold[0] + stationeryCategoryQuantity[i];
		categoryTotalUnitSold[1] = categoryTotalUnitSold[1] + foodCategoryQuantity[i];
		categoryTotalUnitSold[2] = categoryTotalUnitSold[2] + bathCategoryQuantity[i];
		categoryTotalUnitSold[3] = categoryTotalUnitSold[3] + haircareCategoryQuantity[i];
		categoryTotalUnitSold[4] = categoryTotalUnitSold[4] + cleaningCategoryQuantity[i];
		categoryTotalUnitSold[5] = categoryTotalUnitSold[5] + beveragesCategoryQuantity[i];
		categoryTotalUnitSold[6] = categoryTotalUnitSold[6] + laundryCategoryQuantity[i];
		categoryTotalUnitSold[7] = categoryTotalUnitSold[7] + skincareCategoryQuantity[i];
		categoryTotalUnitSold[8] = categoryTotalUnitSold[8] + oralCareCategoryQuantity[i];
		categoryTotalUnitSold[9] = categoryTotalUnitSold[9] + meatCategoryQuantity[i];
		categoryTotalUnitSold[10] = categoryTotalUnitSold[10] + seafoodCategoryQuantity[i];
		categoryTotalUnitSold[11] = categoryTotalUnitSold[11] + pantryCategoryQuantity[i];
		categoryTotalUnitSold[12] = categoryTotalUnitSold[12] + dairyCategoryQuantity[i];
		categoryTotalUnitSold[13] = categoryTotalUnitSold[13] + frozenFoodCategoryQuantity[i];
		categoryTotalUnitSold[14] = categoryTotalUnitSold[14] + produceCategoryQuantity[i];
		categoryTotalUnitSold[15] = categoryTotalUnitSold[15] + bakeryCategoryQuantity[i];
		categoryTotalUnitSold[16] = categoryTotalUnitSold[16] + snacksCategoryQuantity[i];
		categoryTotalUnitSold[17] = categoryTotalUnitSold[17] + otherCategoryQuantity[i];

		categoryTotalSales[0] = categoryTotalSales[0] + stationeryCategorySales[i];
		categoryTotalSales[1] = categoryTotalSales[1] + foodCategorySales[i];
		categoryTotalSales[2] = categoryTotalSales[2] + bathCategorySales[i];
		categoryTotalSales[3] = categoryTotalSales[3] + haircareCategorySales[i];
		categoryTotalSales[4] = categoryTotalSales[4] + cleaningCategorySales[i];
		categoryTotalSales[5] = categoryTotalSales[5] + beveragesCategorySales[i];
		categoryTotalSales[6] = categoryTotalSales[6] + laundryCategorySales[i];
		categoryTotalSales[7] = categoryTotalSales[7] + skincareCategorySales[i];
		categoryTotalSales[8] = categoryTotalSales[8] + oralCareCategorySales[i];
		categoryTotalSales[9] = categoryTotalSales[9] + meatCategorySales[i];
		categoryTotalSales[10] = categoryTotalSales[10] + seafoodCategorySales[i];
		categoryTotalSales[11] = categoryTotalSales[11] + pantryCategorySales[i];
		categoryTotalSales[12] = categoryTotalSales[12] + dairyCategorySales[i];
		categoryTotalSales[13] = categoryTotalSales[13] + frozenFoodCategorySales[i];
		categoryTotalSales[14] = categoryTotalSales[14] + produceCategorySales[i];
		categoryTotalSales[15] = categoryTotalSales[15] + bakeryCategorySales[i];
		categoryTotalSales[16] = categoryTotalSales[16] + snacksCategorySales[i];
		categoryTotalSales[17] = categoryTotalSales[17] + otherCategorySales[i];

	}

	// Display the report
	const string months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	const int tableWidth = 60;
	cout << endl;
	cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;
	cout << "Daily Sales Report (" << day << " " << months[stoi(month) - 1] << " " << year << ")" << endl;
	cout << setfill('=') << setw(tableWidth) << "" << setfill(' ') << endl;

	// Print summary header
	cout << left;  // Align text to the left
	cout << setw(30) << "[Category]";
	cout << right;
	cout << setw(12) << "[Unit Sold]" << setw(18) << "[Total Sales(RM)]" << endl;
	cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;

	int sizeOfCategoryTotalUnitSold = sizeof(categoryTotalUnitSold) / sizeof(categoryTotalUnitSold[0]); //18

	// Print table content
	for (int i = 0; i < sizeOfCategoryTotalUnitSold; i++)
	{
		cout << left;  // Align text to the left
		cout << setw(30) << categoryValues[i];
		cout << right;
		cout << setw(12) << categoryTotalUnitSold[i] << setw(18) << fixed << setprecision(2) << categoryTotalSales[i] << endl;

		totalUnitSold = totalUnitSold + categoryTotalUnitSold[i];
		totalSales = totalSales + categoryTotalSales[i];
	}

	// Print total footer
	cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
	cout << left;  // Align text to the left
	cout << setw(30) << "Total";
	cout << right;
	cout << setw(12) << totalUnitSold << setw(18) << fixed << setprecision(2) << totalSales << endl;

	// Print summary footer	
	cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
	cout << left;
	cout << setw(30) << "Summary:" << endl;
	cout << left;
	cout << "Total Transactions: " << totalTransactions << endl;
	cout << setfill('-') << setw(tableWidth) << "" << setfill(' ') << endl;
}

