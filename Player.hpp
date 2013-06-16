#ifndef PLAYER_HPP
#define PLAYER_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "RgbImage.h"

#define SKIN_BMP "textures/skin.bmp"
#define LEG_BMP "textures/leg.bmp"

#define HEAD_BMP "textures/head.bmp"

#define TORSO0_BMP "textures/torso0.bmp"
#define FACE0_BMP "textures/face0.bmp"
#define TORSO1_BMP "textures/torso1.bmp"
#define FACE1_BMP "textures/face1.bmp"

#define HEAD_W 1.0
#define HEAD_H 1.0
#define HEAD_D 0.7

#define NECK_W 0.3
#define NECK_H 0.3

#define TORSO_W 1.0
#define TORSO_H 2.5
#define TORSO_D 0.4

#define SHOULDER_W 0.6
#define SHOULDER_H 0.5
#define ARM_W 0.3
#define ARM_H 1.5
#define HAND_H 0.3

#define LEG_W 0.3
#define LEG_H 2.0

#define FOOT_H 0.2
#define FOOT_D 0.5

class Player {

	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;
		
		// rotation angles with X and Y axes in radians (look up/down and right/left)
		GLfloat angX;
		GLfloat angY;

		static const GLfloat velocity = 0.3;
		// sensitivity of mouse (velocity of rotation)
		static const GLfloat sensitivity = 0.001;


		Player(GLfloat y_);

		// get reference point (where is looking at)
		GLfloat getRefX();
		GLfloat getRefZ();
		GLfloat getRefY();

		void setZ(GLfloat z_);

		void loadTextures(bool x);
		
		void drawPlayer();
	private:
		GLuint skinText,legText,torsoText,armText,neckText,headText,faceText;
		RgbImage imag;
		
		void drawPipe(GLuint text, GLfloat w, GLfloat h, GLfloat z);
		
		void drawFoot();
		void drawLeg();
		void drawTorso();
		void drawArm();
		void drawNeck();
		void drawHead();

};

#endif
