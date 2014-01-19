#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>

using namespace std;

const char human = 'X';
const char ai = 'O';
enum Player { HUMAN, AI };
struct Move {
	int x;
	int y;
};

class Game {
	char board[3][3];

public:
	Game();
	void printBoard();
	bool gameOver();
	bool checkWin(Player player);
	void play();
	int score();
	Move minmax(char AIboard[3][3]);
	int minSearch(char AIboard[3][3]);
	int maxSearch(char AIboard[3][3]);
};

#endif /* __GAME_H__ */