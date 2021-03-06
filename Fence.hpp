#ifndef FENCE_HPP
#define FENCE_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "RgbImage.h"
#include "Surface.hpp"

#define FENCE_BMP "textures/fence1.bmp"

class Fence {
		static const GLfloat unitW = 0.75f;
		static const GLfloat unitH = 2.5f;
		static const GLfloat unitD = 0.3f;
	public:
		GLfloat width;
		GLfloat height;
		Fence(GLint number, GLfloat w, GLfloat h);
		void draw();
	private:
		GLfloat unitNumber;

		// comprimento da extremidade do triangulo de cima
		GLfloat unitCornerH;
		GLfloat unitCornerAng;

		Surface *unit;

		void drawUnit();
		void drawShape();
		void drawSide();
		void drawTexturedShape(char outside);
};


#endif
