#include "TicTacToe.hpp"

TicTacToe t;

void handleResult(int);

int main() {
	char aux;
	int pos;
	bool x;
	
	while(true) {
		scanf("%c %d",&aux,&pos);
		if(aux == 'x' || aux == 'X' || aux == 'o' || aux == 'O') {
			x = (aux == 'x' || aux == 'X');
			handleResult(t.play(x,pos));
		}
	}
	return 0;
}

void handleResult(int result) {
	bool xTurn;
	
	switch(result) {
		case INVALID_MOVE: printf("Invalid Move\n"); break;
		case INVALID_TURN: printf("Invalid Turn\n"); break;
		case WIN: {
			xTurn = !t.isXTurn();
			printf("%c won the game\n", xTurn ? 'X' : 'O');
		} break;
		case NO_WIN: printf("Normal Accepted Move\n"); break;
		case OVER: printf("Draw\n"); break;
	}
	
	t.plotGame();
}
