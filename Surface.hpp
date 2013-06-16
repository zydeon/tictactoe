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


#define FLOOR_BMP 			"textures/grass.bmp"
#define SKY_BMP 			"textures/sky.bmp"
#define GLASS_BMP 			"textures/glass.bmp"
#define WALLS_RIGHT_BMP 	"textures/night-sky/right.bmp"
#define WALLS_LEFT_BMP 		"textures/night-sky/left.bmp"
#define WALLS_FRONT_BMP		"textures/night-sky/front.bmp"
#define WALLS_BACK_BMP 		"textures/night-sky/back.bmp"
#define WALLS_TOP_BMP 		"textures/night-sky/top.bmp"
#define WALL 				"textures/parede2.bmp"
#define TABLE_BMP			"textures/table.bmp"

class Surface {
	public:
		Surface(GLfloat w_, GLfloat h_, string image, Material m, GLfloat d=0.5f);  // with texture
		void drawSurface(GLint textureParam = GL_MODULATE);
	private:
		GLfloat h, w;
		GLuint texture;
		Material material;
		// superficie dividida em quadrados de dimensao 'dim'
		GLfloat dim;

		void loadTexture(string im_path);
		void disableTexture();
		void enableTexture(GLint param);
};


#endif
