#include "Surface.hpp"

Surface::Surface(GLfloat w_, GLfloat h_, string image, Material m, GLfloat d):
					w(w_),
					h(h_),
					material(m),
					dim(d)
	{
	loadTexture(image);
}

void Surface::drawSurface() {
	GLint i, j;
	GLfloat W, H; // numero de quadrados unitarios de 'dim'	

	material.apply();
	enableTexture();

	i = j = 0;
	W = w / dim;
	H = h / dim;

	glBegin(GL_QUADS);
	for( i = 0; i < H; ++i ){
		for( j = 0; j < W; ++j ){
			glNormal3f(0, 0, 1);
			// face visivel sempre a da frente (considerar coordenadas da textura de 0 a 1)
			glTexCoord2f(j/W, i/H); 		glVertex3f(j*dim-w/2, i*dim-h/2, 0.0);
			glTexCoord2f((j+1)/W, i/H); 	glVertex3f((j+1)*dim-w/2, i*dim-h/2, 0.0);
			glTexCoord2f((j+1)/W, (i+1)/H); glVertex3f((j+1)*dim-w/2, (i+1)*dim-h/2, 0.0);
			glTexCoord2f(j/W, (i+1)/H); 	glVertex3f(j*dim-w/2, (i+1)*dim-h/2, 0.0);
		}
	}
	glEnd();

	disableTexture();
}

void Surface::enableTexture(){
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D,texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Surface::disableTexture(){
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Surface::loadTexture(string im_path) {
	RgbImage image;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	image.LoadBmpFile(im_path.c_str());
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 3,
				 image.GetNumCols(),
				 image.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 image.ImageData() );
	glBindTexture(GL_TEXTURE_2D, 0); // deactivate
}
