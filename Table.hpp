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
		GLfloat width, height, depth;
		TTTGraphics *game;
		
		Table(GLfloat width_, GLfloat height_, GLfloat depth_);
		void drawTable();
		int makeMove(bool playerX, int pos);
	private:
		Surface *feetSurface;
		static const GLfloat feetWidth = 0.2f;		// squared
		void drawFoot();
};

#endif
