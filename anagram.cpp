#include <iostream>
int main() {
	std::string firstWord;
	std::string secondWord;
	std::cout << "Enter two Words:" << std::endl;
	std::cout << "Now enter the first word:" << std::endl;
	std::cin >> firstWord;
	std::cout << "Now enter the second: " << std::endl;
	std::cin >> secondWord;
	if (firstWord.length() != secondWord.length()) {
		std::cout << "The words you entered are not anagrams." << std::endl;
		return 0;
	}
	
	for (int i = 0; i < firstWord.length(); i++) {
		if (firstWord[i] != secondWord[secondWord.length() - 1 - i]) {
			std::cout << "The words you entered are not anagrams." << std::endl;
			return 0;
		}
	}
	
	std::cout << "The words you entered are anagrams." << std::endl;
	return 0;
	
}
