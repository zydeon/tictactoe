
#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "RgbImage.h"
#include "Material.hpp"

#define FLOOR_BMP 	"textures/grass.bmp"
#define WALLS_BMP 	"textures/parede1.bmp"
#define SKY_BMP 	"textures/sky.bmp"

class Surface {
	public:
		Surface(GLfloat w_, GLfloat h_, char * image, Material m);
		void drawSurface(GLfloat nX, GLfloat nY, GLfloat nZ);
	private:
		GLfloat h, w;
		GLuint texture;
		Material material;
		RgbImage imag;
		void loadTexture(char *im_path);

		// superficie dividida em quadrados de dimensao 'dim'
		const static GLfloat dim = 0.5f;
};
