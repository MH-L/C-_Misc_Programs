#include <iostream>

void initializeBoard(int board[][5]) {
	// initialize all of the entries to 0
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			board[i][j] = 0;
}

bool checkIfWinning(int board[][5], int curLocation) {
	// check if the player is winning based on the last location he/she puts in the peg
	// since what really matters is the last input, this reduces unnecessary work.
	if (curLocation == 0) {
		return false;
	}
	int row = (curLocation - 1) / 5;
	int column = (curLocation - 1) % 5;
	int player = board[row][column];
	int count = 0;
	// the pegs in the same column must be the same in order to win
	for (int i = 0; i < 5; i++) {
		if (board[i][column] != player)
			break;
		count++;
	}
	// count == 5 means the loop "survives", meaning that all the pegs are the same
	// This also holds for other checks.
	if (count == 5)
		return true;
	count = 0;
	// Check the row
	for (int j = 0; j < 5; j++) {
		if (board[row][j] != player) 
			break;
		count++;
	}
	
	if (count == 5)
		return true;
	count = 0;
	// If the new peg is on the main diagonal then check the diagonal
	if (row == column) {
		for (int i = 0; i < 5; i++) {
			if (board[i][i] != player)
				break;
			count ++;
		}
	}
	
	if (count == 5)
		return true;
	count = 0;
	
	if (row + column == 4) {
		for (int i = 0; i < 5; i++) {
			if (board[i][4-i] != player)
				break;
			count ++;
		}
	}
	
	if (count == 5)
		return true;
	
	return false;
}

bool isFull(int board[][5]) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (board[i][j] == 0)
				return false;
				
	return true;
}

void renderBoard(int board[][5]) {
	// Pegs placed by player 1 are denoted by 'O' while
	// those placed by player 2 are denoted by 'X'.
	// Board positions with no pegs are '-'.
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if(board[i][j] == 0) {
				std::cout << '-';
			} else if (board[i][j] == 1) {
				std::cout << 'X';
			} else if (board[i][j] == 2) {
				std::cout << 'O';
			}
		}
		std::cout << '\n';
	}
}
int main() {
	int board[5][5];
	initializeBoard(board);
	std::cout << "Now let us start the game!\n";
	std::cout << "The board locations are as follows:\n";
	std::cout << "1  2  3  4  5\n6  7  8  9  10\n11 12 13 14 15\n16 17 18 19 20\n21 22 23 24 25\n";
	std::cout << "Here is the initial board.\n";
	renderBoard(board);
	bool counter = 0;
	int pegLocation = 0;
	while (!isFull(board)) {
		// counter == false means it is player 1's turn;
		// otherwise it is player 2's turn.
		if (!counter)
			std::cout << "Player 1, please enter the location you want to place the peg." << std::endl;
		else 
			std::cout << "Player 2, please enter the location you want to place the peg." << std::endl;
		std::cin >> pegLocation;
		if (pegLocation > 25 || pegLocation < 0) {
			std::cout << "The location you entered must be between 1 and 25. Please enter again!" << std::endl;
			continue;
		}
		int row = (pegLocation - 1) / 5;
		int column = (pegLocation - 1) % 5;
		// if a board location is occupied by player 1's peg,
		// then that entry is 1, if it is occupied by player
		// 2's peg, it is 2. Empty locations are always zeros.
		if (board[row][column] == 0) 
			if (!counter)
				board[row][column] = 1;
			else
				board[row][column] = 2;
		else {
			std::cout << "The location you entered has been taken. Please re-enter.\n";
			continue;
		}
		std::cout << "And now the board is:\n";
		renderBoard(board);
		// If either player wins then the game is over
		if (checkIfWinning(board, pegLocation))
			break;
		counter = !counter;
	}
	// If the board is not full when the loop finishes, 
	// there must be a winner.
	if (!isFull(board))
		if (!counter) {
			// If the last move is done by the first player
			// then player 1 wins.
			std::cout << "Player 1 wins!";
			return 0;
		} else {
			// If the last move is done by the second player
			// then player 2 wins.
			std::cout << "Player 2 wins!";
			return 0;
		}
		
	std::cout << "The board is full and no players win.";
	return 0;
}
