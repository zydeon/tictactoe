#include "Table.hpp"

Table::Table(GLfloat width_, GLfloat height_, GLfloat depth_,
		GLfloat feetSize_) {
	width = width_;
	height = height_;
	depth = depth_;
	feetSize = feetSize_;
	loadTexture();
	game = new TTTGraphics(width_);
}

void Table::drawTable() {
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(width/2-feetSize/2, 0 ,(depth/2-feetSize/2));
		drawFoot();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(width/2-feetSize/2, 0,-(depth/2-feetSize/2));
		drawFoot();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-(width/2-feetSize/2), 0, depth/2-feetSize/2);
		drawFoot();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-(width/2-feetSize/2),0,-(depth/2-feetSize/2));
		drawFoot();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,height/2,0);
		drawTop();
		glPushMatrix();
			glTranslatef(0.0,0.11,0.0);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			game->drawGame();
		glPopMatrix();
	glPopMatrix();
}

void Table::drawTop() {
	GLfloat topHeight = feetSize;
	glBindTexture(GL_TEXTURE_2D,texture);
	// Front
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, -topHeight/2,depth/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( width/2,  topHeight/2,depth/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width/2,  topHeight/2,depth/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width/2, -topHeight/2,depth/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, -topHeight/2,depth/2);
	glEnd();
	
	// Right
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, -topHeight/2,-depth/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( width/2,  topHeight/2,-depth/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( width/2,  topHeight/2, depth/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( width/2, -topHeight/2, depth/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, -topHeight/2,-depth/2);
	glEnd();
	
	// Back
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width/2, -topHeight/2,-depth/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width/2,  topHeight/2,-depth/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( width/2,  topHeight/2,-depth/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( width/2, -topHeight/2,-depth/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width/2, -topHeight/2,-depth/2);
	glEnd();
	
	// Left
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width/2, -topHeight/2, depth/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-width/2,  topHeight/2, depth/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width/2,  topHeight/2,-depth/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width/2, -topHeight/2,-depth/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-width/2, -topHeight/2, depth/2);
	glEnd();
	
	// Top
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, topHeight/2, depth/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( width/2, topHeight/2,-depth/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width/2, topHeight/2,-depth/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width/2, topHeight/2, depth/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, topHeight/2, depth/2);
	glEnd();
	
	// Bottom
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, -topHeight/2,-depth/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( width/2, -topHeight/2, depth/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-width/2, -topHeight/2, depth/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-width/2, -topHeight/2,-depth/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( width/2, -topHeight/2,-depth/2);
	glEnd();
}

void Table::drawFoot() {
	GLfloat footHeight = height-feetSize;
	glBindTexture(GL_TEXTURE_2D,texture);
	// Front
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2,feetSize/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( feetSize/2,  footHeight/2,feetSize/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-feetSize/2,  footHeight/2,feetSize/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-feetSize/2, -footHeight/2,feetSize/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2,feetSize/2);
	glEnd();
	
	// Right
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2,-feetSize/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( feetSize/2,  footHeight/2,-feetSize/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( feetSize/2,  footHeight/2, feetSize/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2, feetSize/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2,-feetSize/2);
	glEnd();
	
	// Back
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-feetSize/2, -footHeight/2,-feetSize/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-feetSize/2,  footHeight/2,-feetSize/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( feetSize/2,  footHeight/2,-feetSize/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2,-feetSize/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-feetSize/2, -footHeight/2,-feetSize/2);
	glEnd();
	
	// Left
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-feetSize/2, -footHeight/2, feetSize/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-feetSize/2,  footHeight/2, feetSize/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-feetSize/2,  footHeight/2,-feetSize/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-feetSize/2, -footHeight/2,-feetSize/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-feetSize/2, -footHeight/2, feetSize/2);
	glEnd();
	
	// Top
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, footHeight/2, feetSize/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( feetSize/2, footHeight/2,-feetSize/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-feetSize/2, footHeight/2,-feetSize/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-feetSize/2, footHeight/2, feetSize/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, footHeight/2, feetSize/2);
	glEnd();
	
	// Bottom
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2,-feetSize/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( feetSize/2, -footHeight/2, feetSize/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-feetSize/2, -footHeight/2, feetSize/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-feetSize/2, -footHeight/2,-feetSize/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( feetSize/2, -footHeight/2,-feetSize/2);
	glEnd();
}

int Table::makeMove(bool playerX, int pos) {
	return game->play(playerX,pos);
}

void Table::loadTexture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(TABLE_BMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}
