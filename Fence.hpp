#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "RgbImage.h"

#define FENCE_BMP "textures/fence1.bmp"

class Fence {
	public:
		Fence(GLfloat w_, GLfloat h_, GLfloat d_);
		void drawFence();
		void drawSmallPiece(GLfloat size);
	private:
		GLfloat w,h,d;
		GLuint texture;
		RgbImage imag;
		void loadTexture();
};
