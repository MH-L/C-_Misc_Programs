#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdlib>

int main() {
	// get the data file to read
	std::ifstream fin("data.txt");
	std::string currentLine; // the current line in the file the reader is reading
	int sector; // to determine which variable the data should be stored in
	int numEmployees = 0; // calculates total number of employees
	// variables for the company
	float totalGrossPay = 0;
	float totalNetPay = 0;
	float totalDeduction = 0;
	float totalPension = 0;
	// print the header of the chart
	printf("Social insurance NO.     gross pay     net pay     pensions     deductions\n");
	while (!fin.eof() /* While this is not the end of the file*/) {
		long int sin;
		float payRate;
		int numOfExemptions;
		float hoursWorked;
		char prev;
		std::string infileString;
		// variables for a single employee
		float grossPay = 0;
		float netPay = 0;
		float pension = 0;
		float deduction = 0;
		getline(fin,currentLine);
		sector = 0;	
		numEmployees ++;
		// std::cout << "Data from file: " << currentLine << std::endl;
		for (int i = 0; i < currentLine.length(); i++){
			if (i != 0)
				prev = currentLine[i-1];
			if (sector >= 4) {
				// if there are more than 4 sectors then there must be an error
				std::cout << "An error occurred in the file!" << std::endl;
				return 1;
			}
			if (currentLine[i] != ' '){
				infileString = infileString + currentLine[i];
			} else {
				if (prev != ' ' /* this denotes the end of a section of the line*/) {
					switch (sector) {
						case 0: /* the first sector is sin number*/
							// Checking if the sin number is 9 digits
							if (infileString.length() != 9) {
								std::cout << "An error occurred! The sin number must be nine digits!" << std::endl;
								return 1;
							}
							sin = std::atoi(infileString.c_str());
							break;
						case 1: /* the second sector is pay rate*/
							payRate = (float) atof(infileString.c_str());
							if (payRate < 0) {
								std::cout << "The pay rate cannot be negative. Error!" << std::endl;
								return 1;
							}
							break;
						case 2: /* the third sector is number of exemptions*/
							numOfExemptions = std::atoi(infileString.c_str());
							if (numOfExemptions < 0) {
								std::cout << "The number of exemptions cannot be negative. Error!" << std::endl;
								return 1;
							}
							break;
						case 3: /* the fourth sector is the total hours worked*/
							hoursWorked = (float) atof(infileString.c_str());
							if (hoursWorked < 0) {
								std::cout << "The hours worked cannot be negative. Error!" << std::endl;
								return 1;
							}
							break;
						default:
							std::cout << "Error!" << std::endl;
					}
					sector++;
					infileString.clear();
				} else {
					continue;
				}
			}
		}
		if (!infileString.empty()) {
			hoursWorked = (float) atof(infileString.c_str());
		}
		
		// Calculate the gross pay of an employee
		if (hoursWorked > 40) {
			if (hoursWorked > 54) {
				grossPay = 40 * payRate + 14 * payRate * 1.5;
			} else {
				grossPay = 40 * payRate + (hoursWorked - 40) * 1.5 * payRate;
			}
		} else {
			grossPay = hoursWorked * payRate;
		}
		
		// Calculate the pension for an employee
		if (grossPay * 0.077 > 16.5) {
			pension = 16.5;
		} else {
			pension = grossPay * 0.077;
		}
			
		// Calculate the deduction for an employee
		float taxable = grossPay - 14 * numOfExemptions - 11;
		if (taxable <= 0)
			taxable = 0;
		float federal = taxable * (0.14 + 2.3e-4);
		float provincal = 0.35 * federal;
		deduction = federal + provincal + pension;
		
		// Calculate the net pay for an employee
		netPay = grossPay - deduction;
		
		printf("%i               %.2f         %.2f        %.2f        %.2f\n", sin, grossPay, netPay, pension, deduction);
		totalGrossPay += grossPay;
		totalPension += pension;
		totalNetPay += netPay;
		totalDeduction += deduction;
	}
	printf("Number of employees processed: %i\n", numEmployees);
	printf("Total gross pay for all employees: %.2f\n", totalGrossPay);
	printf("Total net pay for all employees: %.2f\n", totalNetPay);
	printf("Total pension for all employees: %.2f\n", totalPension);
	printf("Total deduction for all employees: %.2f\n", totalDeduction);
	
	fin.close();
}
