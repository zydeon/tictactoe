#include "TicTacToe.hpp"

int TicTacToe::play(bool _xTurn, int pos) {
	bool win;
	
	if(!isRightTurn(_xTurn)) {
		return INVALID_TURN;
	}
	
	if(!isValidMove(pos)) {
		return INVALID_MOVE;
	}
	
	placeMove(_xTurn,pos);
	
	win = won(_xTurn);
	xTurn = !xTurn;
	
	if(win) {
		resetGame();
		return WIN;
	}
	else if(isFull()){
		resetGame();
		return OVER;
	}
	else {
		return NO_WIN;
	}
}

bool TicTacToe::isValidMove(int pos) {
	return !(pos >= POSITIONS_NO || pos < 0 || positions[pos] != NO_MOVE);
}

bool TicTacToe::isRightTurn(bool _xTurn) {
	return _xTurn == xTurn;
}

void TicTacToe::placeMove(bool _xTurn, int pos) {
	positions[pos] = _xTurn ? X_MOVE : O_MOVE;
}

bool TicTacToe::won(bool _xTurn) {
	int i, aux;
	
	aux = _xTurn ? X_MOVE : O_MOVE;
	int a1,a2,a3;
	
	for(i = 0; i < WIN_CASES_NO; i++) {
		a1 = positions[win_cases[i][0]];
		a2 = positions[win_cases[i][1]];
		a3 = positions[win_cases[i][2]];
		if(aux == a1 && aux == a2 && aux == a3) {
			return true;
		}
	}
	
	return false;
}

bool TicTacToe::isFull() {
	int i,count;
	for(i = count = 0; i< POSITIONS_NO; i++) {
		if(positions[i] != NO_MOVE) {
			count ++;
		}
	}
	return count == POSITIONS_NO;
}

void TicTacToe::resetGame() {
	int i;
	for(i = 0; i < POSITIONS_NO; i++) {
		positions[i] = NO_MOVE;
	}
	printf("Game Reset\n");
}

TicTacToe::TicTacToe() {
	int i;
	for(i = 0; i < POSITIONS_NO; i++) {
		positions[i] = NO_MOVE;
	}
	xTurn = true;
}

void TicTacToe::plotGame() {
	int i,j;
	char aux;
	i = 0;
	while(i < POSITIONS_NO) {
		for(j = 0; j < 3; j++) {
			switch(positions[i++]) {
				case NO_MOVE: aux = ' '; break;
				case X_MOVE: aux = 'X'; break;
				case O_MOVE: aux = 'O'; break;
			}
			printf("|%c|",aux);
		}
		printf("\n----------\n");
	}
	printf("\n");
}

bool TicTacToe::isXTurn() {
	return xTurn;
}

int *TicTacToe::getPositions() {
	return positions;
}
