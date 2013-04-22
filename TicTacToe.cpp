#import "TicTacToe.hpp"

TicTacToe::TicTacToe() {
	int i;
	for(i = 0; i < POSITIONS_NO; i++) {
		positions[i] = NO_MOVE;
	}
	xTurn = true;
}

int TicTacToe::play(bool _xTurn, int pos) {
	if(!isRightTurn(_xTurn)) {
		return INVALID_TURN;
	}
	
	if(!isValidMove(pos)) {
		return INVALID_MOVE;
	}
	
	placeMove(_xTurn,pos);
	
	return won(_xTurn) ? WIN : NO_WIN;
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
	
	for(i = 0; i < WIN_CASES_NO; i++) {
		if(aux == WIN_CASES[i][0] && aux == WIN_CASES[i][1] 
				&& aux == WIN_CASES[i][2]) {
			return true;
		}
	}
	
	return false;
}
