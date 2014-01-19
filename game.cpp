#include <iostream>
#include <sstream>
#include <iomanip>
#include "game.h"

using namespace std;

// init the board to blank
Game::Game() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			board[i][j] = '-';
		}
	}
}

void Game::printBoard() {
	cout << "-------------------";
	for(int i = 0; i < 3; i++) {
		cout << '\n' << "|";
		for(int j = 0; j < 3; j++) {
			cout << setw(3) << board[i][j] << setw(3) << " |";
		}
	}
	cout << '\n' << "-------------------" << '\n';
}

bool Game::gameOver() {
	if(checkWin(HUMAN)) return true;
	else if(checkWin(AI)) return true;

	bool emptySpace = false;
	for(int i = 0; i < 3; i++) {
		if(board[i][0] == '-' || board[i][1] == '-' || board[i][2] == '-')
			emptySpace = true;
	}
	return !emptySpace;
}

bool Game::checkWin(Player player) {
	char playerChar;
	if(player == HUMAN) playerChar = human;
	else playerChar = ai;

	for(int i = 0; i < 3; i++) {
		// Check horizontals
		if(board[i][0] == playerChar && board[i][1] == playerChar
			&& board[i][2] == playerChar)
			return true;

		// Check verticals
		if(board[0][i] == playerChar && board[1][i] == playerChar
			&& board[2][i] == playerChar)
			return true;
	}

	// Check diagonals
	if (board[0][0] == playerChar && board[1][1] == playerChar 
		&& board[2][2] == playerChar) {
		return true;
	} else if (board[0][2] == playerChar && board[1][1] == playerChar 
		&& board[2][0] == playerChar) {
		return true;
	}

	return false;
}

int Game::score() {
	if(checkWin(HUMAN)) { return 10; }
	else if(checkWin(AI)) { return -10; }
	return 0; // draw
}

Move Game::minmax(char AIboard[3][3]) { 
	int bestMoveScore = 100; // -100 is arbitrary
	Move bestMove;

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMoveScore = maxSearch(AIboard);
				if(tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMove;
}

int Game::maxSearch(char AIboard[3][3]) {
	if(gameOver()) return score();
	Move bestMove;

	int bestMoveScore = -1000;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = human;
				int tempMoveScore = minSearch(AIboard);
				if(tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

int Game::minSearch(char AIboard[3][3]) {
	if(gameOver()) return score();

	int bestMoveScore = 1000; 
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(AIboard[i][j] == '-') {
				AIboard[i][j] = ai;
				int tempMove = maxSearch(AIboard);
				if(tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
				}
				AIboard[i][j] = '-';
			}
		}
	}

	return bestMoveScore;
}

void Game::play() {
	int turn = 0;
	printBoard();
	while(!checkWin(HUMAN) && !checkWin(AI) && !gameOver()) {
		// human move
		if(turn % 2 == 0) {
			cout << "Enter your move in coordinate form, ex: (1,3)." << endl;
			cout << "Your Move: ";
			int x, y;
			char c;
			string restofline;
			cin >> c >> c;
			x = c - '0' - 1;
			cin >> c >> c;
			y = c - '0' - 1;
			getline(cin, restofline); // get garbage chars after move
			cout << x << " " << y << endl;
			board[x][y] = human; // NEED TO CHECK THIS
			turn++;
			printBoard();
			if(checkWin(HUMAN)) cout << "p1 wins" << endl;
		} else {
			cout << endl << "Computer Player Move:" << endl;
			Move AImove = minmax(board);
			board[AImove.x][AImove.y] = ai;
			if(checkWin(AI)) cout << "p2 wins" << endl;
			turn++;
			printBoard();
		}
	}
}