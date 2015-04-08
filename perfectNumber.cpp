#include <iostream>

int IsFactor(int number, int divisor) {
	if (number % divisor == 0)
		return 1;
	else
		return 0;
}

void printFactor(int number) {
	for (int i = 1; i < number; i++) {
		if (IsFactor(number, i)) {
			std::cout << i << " ";
		}
	}
}

int PERFECT(int N) {
	int sumOfFactors = 0;
	for (int i = 1; i < N; i++) {
		if (IsFactor(N, i))
			sumOfFactors += i;
	}
	if (sumOfFactors == N)
		return 1;
	else
		return 0;
}

int main() {
	std::cout << "Here is all perfect numbers from "
			  << "1 to 1000.\n";
	for (int i = 1; i < 1001; i++) {
		if (PERFECT(i)) {
			std::cout << "Perfect number: " << i << std::endl;
			std::cout << "And its factor is: ";
			printFactor(i);
			std::cout << "\n";
		}
	}
	
	int N;
	std::cout << "\nNow, please enter the number you "
	          << "want the program to test, and the program "
	          << "will test numbers from 1 up to that number"
	          << std::endl;
    std::cin >> N;
    
    for (int j = 1; j < N + 1; j++) {
    	if (PERFECT(j)) {
			std::cout << "Perfect number: " << j << std::endl;
			std::cout << "And its factor is: ";
			printFactor(j);
			std::cout << "\n";
		}
	}
	fflush(stdin);
	getchar();
	return 0;
}
