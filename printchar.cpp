#include <iostream>


void display(char ch, int side) {
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++)
			std::cout << ch;
		std::cout << "\n";
	}
}


int main() {
	char input;
    int side;
	std::cout << "Enter the char you want to display in the console:" << std::endl;
	std::cin >> input;
	std::cout << "Enter the side length of the square you want to display" << std::endl;
	std::cin >> side;
	display(input, side);
	fflush(stdin);
	getchar();
	return 0;
}
