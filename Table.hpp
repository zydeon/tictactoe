#ifndef TABLE_HPP
#define TABLE_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "RgbImage.h"
#include "TTTGraphics.hpp"

#define TABLE_BMP "textures/table.bmp"

class Table {
	public:
		GLfloat width, height, depth, feetSize;
		
		Table(GLfloat width_, GLfloat height_, GLfloat depth_,
				GLfloat feetSize_);
		void drawTable();
		int makeMove(bool playerX, int pos);
	private:
		TTTGraphics *game;
		GLuint texture;
		RgbImage imag;
		void drawFoot();
		void drawTop();
		void loadTexture();
};

#endif
