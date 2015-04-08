#include <iomanip>
#include <iostream>
#include <fstream>

/* This function extracts all the records from the given txt file
   and checks for the invalid records
   */
void interpret(std::string line, int sales[], int values[]) {
	int section = 0;
	std::string buffer = "";
	std::string words[4];
	char prevChar = ' ';
	int sale;  // sales of a record
	int agentID;  // agent id of a record
	double price; // unit price of the sale
	
	// Extract words from the input file. Use space to separate words.
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ') {
			if (prevChar != ' ') {
				if (section == 0) {
					agentID = std::stoi(buffer);
				} else if (section == 1) {
					sale = std::stoi(buffer);
				} else if (section == 2) {
					price = std::stod(buffer);
				} else {
					std::cout << "The file is in invalid format!";
					exit(1);
				}
				section ++;
				buffer="";
			}
		} else {
			buffer += line[i];
			prevChar = line[i];
		}
	}
	
	if (buffer.length() != 0) {
		price = std::stod(buffer);
	}
	
	if (agentID < 1 || agentID > 20) {
		// check if the agent id is invalid: the ID must be within 1 to 20
		std::cout << std::setw(5) << std::left << agentID
				  << std::setw(5) << std::left << sale
				  << std::setw(9) << std::left << price 
				  << "Invalid Agent!" << std::endl;
	} else if (sale < 0) {
		// check if the sales is invalid: the sales cannot be negative
		std::cout << std::setw(5) << std::left << agentID
				  << std::setw(5) << std::left << sale
				  << std::setw(9) << std::left << price 
				  << "Invalid Sales!" << std::endl;
	} else if (price < 0) {
		// check if the price is invalid: the price must be positive
		std::cout << std::setw(5) << std::left << agentID
				  << std::setw(5) << std::left << sale
				  << std::setw(9) << std::left << price 
				  << "Invalid Price!" << std::endl;
	} else {
		sales[agentID - 1] += sale;
		values[agentID - 1] += sale * price;
	}
}

/* Pre-condition: The file must be organized in rows, with each record in a separate row from others.
	Also, variable in a record must be separated with one or more spaces. There should not be any 
	empty lines with no record. */
int main() {
	int sales[20];  // records the total sales per agent
	int values[20]; // records the total value per agent
	for (int i = 0; i < 20; i++) {
		sales[i] = 0;
		values[i] = 0;
	}
	std::string line;
	std::ifstream myfile("sales.txt");
	std::cout << std::setw(25) << " " << "Kwantlen Travel Agency\n\n";
	std::cout << "List of invalid entries:\n";
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			interpret(line, sales, values);
		}
	} else {
		std::cout << "Cannot open the file!";
		exit(1);
	}
	double volume = 0;  // total volumes of the sales
	int totalSales = 0; // total sales amount
	
	std::cout << "\n" << std::setw(25) << " " << "Total Sales by Agents\n\n";
	std::cout << std::setw(20) << std::left << "Agent Number" 
			  << std::setw(20) << std::left << "#Sale" 
			  << std::setw(20) << std::left << "Value/Sale"
			  << std::setw(20) << std::left << "Amount" << "\n";
	for (int t = 0; t < 20; t++) {
		double average; // value/sales for a certain agent
		if (sales[t] != 0) {
			average = (double) values[t] / sales[t];
		} else {
		    average = 0;
		}
		totalSales += sales[t];
		volume += values[t];
		std::cout << std::setw(20) << std::left << t + 1
				  << std::setw(20) << std::left << sales[t]
				  << std::setw(20) << std::left << std::fixed 
				  << std::setprecision(2) << average
				  << std::setw(20) << std::left << values[t];
	}
	std::cout << '\n';
	std::cout << std::setw(25) << std::left << "Total Sales" << totalSales << '\n';
	std::cout << std::setw(25) << std::left << "Average Sales Value" 
			  << std::fixed << std::setprecision(2) << volume/totalSales << '\n';
	std::cout << std::setw(25) << std::left << "Total Volume in Sales" << volume << "\n\n\n\n";
	std::cout << "Top 3 Winners of the Sales Campaign\n\n";
	std::cout << std::setw(10) << std::left << "Agent" << std::setw(20) << std::left << "Dollar Volume Sold" << '\n';
	int first = 0; // the index of the agent with the highest value in sales.
	int second = -1; // the index of the agent with the second highest value in sales.
	int third = -1; // the index of the agent with the third highest value in sales.
	// second and third are initialized to -1 in order to avoid being the index
	// of the agent with the highest sales (in that case they will never get changed
	// in the program).
	// find the agent with the highest sales
	for (int j = 0; j < 20; j++) {
		if (values[j] > values[first]) {
			first = j;
		}
	}
	// find the agent with the second highest sales
	for (int j = 0; j < 20; j++) {
		if (second == -1 && j != first) {
			second = j;
		} else if (values[j] > values[second] && j != first) {
			second = j;
		}
	}
	// find the agent with the third highest sales
	for (int j = 0; j < 20; j++) {
		if (third == -1 && j != first && j != second) {
			third = j;
		} else if (values[j] > values[third] && j != first && j != second) {
			third = j;
		}
	}
	std::cout << std::setw(14) << std::left << first + 1 << values[first] << '\n';
	std::cout << std::setw(14) << std::left << second + 1 << values[second] << '\n';
	std::cout << std::setw(14) << std::left << third + 1 << values[third] << '\n' << "\n\n\n";
	
	std::cout << "Agent Whose Sales Were Below $1000\n\n";
	std::cout << std::setw(10) << std::left << "Agent" << std::setw(20) << std::left << "Dollar Volume Sold" << '\n';
	for (int j = 0; j < 20; j++) {
		if (values[j] != 0 && values[j] < 1000) {
			std::cout << std::setw(14) << std::left << j + 1 << values[j] << '\n';
		}
	}
	
	std::cout << "\n\n\nAgents Who Did Not Participate in the Campaign" << std::endl;
	std::cout << "";
	for (int j = 0; j < 20; j++) {
		if (sales[j] == 0) {
			std::cout << j + 1 << "  ";
		}
	}
}

