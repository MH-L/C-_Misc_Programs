#include <fstream>
#include <iostream>

void printWord(std::string str, int length) {
	std::cout << str;
	int count = 20 - length;
	while (count > 0) {
		std::cout << " ";
		count --;
	}
	
	std::cout << length << "\n";
}

int analyse(std::string line) {
	std::string curWord = "";
	int count = 0;
	int numWords = 0;
	for(int i = 0; i < line.length(); i++) {
		if (line[i] != ' ') {
			curWord += line[i];
			count++;
		}
		else {
			if (curWord.length() != 0) {
				printWord(curWord, count);
				numWords ++;
			}
			curWord = "";
			count = 0;
		}
	}
	if (curWord.length() != 0) {
		printWord(curWord, count);
		numWords ++;
	}
	return numWords;
}

int main() {
	std::ifstream fin("data.txt");
	std::string curLine;
	int total = 0;
	while (!fin.eof()) {
		getline(fin, curLine);
		total += analyse(curLine);
	}
	
	std::cout << "\nThe total number of words is " << total << "\n";;
	
	return 0;
}
