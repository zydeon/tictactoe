#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <stdio.h>

#define NO_MOVE 0
#define X_MOVE 1
#define O_MOVE 2
#define INVALID_MOVE -1
#define INVALID_TURN -2
#define WIN 3
#define NO_WIN 4
#define OVER 5

#define POSITIONS_NO 9

#define WIN_CASES_NO 8

static int win_cases[WIN_CASES_NO][3] = {{ 0, 1, 2 }, { 3, 4, 5 }, {6, 7, 8 }, {0, 3, 6 },{ 1, 4, 7 },{ 2, 5, 8 },{ 0, 4, 8 },{ 2, 4, 6 }};

class TicTacToe {
	public:
		TicTacToe();
		int play(bool _xTurn, int pos);
		void plotGame();
		bool isXTurn();
		int *getPositions();
	private:
		
		int positions[POSITIONS_NO];
		bool xTurn;
	
		bool isRightTurn(bool _xTurn);
		bool isValidMove(int pos);
		void placeMove(bool _xTurn, int pos);
		bool won(bool _xTurn);
		bool isFull();
		void resetGame();


};

#endif
