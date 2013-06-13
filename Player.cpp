#include "Player.hpp"
#include <math.h>

Player::Player(GLfloat y_){
	this->x = 0.0;
	this->y = y_;
	this->z = 0.0;

	this->angX = 0.0;
	this->angY = 0.0;
}

void Player::drawPlayer() {
	glPushMatrix();
		drawTorso();
		
		glPushMatrix();
			glTranslatef(0.0, TORSO_H/2+NECK_H/2, 0.0);
			drawNeck();
			glTranslatef(0.0, NECK_H/2+HEAD_H/2, 0.0);
			drawHead();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-TORSO_W/2-SHOULDER_W/2, TORSO_H/2-SHOULDER_H/2, 0.0);
			drawArm();
		glPopMatrix();
		
		
		glPushMatrix();
			glTranslatef(TORSO_W/2+SHOULDER_W/2, TORSO_H/2-SHOULDER_H/2, 0.0);
			glScalef(-1.0, 1.0, 1.0);
			drawArm();
		glPopMatrix();
		
		glTranslatef(0.0, -TORSO_H/2-LEG_H/2, 0.0);
		glPushMatrix();
			glTranslatef(-TORSO_W/2+LEG_W/2, 0.0, 0.0);
			drawLeg();
			glTranslatef(0.0, -LEG_H/2-FOOT_H/2, -TORSO_D/2+FOOT_D/2);
			drawFoot();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(TORSO_W/2-LEG_W/2, 0.0, 0.0);
			drawLeg();
			glTranslatef(0.0, -LEG_H/2-FOOT_H/2, -TORSO_D/2+FOOT_D/2);
			drawFoot();
		glPopMatrix();
	glPopMatrix();
}

void Player::drawFoot() {
	drawPipe(skinText,LEG_W, FOOT_H, FOOT_D);
}

void Player::drawLeg() {
	drawPipe(legText, LEG_W, LEG_H, TORSO_D);
}

void Player::drawTorso() {
	drawPipe(torsoText, TORSO_W, TORSO_H, TORSO_D);
}

void Player::drawArm() {
	glPushMatrix();
	drawPipe(torsoText,SHOULDER_W, SHOULDER_H, TORSO_D);
	glTranslatef(-SHOULDER_W/2+ARM_W/2, -SHOULDER_H/2-ARM_H/2, 0.0);
	drawPipe(torsoText, ARM_W, ARM_H, TORSO_D);
	glTranslatef(0.0, -ARM_H/2-HAND_H/2, 0.0);
	drawPipe(skinText, HAND_H, HAND_H, TORSO_D);
	glPopMatrix();
}

void Player::drawNeck() {
	drawPipe(skinText, NECK_W, NECK_H, TORSO_D);
}

void Player::drawHead() {
	GLfloat w = HEAD_W;
	GLfloat h = HEAD_H;
	GLfloat z = HEAD_D;
	
	glBindTexture(GL_TEXTURE_2D,faceText);
	// Front
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2,  h/2,z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2,  h/2,z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,z/2);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,headText);
	// Right
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( w/2,  h/2, z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( w/2, -h/2, z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	glEnd();
	
	// Back
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
	glEnd();
	
	// Left
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2, z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-w/2,  h/2, z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2, z/2);
	glEnd();
	
	// Top
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, h/2, z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2, h/2,-z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2, h/2,-z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, h/2, z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, h/2, z/2);
	glEnd();
	
	// Bottom
	glBindTexture(GL_TEXTURE_2D,skinText);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2, -h/2, z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2, -h/2, z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	glEnd();
}

void Player::drawPipe(GLuint text, GLfloat w, GLfloat h, GLfloat z) {
	glBindTexture(GL_TEXTURE_2D,text);
	
	// Front
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2,  h/2,z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2,  h/2,z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,z/2);
	glEnd();
	
	// Right
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( w/2,  h/2, z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( w/2, -h/2, z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	glEnd();
	
	// Back
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f( w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
	glEnd();
	
	// Left
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2, z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f(-w/2,  h/2, z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2,  h/2,-z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2, z/2);
	glEnd();
	
	// Top
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, h/2, z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2, h/2,-z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2, h/2,-z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, h/2, z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, h/2, z/2);
	glEnd();
	
	// Bottom
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,1.0f); glVertex3f( w/2, -h/2, z/2);
		glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2, -h/2, z/2);
		glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
		glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	glEnd();
}


void Player::loadTextures(bool x) {
	glGenTextures(1, &skinText);
	glBindTexture(GL_TEXTURE_2D, skinText);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(SKIN_BMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
		
	glGenTextures(1, &legText);
	glBindTexture(GL_TEXTURE_2D, legText);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(LEG_BMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
		
	glGenTextures(1, &torsoText);
	glBindTexture(GL_TEXTURE_2D, torsoText);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if(x) {
		imag.LoadBmpFile(TORSO0_BMP);
	}
	else {
		imag.LoadBmpFile(TORSO1_BMP);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
		
	glGenTextures(1, &headText);
	glBindTexture(GL_TEXTURE_2D, headText);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(HEAD_BMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
		
	glGenTextures(1, &faceText);
	glBindTexture(GL_TEXTURE_2D, faceText);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if(x) {
		imag.LoadBmpFile(FACE0_BMP);
	}
	else {
		imag.LoadBmpFile(FACE1_BMP);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}

void Player::setZ(GLfloat z_) {
	z = z_;
}

GLfloat Player::getRefX(){
	return this->x + sin(angY) * 0.01f;
}
GLfloat Player::getRefZ(){
	return this->z - cos(angY) * 0.01f;
}
GLfloat Player::getRefY(){
	return this->y + sin(angX) * 0.01f;
}
