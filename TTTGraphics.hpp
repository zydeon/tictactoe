#ifndef TTTGRAPHICS_HPP
#define TTTGRAPHICS_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "TicTacToe.hpp"
#include "RgbImage.h"
#include "Surface.hpp"

#define BLUE_BMP "textures/blue.bmp"
#define RED_BMP "textures/red.bmp"

class TTTGraphics {
	public:
		TTTGraphics(GLfloat size_);
		void drawGame();
		int play(bool x, int pos);
		void loadTextures();
		
	private:
		Surface *board;
		GLfloat size;
		TicTacToe *ttt;
		GLuint texture[2];
		RgbImage imag;
		void drawLines();
		void drawPieces();
		void drawX();
		void drawO();
		void drawPiece();
};


#endif
