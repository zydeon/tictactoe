
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
		Surface(GLfloat w_, GLfloat h_, int type_);
		void drawSurface(GLfloat nX, GLfloat nY, GLfloat nZ);
	private:
		int type;
		GLfloat h,w,reps;
		GLuint texture;
		RgbImage imag;
		void loadTexture();

		// superficie dividida em quadrados de dimensao 'dim'
		const static GLfloat dim = 0.5f;
};
