#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

double serviceFee(double amount) {
	// This function calculates the service fee for a customer
	double returnVal;
	if (amount < 50)
		returnVal = amount * 0.10;
	else if (amount < 100)
		returnVal = amount * 0.05;
	else
		returnVal = 0.0;
	return returnVal;
}

double discount(int deptNum, double amount) {
	// This function calculates the discount for an item
	if (deptNum == 1 || deptNum == 2)
		if (amount >= 10)
			return amount * 0.05;
		else return 0;
	
	else if (deptNum == 3 || deptNum == 4)
		if (amount >= 25)
			return amount * 0.08;
		else return 0;
			
	else {
			std::cout << "Invalid department number, terminating the program...\n";
			exit(1);
	}
}

void printHeader(int cID) {
	// This function prints out the header information
	std::cout << std::setw(30) << " " << "HIGH FASHION DEPARTMENT STORE\n"
	          << std::setw(32) << " " << "MONTHLY BILLING STATEMENT\n" 
	          << std::setw(37) << " " << "CUSTOMER# " << cID
			  << std::endl;
	std::cout << std::setw(16) << std::left << "DEPT NBR" 
			  << std::setw(16) << std::left << "ITEM NBR" 
			  << std::setw(25) << std::left << "AMOUNT OF PURCHASE"
			  << std::setw(16) << std::left << "DISCOUNT AMT" 
			  << std::setw(7)  << std::left << "NET AMT" 
			  << std::endl; 
	for (int k = 0; k < 70; k++) {
		std::cout << '-';
	}
	std::cout << '\n';
}

int main() {
	std::ifstream fin("customer.txt");
	if (fin == NULL) {
		// check if the input file exists
		std::cout << "Error: input file cannot be found." << std::endl;
		exit(1);
	}
	std::string currentLine;
	double curDeptTotal = 0;  // The total item amount for a department
	double curDeptDisc = 0;  // The total discount for a department
	double netTotal = 0;   // The net total for an item.
	int counter = 0;  // counts the number of times the loop runs
	int cNumber;  // customer number
	int dept;     // department number
	int itemNum;  // item number
	double itemAmount;  // total amount spent on the item
	double itemDiscount;   // discount for the item
	double itemNet;    // net price for the item
	int prevCustomer = -1; // The customer number of the last line
	int prevDept = -1;  // current department number
	
	while (!fin.eof()) {
		getline(fin, currentLine);
		int sector = 0;
		std::string buffer = "";
		for (int i = 0; i < currentLine.length(); i++) {
			if (currentLine[i] == ' ') {
				if (buffer.length() != 0) {
					if (sector == 0) {
						cNumber = std::stoi(buffer);
					} else if (sector == 1) {
						dept = std::stoi(buffer);
					} else if (sector == 2) {
						itemNum = std::stoi(buffer);
					} else if (sector == 3) {
						itemAmount = std::stod(buffer);
					} else {
						std::cout << "An error is in the file. Exit." << std::endl;
						exit(1);
					}
					buffer.clear();
					sector ++;
				}
			} else {
				buffer += currentLine[i];
			}
		}
		if (buffer.length() != 0) {
			itemAmount = std::stod(buffer);
		}
		// Perform input checks.
		if (itemAmount < 0) {
			std::cout << "The item amount cannot be negative. Terminating the program." << std::endl;
			exit(1);
		}
		if (dept < 1 || dept > 4) {
			std::cout << "Invalid department number, terminating the program...\n";
			exit(1);
		}
		if (cNumber < 0) {
			std::cout << "Invalid customer number, terminating the program...\n";
			exit(1);
		}
		
		if (prevCustomer != -1) {
			if (cNumber != prevCustomer) {
				break;
			}
		} else {
			prevCustomer = cNumber;
		}
		
		if(counter == 0) {
			printHeader(prevCustomer);
		}
		
		if (prevDept != -1) {
			if (dept != prevDept) {
				netTotal += curDeptTotal - curDeptDisc;
				std::cout << "\n";
				std::cout << std::setw(16) << "TOTAL DEPT:  "
						  << std::setw(16) << prevDept
						  << std::setw(25) << std::setprecision(2) << curDeptTotal
						  << std::setw(16) << std::setprecision(2) << curDeptDisc
						  << std::setw(7)  << std::setprecision(2) << curDeptTotal - curDeptDisc
						  << "\n"
						  << std::endl;
				curDeptTotal = 0;
				curDeptDisc = 0;
			}
		}
		
		itemDiscount = discount(dept, itemAmount);
		itemNet = itemAmount - itemDiscount;
		curDeptTotal += itemAmount;
		curDeptDisc += itemDiscount;
		std::cout << std::fixed;
		std::cout << std::setw(16) << std::left << dept 
			      << std::setw(16) << std::left << itemNum
			      << std::setw(25) << std::left << std::setprecision(2) << itemAmount
			 	  << std::setw(16) << std::left << std::setprecision(2) << itemDiscount
				  << std::setw(7)  << std::left << std::setprecision(2) << itemNet
				  << '\n';
		prevDept = dept;
		counter++;
		
	}
	
	netTotal += curDeptTotal - curDeptDisc;
	std::cout << "\n";
	std::cout << std::setw(16) << "TOTAL DEPT:  "
			  << std::setw(16) << prevDept
			  << std::setw(25) << std::setprecision(2) << curDeptTotal
			  << std::setw(16) << std::setprecision(2) << curDeptDisc
			  << std::setw(7)  << std::setprecision(2) << curDeptTotal - curDeptDisc
			  << "\n"
			  << std::endl;
			  
	double salesTax = netTotal * 0.07;
	double serviceCharge = serviceFee(netTotal);
	
	std::cout << std::setw(32) << " " << std::setw(22) << std::left << "NET TOTAL AMOUNT" << netTotal << "\n"
			  << std::setw(32) << " " << std::setw(22) << std::left << "SALES TAX AT 7%"  << salesTax << "\n"
			  << std::setw(32) << " " << std::setw(22) << std::left << "SERVICE CHARGE"   << serviceCharge << "\n"
			  << std::endl;
	std::cout << "FINAL TOTAL - PLEASE PAY THIS AMOUNT: " << netTotal + salesTax << std::endl;
	
	return 0;
} 
