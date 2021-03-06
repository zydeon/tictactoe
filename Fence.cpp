#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include <math.h>
#include "Fence.hpp"
#include "project.hpp"

Fence::Fence(GLint number, GLfloat w, GLfloat h) {
	unitNumber = number;
	unit = new Surface(FENCE_BMP, Material(), 0.05f);
	width = w;
	height = h;

	unitCornerH = sqrt((unitH/4)*(unitH/4)+(unitW/2)*(unitW/2));
	unitCornerAng = toDeg( atan( (unitW/2)/(unitH/4)) );
}

void Fence::draw() {
	int i;
	glPushMatrix();
		glTranslatef(-width/2, unitH/2, -height/2);
		// front
		drawSide();
		glRotatef(-90,0,1,0);
		//right
		drawSide();
		glRotatef(-90,0,1,0);
		// back
		drawSide();
		glRotatef(-90,0,1,0);
		// left
		drawSide();

	glPopMatrix();
}

void Fence::drawSide(){
	GLint i;
	// adjust corner
	glTranslatef(unitW/2, 0, unitW/2);

	for( i = 0; i < unitNumber; ++i ){
		drawUnit();
		glTranslatef(unitW, 0, 0);
	}
}

void Fence::drawUnit(){
	// front
	drawTexturedShape(0);
	//back
	glTranslatef(0, 0, -1*unitD/2);
	drawTexturedShape(1);
	glTranslatef(0, 0, unitD/2);

	// Top left
	glPushMatrix();
		glTranslatef(-1*unitW/4, unitH/4+unitH/8, -1*unitD/2);
		glRotatef(-90, 0,1,0);
		glRotatef(-unitCornerAng , 1,0,0);
		unit->draw(unitD, unitCornerH );
	glPopMatrix();
	// Top right
	glPushMatrix();
		glTranslatef(unitW/4, unitH/4+unitH/8, -1*unitD/2);
		glRotatef(90, 0,1,0);
		glRotatef(-unitCornerAng, 1,0,0);
		unit->draw(unitD, unitCornerH );
	glPopMatrix();	
}

void Fence::drawTexturedShape(char outside){
	// use stencil
	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	glColorMask(0, 0, 0, 0);
	glDisable(GL_DEPTH_TEST);

	// definir molde
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 1);
	drawShape();

	glColorMask(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_EQUAL, 1, 1);	

	if(outside)	unit->drawOutside(unitW, unitH);
	else		unit->draw(unitW, unitH);

	glDisable(GL_STENCIL_TEST);
}
void Fence::drawShape(){
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
		glVertex3f(unitW/2, -1*unitH/2, 0);
		glVertex3f(unitW/2, unitH/4, 0);
		glVertex3f(0, unitH/2, 0);
		glVertex3f(-1*unitW/2, unitH/4, 0);
		glVertex3f(-1*unitW/2, -1*unitH/2, 0);
	glEnd();	
	glEnable(GL_LIGHTING);
}
