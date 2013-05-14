#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

class Player {

	public:
		Player();

		GLfloat x;
		GLfloat y;
		// angulos de rotacao com eixos do Y e X (olhar para cima/baixo e lados)
		GLfloat rotX;
		GLfloat rotY;

	private:


};

#endif
