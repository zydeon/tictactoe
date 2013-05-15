#include "Fence.hpp"

Fence::Fence(GLfloat w_, GLfloat h_, GLfloat d_) {
	w = w_;
	h = h_;
	d = d_;
	loadTexture();
}

void Fence::drawFence() {
	glBindTexture(GL_TEXTURE_2D,texture);

	glBegin(GL_POLYGON);
		glTexCoord2f(1.0f,0.0f); glVertex3f(w/2, -h/2, 0.0);
		glTexCoord2f(1.0f,0.75f); glVertex3f(w/2, h/4, 0.0);
		glTexCoord2f(0.5f,1.f); glVertex3f(0, h/2, 0.0);
		glTexCoord2f(0.0f,0.75f); glVertex3f(-w/2, h/4, 0.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2, 0.0);
		glTexCoord2f(1.0f,0.0f); glVertex3f(w/2, -h/2, 0.0);
	glEnd();
	
}

void Fence::drawSmallPiece(GLfloat size) {
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_POLYGON);
		glTexCoord2f(1.0f,0.0f); glVertex3f(size/2, -h/2, 0.0);
		glTexCoord2f(1.0f,0.75f); glVertex3f(size/2, h/4, 0.0);
		glTexCoord2f(0.0f,0.75f); glVertex3f(-size/2, h/4, 0.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-size/2, -h/2, 0.0);
		glTexCoord2f(1.0f,0.0f); glVertex3f(size/2, -h/2, 0.0);
	glEnd();
}

void Fence::loadTexture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(FENCE_BMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}
