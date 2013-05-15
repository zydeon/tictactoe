#ifndef TICTACTOEGL_HPP
#define TICTACTOEGL_HPP

#include "Fence.hpp"
#include "Surface.hpp"
#include <math.h>


#define PI 3.14

#define RED   	 1.0, 0.0, 0.0, 1.0
#define GREEN 	 0.0, 1.0, 0.0, 1.0
#define BLUE   	 0.0, 0.0, 1.0, 1.0
#define YELLOW   1.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK	 0.0, 0.0, 0.0, 1.0

#define SQUARESIZE 20.0

#define FENCE_W 0.75
#define FENCE_H 7.5
#define FENCE_D 0.5

double toRad(double);

class TicTacToeGL{
	public:
		static const int XSCREEN = 800;
		static const int YSCREEN = 600;

		static const int XWORLD = 75;
		static const int YWORLD = 40;
		static const int ZWORLD = 75;

		static void initControls();
		// calbacks (need to be static)
		static void inputMouseCb(int x, int y);
		static void inputKeyboardCb(unsigned char key, int x, int y);
		static void inputSpecialCb(int key, int x, int y);
		static void display();

		TicTacToeGL(int, char**);
		static void init();
	private:
		static void draw();
		static void drawAxis();
		static void drawFence();
		static void drawFloor();
		static void drawWalls();
		static void drawSky();

};

#endif
