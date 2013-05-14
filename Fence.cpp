#include "Fence.hpp"

Fence::Fence(GLfloat w_, GLfloat h_, GLfloat d_) {
	w = w_;
	h = h_;
	d = d_;
}


void Fence::drawFence() {
	glColor3f(1.0, 0.0, 1.0);
	
	// Front
	glPushMatrix();
	glScalef(3,3,3);
	glBegin(GL_POLYGON);
		glNormal3f(-0.5, 0.0, 1.0);
		glVertex3f(-0.5, 0.0, 0.0);
		glVertex3f(-0.5,	0.0, 0.0);
		glVertex3f(-0.5, 3, 0.0);
		glVertex3f(0, 4, 0.0);
		glVertex3f(0.5, 3, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
	glEnd();
	
	glPopMatrix();
	
	// Front
	glBegin(GL_POLYGON);
		glNormal3f(-w/2, 0.0, 1.0);
		glVertex3f(-w/2, 0.0, 0.0);
		glVertex3f(-w/2,	0.0, 0.0);
		glVertex3f(-w/2, 3*h/4, 0.0);
		glVertex3f(0, h, 0.0);
		glVertex3f(w/2, 3*h/4, 0.0);
		glVertex3f(w/2, 0.0, 0.0);
	glEnd();
	
	// Right
	/*glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(w,	0.0,	0.0);
		glVertex3f(w,	0.0,	d);
		glVertex3f(w,	3*h/4,	d);
		glVertex3f(w/2,	h,		d);
		glVertex3f(w/2, h,		0.0);
		glVertex3f(w,	3*h/4,	0.0);
		glVertex3f(w,	0.0,	0.0);
	glEnd();*/
	
	// Back
	/*glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, d);
		glVertex3f(w,	0.0, d);
		glVertex3f(w, 3*h/4, d);
		glVertex3f(w/2, h, d);
		glVertex3f(0.0, 3*h/4, d);
		glVertex3f(0.0, 0.0, d);
	glEnd();*/
	
	// Left
	/*glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.0,	0.0,	0.0);
		glVertex3f(0.0,	0.0,	d);
		glVertex3f(0.0,	3*h/4,	d);
		glVertex3f(w/2,	h,		d);
		glVertex3f(w/2, h,		0.0);
		glVertex3f(0.0,	3*h/4,	0.0);
		glVertex3f(0.0,	0.0,	0.0);
	glEnd();*/
	
	// Bottom
	/*glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(w, 0.0, 0.0);
		glVertex3f(w, 0.0, d);
		glVertex3f(0.0, 0.0, d);
	glEnd();*/
	
}
