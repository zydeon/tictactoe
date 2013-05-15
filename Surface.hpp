
#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "RgbImage.h"

#define FLOOR_BMP "textures/grass.bmp"
#define WALLS_BMP "textures/parede1.bmp"
#define SKY_BMP "textures/sky.bmp"

#define F_TYPE 0
#define S_TYPE 1
#define W_TYPE 2

class Surface {
	public:
		Surface(GLfloat x_, GLfloat y_, int type_);
		void drawSurface();
	private:
		int type;
		GLfloat y,x,reps;
		GLuint texture;
		RgbImage imag;
		void loadTexture();
};
