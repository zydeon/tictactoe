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
		GLfloat x;
		GLfloat y;
		GLfloat z;
		// rotation angles with X and Y axes (look up/down and right/left)
		GLfloat angX;
		GLfloat angY;

		static const GLfloat velocity = 0.3;
		// sensitivity of mouse (velocity of rotation)
		static const GLfloat sensitivity = 0.001;


		Player();

		// get reference point (where is looking at)
		GLfloat getRefX();
		GLfloat getRefZ();


	private:


};

#endif
