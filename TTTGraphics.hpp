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

class Piece{
public:
	static const GLfloat incY = 3.0;
	static const GLfloat incX = 3.0;
	GLfloat angY;
	GLfloat angX;

	Piece(){
		angY = rand() % 360;
		angX = rand() % 360;
	}

	void draw(color4 color){
		glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
			glPushMatrix();
				glColor4f(color.values[0],color.values[1],color.values[2],color.values[3]);
				glRotatef(angY, 0, 1, 0);
				glRotatef(angX, 1, 0, 0);
				glutSolidCube(0.2);
				glColor3f(0,0,0);
				glutWireCube(0.23);
			glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
	}

	void update(){
		angY += incY;
		angX += incX;
	}
};

class TTTGraphics {
	public:
		TTTGraphics(GLfloat size_);
		void drawGame();
		int play(bool x, int pos);
		void updatePieces();
		
	private:
		Surface *board;
		Piece pieces[9];

		GLfloat size;
		TicTacToe *ttt;
		GLuint texture[2];
		RgbImage imag;
		void drawLines();
		void drawPieces();
};


#endif
