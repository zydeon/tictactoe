#include "Player.hpp"
#include <math.h>

Player::Player(GLfloat y_, char player){
	this->x = 0.0;
	this->y = y_;
	this->z = 0.0;

	this->angX = 0.0;
	this->angY = 0.0;

	if(player){
		face = new Surface(FACE1_BMP, Material(), 0.1f);
		torso = new Surface(TORSO0_BMP, Material(), 0.1f);		
	}
	else{
		face = new Surface(FACE0_BMP, Material(), 0.1f);
		torso = new Surface(TORSO1_BMP, Material(), 0.1f);		
	}
	skin = new Surface(SKIN_BMP, Material(), 0.1f);
	head = new Surface(HEAD_BMP, Material(), 0.1f);
	leg = new Surface(LEG_BMP, Material(), 0.1f);

}

void Player::drawPlayer() {
	// centrar posicao da camara com cabeca do jogador
	glTranslatef(0, -(HEAD_H/2+NECK_H+TORSO_H/2), 0);
	drawTorso();
	
	glPushMatrix();
		glTranslatef(0.0, TORSO_H/2+NECK_H/2, 0.0);
		drawNeck();
		glTranslatef(0.0, NECK_H/2+HEAD_H/2, 0.0);
		drawHead();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-TORSO_W/2-SHOULDER_W/2, TORSO_H/2-SHOULDER_H/2, 0.0);
		glScalef(1.0, -1.0, 1.0);
		drawArm();
	glPopMatrix();
	
	
	glPushMatrix();
		glTranslatef(TORSO_W/2+SHOULDER_W/2, TORSO_H/2-SHOULDER_H/2, 0.0);
		glScalef(-1.0, -1.0, 1.0);
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

	glTranslatef(0, HEAD_H/2+NECK_H+TORSO_H/2, 0);
}

void Player::drawFoot() {
	drawPipe(skin,LEG_W, FOOT_H, FOOT_D);
}

void Player::drawLeg() {
	drawPipe(leg, LEG_W, LEG_H, TORSO_D);
}

void Player::drawTorso() {
	drawPipe(torso, TORSO_W, TORSO_H, TORSO_D);
}

void Player::drawArm() {
	glPushMatrix();
		drawPipe(torso,SHOULDER_W, SHOULDER_H, TORSO_D);
		glTranslatef(-SHOULDER_W/2+ARM_W/2, -SHOULDER_H/2-ARM_H/2, 0.0);
		drawPipe(torso, ARM_W, ARM_H, TORSO_D);
		glTranslatef(0.0, -ARM_H/2-HAND_H/2, 0.0);
		drawPipe(skin, HAND_H, HAND_H, TORSO_D);
	glPopMatrix();
}

void Player::drawNeck() {
	drawPipe(skin, NECK_W, NECK_H, TORSO_D);
}

void Player::drawHead() {
	// Front
	glPushMatrix();
		glTranslatef(0, 0, HEAD_D/2);
		face->drawOutside(HEAD_W, HEAD_H);
	glPopMatrix();
	// Back
	glPushMatrix();
		glTranslatef(0, 0, -HEAD_D/2);
		head->drawOutside(HEAD_W, HEAD_H);
	glPopMatrix();	

	// Right
	glPushMatrix();
		glRotatef(-90, 0,1,0);
		glTranslatef(0, 0, -HEAD_W/2);
		head->drawOutside(HEAD_D, HEAD_H);
	glPopMatrix();
	// Left
	glPushMatrix();
		glRotatef(90, 0,1,0);
		glTranslatef(0, 0, -HEAD_W/2);
		head->drawOutside(HEAD_D, HEAD_H);
	glPopMatrix();	

	// Top
	glPushMatrix();
		glRotatef(90, 1,0,0);
		glTranslatef(0, 0, -HEAD_H/2);
		head->drawOutside(HEAD_W, HEAD_D);
	glPopMatrix();	
	// Bottom
	glPushMatrix();
		glRotatef(-90, 1,0,0);
		glTranslatef(0, 0, -HEAD_H/2);
		skin->drawOutside(HEAD_W, HEAD_D);
	glPopMatrix();	
}

void Player::drawPipe(Surface *surface, GLfloat w, GLfloat h, GLfloat z) {
	// default model view matrix position is always at the center
	glPushMatrix();
		// back
		glPushMatrix();
			glTranslatef(0, 0, -z/2);
			surface->drawOutside(w, h);
		glPopMatrix();
		// front
		glPushMatrix();
			glRotatef(180, 0,1,0);
			glTranslatef(0, 0, -z/2);
			surface->drawOutside(w, h);
		glPopMatrix();

		// right
		glPushMatrix();
			glRotatef(-90, 0,1,0);
			glTranslatef(0, 0, -w/2);
			surface->drawOutside(z, h);
		glPopMatrix();
		// left
		glPushMatrix();
			glRotatef(90, 0,1,0);
			glTranslatef(0, 0, -w/2);
			surface->drawOutside(z, h);
		glPopMatrix();

		// top
		glPushMatrix();
			glRotatef(90, 1,0,0);
			glTranslatef(0, 0, -h/2);
			surface->drawOutside(w, z);
		glPopMatrix();
		// bottom
		glPushMatrix();
			glRotatef(-90, 1,0,0);
			glTranslatef(0, 0, -h/2);
			surface->drawOutside(w, z);
		glPopMatrix();

	glPopMatrix();

	// glBindTexture(GL_TEXTURE_2D,text);
	
	// // Front
	// glBegin(GL_QUADS);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,z/2);
	// 	glTexCoord2f(1.0f,1.0f); glVertex3f( w/2,  h/2,z/2);
	// 	glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2,  h/2,z/2);
	// 	glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,z/2);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,z/2);
	// glEnd();
	
	// // Right
	// glBegin(GL_QUADS);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	// 	glTexCoord2f(1.0f,1.0f); glVertex3f( w/2,  h/2,-z/2);
	// 	glTexCoord2f(0.0f,1.0f); glVertex3f( w/2,  h/2, z/2);
	// 	glTexCoord2f(0.0f,0.0f); glVertex3f( w/2, -h/2, z/2);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	// glEnd();
	
	// // Back
	// glBegin(GL_QUADS);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
	// 	glTexCoord2f(1.0f,1.0f); glVertex3f(-w/2,  h/2,-z/2);
	// 	glTexCoord2f(0.0f,1.0f); glVertex3f( w/2,  h/2,-z/2);
	// 	glTexCoord2f(0.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
	// glEnd();
	
	// // Left
	// glBegin(GL_QUADS);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2, z/2);
	// 	glTexCoord2f(1.0f,1.0f); glVertex3f(-w/2,  h/2, z/2);
	// 	glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2,  h/2,-z/2);
	// 	glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f(-w/2, -h/2, z/2);
	// glEnd();
	
	// // Top
	// glBegin(GL_QUADS);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, h/2, z/2);
	// 	glTexCoord2f(1.0f,1.0f); glVertex3f( w/2, h/2,-z/2);
	// 	glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2, h/2,-z/2);
	// 	glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, h/2, z/2);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, h/2, z/2);
	// glEnd();
	
	// // Bottom
	// glBegin(GL_QUADS);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	// 	glTexCoord2f(1.0f,1.0f); glVertex3f( w/2, -h/2, z/2);
	// 	glTexCoord2f(0.0f,1.0f); glVertex3f(-w/2, -h/2, z/2);
	// 	glTexCoord2f(0.0f,0.0f); glVertex3f(-w/2, -h/2,-z/2);
	// 	glTexCoord2f(1.0f,0.0f); glVertex3f( w/2, -h/2,-z/2);
	// glEnd();
}

void Player::setZ(GLfloat z_) {
	z = z_;
}

GLfloat Player::getRefX(){
	return this->x - sin(angY) * 0.01f;
}
GLfloat Player::getRefZ(){
	return this->z - cos(angY) * 0.01f;
}
GLfloat Player::getRefY(){
	return this->y + sin(angX) * 0.01f;
}
