#include "Surface.hpp"

Surface::Surface(GLfloat x_, GLfloat y_, int type_) {
	x = x_;
	y = y_;
	type = type_;
	loadTexture();
}

void Surface::drawSurface() {
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_POLYGON);
		glTexCoord2f(reps,0.0f); glVertex3f(x/2, -y/2, 0.0);
		glTexCoord2f(reps,reps); glVertex3f(x/2, y/2, 0.0);
		glTexCoord2f(0.0f,reps); glVertex3f(-x/2, y/2, 0.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-x/2, -y/2, 0.0);
		glTexCoord2f(reps,0.0f); glVertex3f(x/2, -y/2, 0.0);
	glEnd();
}

void Surface::loadTexture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if(type == S_TYPE) {
		imag.LoadBmpFile(SKY_BMP);
		reps = 1.0;
	}
	else if(type == F_TYPE) {
		imag.LoadBmpFile(FLOOR_BMP);
		reps = 4.0;
	}
	else {
		imag.LoadBmpFile(WALLS_BMP);
		reps = 1.0;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}
