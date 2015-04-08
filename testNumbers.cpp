#include <iostream>
#include <cmath>

int testMultiples(int testNumber) {
	if (testNumber % 7 == 0 || 
	    testNumber % 11 == 0 ||
		testNumber % 13 == 0) {
			return 1;
		}
	else
		return 0;
}

int sumDigitParity(int number) {
	int test = number;
	int sum = 0;
	int currentDigit;
	while (test != 0) {
		currentDigit = test - (test / 10) * 10;
		sum += currentDigit;
		test /= 10;
	}
	return sum % 2 == 0;
}

double sqrtValue(int num) {
	if (num >= 0) {
		return sqrt(num);
	}
	else 
	    return -1;
}

int isPrime(int num) {
	for (int i = 2; i < num; i ++) {
		if (num % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int testNum;
	int begin = 1;
	while (begin != 0) {
		std::cout << "Please enter the number you want the program to test:\n";
		std::cin >> testNum;
		std::cout << "Is the number a multiple of 7, 11 or 13? "; 
		std::string multiple =  testMultiples(testNum) ? "true" : "false";
		std::cout << multiple << std::endl;
		std::cout << "The sum of digits is: "; 
		std::string parity = sumDigitParity(testNum) ? "even" : "odd";
		std::cout << parity << std::endl;
		std::cout << "The square root of the number is: ";
		if (sqrtValue(testNum) == -1) {
			std::cout << "The number you entered is a negative number"
			          << ", so it does not have a square root." << std::endl;
		} else 
			std::cout << sqrtValue(testNum) << std::endl;
		std::cout << "Is it a prime number? "; 
		std::string prime = isPrime(testNum) ? "true" : "false";
		std::cout << prime << std::endl;
		std::cout << "Enter 0 if you want to terminate, other number to run again." << std::endl;
		std::cin >> begin;
	}
	fflush(stdin);
	getchar();
	return 0;
}
