#ifndef TICTACTOEGL_HPP
#define TICTACTOEGL_HPP

#include "Player.hpp"

#define RED   	 1.0, 0.0, 0.0, 1.0
#define GREEN 	 0.0, 1.0, 0.0, 1.0
#define BLUE   	 0.0, 0.0, 1.0, 1.0
#define YELLOW   1.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0

#define PI    3.14159265359

class TicTacToeGL{
	// all members must be static because callback functions must be static
	// is this class useless ?

	public:
		static const int XSCREEN = 600;
		static const int YSCREEN = 400;

		static const int XWORLD = 20;
		static const int YWORLD = 20;
		static const int ZWORLD = 20;

		static void initControls();
		// calbacks (need to be static)
		static void inputMouseCb(int x, int y);
		static void inputKeyboardCb(unsigned char key, int x, int y);
		static void inputSpecialCb(int key, int x, int y);
		static void display();


		TicTacToeGL(int, char**);

	private:
		// static members must be "redefined" and initialized outside
		static Player p1;
		static Player p2;

		static Player *currPlayer; // pointer to current player

		static int mouseX;
		static int mouseY;

		static void draw();
		static void init();

};

#endif
