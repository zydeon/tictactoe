#ifdef __linux__
	#define VERSION 0
#elif defined __APPLE__
	#define VERSION 1
#else
	#define VERSION 2
#endif

#include "TicTacToe.hpp"

TicTacToe t;

void handleResult(int);


/*int main() {
	char aux;
	int pos;
	bool x;
	int y = VERSION;
	printf("Version = %d\n",y);
	
	while(true) {
		scanf("%c %d",&aux,&pos);
		if(aux == 'x' || aux == 'X' || aux == 'o' || aux == 'O') {
			x = (aux == 'x' || aux == 'X');
			handleResult(t.play(x,pos));
		}
	}
	return 0;
}*/

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
