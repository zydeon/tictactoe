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
		Table(GLfloat width_, GLfloat height_, GLfloat depth_,
				GLfloat feetSize_);
		void drawTable();
		int makeMove(bool playerX, int pos);
	private:
		TTTGraphics *game;
		GLfloat width, height, depth, feetSize;
		GLuint texture;
		RgbImage imag;
		void drawFoot();
		void drawTop();
		void loadTexture();
};
