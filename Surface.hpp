#ifndef SURFACE_HPP
#define SURFACE_HPP


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
#define GLASS_BMP 	"textures/glass.bmp"

class Surface {
	public:
		Surface(GLfloat w_, GLfloat h_, string image, Material m, GLfloat d=0.5f);  // with texture
		void drawSurface();
	private:
		GLfloat h, w;
		GLuint texture;
		Material material;
		// superficie dividida em quadrados de dimensao 'dim'
		GLfloat dim;

		void loadTexture(string im_path);
		void disableTexture();
		void enableTexture();
};


#endif
