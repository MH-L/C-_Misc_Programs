#include <fstream> // for reading input from a file
#include <iostream> // for std::cout 
#include <iomanip> // for std::setw and std::left

int sortAndPrint(std::string line);
bool compareWords(std::string firstWord, std::string secondWord);
int main() {
	int numInOrder = 0;
	int lineCount = 0;
	std::string line;
	std::ifstream myFile("openFile.txt");
	if (myFile.is_open()) {
		while (getline(myFile, line)) {
			numInOrder += sortAndPrint(line);
			lineCount ++;
		}
	} else 
		std::cout << "Cannot open the file." << std::endl;
	std::cout << "Number of Cards: " << lineCount << std::endl;
	std::cout << "Number in Order: " << numInOrder << std::endl;
	return 0;
	
}

int sortWords(std::string strings[]) {
	// return 0 if not in order, return 1 if in order.
	std::string temp;
	int count = 0; // record the number of times the loop has run
	while (1) {
		// recursively sort the array of string using improved bubble sort
		// the loop only terminates when the array is already sorted
		if (compareWords(strings[1], strings[0])) {
			// swap the two words since they are not in order
			temp = strings[0];
			strings[0] = strings[1];
			strings[1] = temp;
		} else if (compareWords(strings[2], strings[1])) {
			// swap the two words since they are not in order
			temp = strings[1];
			strings[1] = strings[2];
			strings[2] = temp;
		} else if (compareWords(strings[3], strings[2])) {
			// swap the two words since they are not in order
			temp = strings[2];
			strings[2] = strings[3];
			strings[3] = temp;
		} else {
			// array already sorted so falls into this case
			// return 1 if in order and 0 otherwise
			if (count == 0) {
				return 1;
			} else {
				return 0;
			}
		}
		count ++;
	}
}

bool compareWords(std::string firstWord, std::string secondWord) {
	// if the firstWord has precedence over the second then return true;
	// return false otherwise.
	int counter = 0;
	while (counter < firstWord.length() && counter < secondWord.length()) {
		if (firstWord[counter] < secondWord[counter]) {
			return true;
		} else if (firstWord[counter] > secondWord[counter]) {
			return false;
		} else {
			counter ++;
			continue;
		}
		counter++;
	}
	// If all characters are the same, then compare the lengths of the two strings.
	// The one with shorter length has higher precedence.
	if (firstWord.length() <= secondWord.length()) {
		return true;
	} else 
		return false;
}

int sortAndPrint(std::string line) {
	int section = 0;
	std::string buffer = "";
	std::string words[4];
	char prevChar = ' ';
	int inOrder = 0;
	// Extract words from the input file. Use space to separate words.
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ') {
			if (prevChar != ' ') {
				if (section == 0) {
					words[0] = buffer;
				} else if (section == 1) {
					words[1] = buffer;
				} else if (section == 2) {
					words[2] = buffer;
				} else 
					words[3] = buffer;
				section ++;
				buffer="";
			}
		} else {
			buffer += line[i];
			prevChar = line[i];
		}
	}
	
	if (buffer.length() != 0) {
		words[3] = buffer;
	}
	
	inOrder += sortWords(words);
	
	for (int i = 0; i < 4; i++) {
		std::cout << std::setw(9) << std::left << words[i];
	}
	std::cout << "\n";
	
	return inOrder;
}
