
#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "RgbImage.h"
#include "Material.hpp"
#include <string>
using namespace std;


#define FLOOR_BMP 	"textures/grass.bmp"
#define WALLS_BMP 	"textures/parede1.bmp"
#define SKY_BMP 	"textures/sky.bmp"

class Surface {
	public:
		Surface(GLfloat w_, GLfloat h_, string image, Material m);
		void drawSurface(GLfloat nX, GLfloat nY, GLfloat nZ);
	private:
		GLfloat h, w;
		GLuint texture;
		Material material;
		// superficie dividida em quadrados de dimensao 'dim'
		const static GLfloat dim = 0.5f;

		void loadTexture(string im_path);
		void disableTexture();
		void enableTexture();
};
