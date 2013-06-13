#include "Surface.hpp"

Surface::Surface(GLfloat w_, GLfloat h_, char *image, Material m):
					w(w_),
					h(h_),
					material(m)
	{
	loadTexture(image);
}

void Surface::drawSurface(GLfloat nX, GLfloat nY, GLfloat nZ) {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);

	GLint i, j;
	GLfloat W, H; // numero de quadrados unitarios de 'dim'

	i = j = 0;
	glBegin(GL_QUADS);

	W = w / dim;
	H = h / dim;
	for( i = 0; i < H; ++i ){
		for( j = 0; j < W; ++j ){
			glNormal3f(nX, nY, nZ);
			// face visivel sempre a da frente (considerar coordenadas da textura de 0 a 1)
			glTexCoord2f(j/W, i/H); 		glVertex3f(j*dim-w/2, i*dim-h/2, 0.0);
			glTexCoord2f((j+1)/W, i/H); 	glVertex3f((j+1)*dim-w/2, i*dim-h/2, 0.0);
			glTexCoord2f((j+1)/W, (i+1)/H); glVertex3f((j+1)*dim-w/2, (i+1)*dim-h/2, 0.0);
			glTexCoord2f(j/W, (i+1)/H); 	glVertex3f(j*dim-w/2, (i+1)*dim-h/2, 0.0);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Surface::loadTexture(char *im_path) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(im_path);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}
