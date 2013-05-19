#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "TicTacToeGL.hpp"
#include <iostream>

#define RADIUS 40.0

using namespace std;

GLfloat projAngle = 100;
GLfloat projNear = 1;
GLfloat projFar = 70;
GLfloat viewerPos [] = { 0.0, 0.0, 0.0 };

GLfloat rVisao=3.0, aVisao=0.25*PI, incVisao=0.3;
GLfloat  obsPini[] ={0, 5, 0};
GLfloat  obsPfin[] ={obsPini[0]-rVisao*cos(aVisao), obsPini[1], obsPini[2]-rVisao*sin(aVisao)};

GLfloat viewInc = 2.0;
GLfloat angInc = 3.0;

double hAng = 45.0;

bool playerX = true;

double toRad(double deg) {
	return (PI*deg)/180;
}

Player TicTacToeGL::p1(PLAYER_H);
Player TicTacToeGL::p2(PLAYER_H);
Player *TicTacToeGL::currPlayer;
int TicTacToeGL::mouseX;
int TicTacToeGL::mouseY;

Table *table;
Surface *sky;
Surface *wall;
Surface *ground;
Fence *f;

/*
 * T | Y | U
 * ---------
 * G | H | J
 * ---------
 * B | N | M
 * 
 * X muda de jogador (so joga se estiver na vez certa)
 * Ainda falta depois desenhar qualquer coisa mais pipi para cada peca
 */

TicTacToeGL::TicTacToeGL(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (XSCREEN, YSCREEN); 
	glutInitWindowPosition (0, 0); 
	glutCreateWindow ("Tic Tac Toe");


	init();

	// glutReshapeFunc(resize);
	glutDisplayFunc(display); 
	
	glutMainLoop();

}

void TicTacToeGL::init(){
	glClearColor(BLACK);
	currPlayer = &p1;

	table = new Table(TABLE_W,TABLE_H,TABLE_D,TABLE_F);
	sky = new Surface(XWORLD,ZWORLD,S_TYPE);
	wall = new Surface(XWORLD,YWORLD,W_TYPE);
	ground = new Surface(XWORLD,ZWORLD,F_TYPE);
	f = new Fence(FENCE_W, FENCE_H, FENCE_D);

	glShadeModel(GL_SMOOTH);
	// initLights();
	initControls();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void TicTacToeGL::initControls(){
	glutSpecialFunc( inputSpecialCb ); 
	glutKeyboardFunc(inputKeyboardCb);
	glutPassiveMotionFunc( inputMouseCb ); // A glutPassiveMotionFunc funciona também em linux
}

void TicTacToeGL::inputMouseCb(int x, int y){

	currPlayer->angY += (x-mouseX) * Player::sensitivity ;
	currPlayer->angX += (mouseY-y) * Player::sensitivity ;

	glutPostRedisplay();

	mouseX = x;
	mouseY = y;
}
void TicTacToeGL::inputSpecialCb(int key, int x, int y){
	switch(key) {
		case GLUT_KEY_UP: {
			obsPini[0]=obsPini[0]+incVisao*cos(aVisao); 
			obsPini[2]=obsPini[2]-incVisao*sin(aVisao); 
		} break;
		
		case GLUT_KEY_DOWN: {
			obsPini[0]=obsPini[0]-incVisao*cos(aVisao); 
			obsPini[2]=obsPini[2]+incVisao*sin(aVisao);
		} break;
		
		case GLUT_KEY_LEFT: { 
			aVisao = (aVisao + 0.1);
		} break;
		
		case GLUT_KEY_RIGHT: {
			aVisao = (aVisao - 0.1);
		} break;
		default: return;
	}
	obsPfin[0] =obsPini[0]+rVisao*cos(aVisao);
	obsPfin[2] =obsPini[2]-rVisao*sin(aVisao);
	glutPostRedisplay();	
	
}
void TicTacToeGL::inputKeyboardCb(unsigned char key, int x, int y){

    switch (key) {
		case 27:
			exit(0);
		break;
		
		case 'r': obsPfin[1] += incVisao; break;
		case 'f': obsPfin[1] -= incVisao; break;
		
		case 'w':
			currPlayer->x += Player::velocity * sin(currPlayer->angY);
			currPlayer->z -= Player::velocity * cos(currPlayer->angY);
		break;
		case 's':
			currPlayer->x -= Player::velocity * sin(currPlayer->angY);
			currPlayer->z += Player::velocity * cos(currPlayer->angY);
		break;
		case 'a':
			currPlayer->x += Player::velocity * sin(currPlayer->angY-PI/2);
			currPlayer->z += Player::velocity * cos(currPlayer->angY-PI/2);
		break;
		case 'd':
			currPlayer->x += Player::velocity * sin(currPlayer->angY+PI/2);
			currPlayer->z += Player::velocity * cos(currPlayer->angY+PI/2);
		break;
		
		case 'x': playerX = !playerX; break;
		
		case 't': table->makeMove(playerX, 0); break;
		case 'y': table->makeMove(playerX, 1); break;
		case 'u': table->makeMove(playerX, 2); break;
		case 'g': table->makeMove(playerX, 3); break;
		case 'h': table->makeMove(playerX, 4); break;
		case 'j': table->makeMove(playerX, 5); break;
		case 'b': table->makeMove(playerX, 6); break;
		case 'n': table->makeMove(playerX, 7); break;
		case 'm': table->makeMove(playerX, 8); break;
   	}	
	glutPostRedisplay();
}


void TicTacToeGL::display(){

	// Viewport
	glViewport(0,0,XSCREEN,YSCREEN);
	// Projecao
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport(0,0,XSCREEN, YSCREEN);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(projAngle, XSCREEN/YSCREEN, projNear, projFar);
	// Observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);

	/*
	 * Muda depois isto a vontade, estava a dar conflito com o que
	 * estava a fazer por isso comentei o teu
	 */
	 
	// printf(">%f\n", currPlayer->getRefX());

	gluLookAt( currPlayer->x, currPlayer->y, currPlayer->z,
			   currPlayer->getRefX(), currPlayer->getRefY(), currPlayer->getRefZ(),
				0,1,0);

	draw();

	glutSwapBuffers();
}

void TicTacToeGL::draw(){

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*glPushMatrix();
		glColor4f(RED);
		glutWireCube(2.0);
	glPopMatrix();*/
	
	drawAxis();
	drawFence();
	drawFloor();
	drawWalls();
	drawSky();
	drawTable();
}

void TicTacToeGL::drawSky() {
	glPushMatrix();
		glTranslatef(0.0,YWORLD, 0.0);
		glRotatef(-90.0,1.0,0.0,0.0);
		sky->drawSurface();
	glPopMatrix();
}

void TicTacToeGL::drawWalls() {
	glPushMatrix();
		glTranslatef(0.0, YWORLD/2, -ZWORLD/2);
		wall->drawSurface();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-XWORLD/2, YWORLD/2, 0.0);
		glRotatef(90.0,0.0,1.0,0.0);
		wall->drawSurface();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(XWORLD/2, YWORLD/2, 0.0);
		glRotatef(-90.0,0.0,1.0,0.0);
		wall->drawSurface();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, YWORLD/2, ZWORLD/2);
		glRotatef(180.0,0.0,1.0,0.0);
		wall->drawSurface();
	glPopMatrix();
}

void TicTacToeGL::drawFloor() {
	glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		ground->drawSurface();
	glPopMatrix();
}

void TicTacToeGL::drawTable() {
	glPushMatrix();
		table->drawTable();
	glPopMatrix();
}

void TicTacToeGL::drawAxis() {
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3i(-XWORLD/2,0,0);
		glVertex3i(XWORLD/2,0,0);
		glVertex3i(0,-YWORLD/2,0);
		glVertex3i(0,YWORLD/2,0);
		glVertex3i(0,0,-ZWORLD/2);
		glVertex3i(0,0,ZWORLD/2);
	glEnd();
}

void TicTacToeGL::drawFence() {
	int numberOfFences = SQUARESIZE/FENCE_W;
	
	//FIX THIS
	double difference = SQUARESIZE-numberOfFences*FENCE_W;
	
	bool corner = difference > 0.1;
	
	int i;
	
	glPushMatrix();
	
	glTranslatef(0.0,FENCE_H/2, 0.0);

	for(i = 0; i < numberOfFences; i++) {
		glPushMatrix();
			glTranslatef(-SQUARESIZE/2+i*FENCE_W, 0.0, -SQUARESIZE/2);
			f->drawFence();
		glPopMatrix();
	}
	if(corner) {
		glPushMatrix();
			glTranslatef(-SQUARESIZE/2+numberOfFences*FENCE_W-difference/4, 0.0, -SQUARESIZE/2);
			f->drawSmallPiece(difference);
			glColor3f(1.0,1.0,1.0);
			glBegin(GL_LINES);
			glVertex3f(0.0,0.0,0.0);
			glVertex3f(difference,0.0,0.0);
			glEnd();
		glPopMatrix();
	}
	
	for(i = 0; i < numberOfFences; i++) {
		glPushMatrix();
			glTranslatef(SQUARESIZE/2-FENCE_W/2, 0.0, i*FENCE_W-SQUARESIZE/2);
			glRotatef(90.0, 0, 1 , 0);
			f->drawFence();
		glPopMatrix();
	}
	if(corner) {
		glPushMatrix();
			glTranslatef(SQUARESIZE/2, 0.0, numberOfFences*FENCE_W-difference/4-SQUARESIZE/2);
			glRotatef(90.0, 0, 1 , 0);
			f->drawSmallPiece(difference);
		glPopMatrix();
	}
	
	for(i = 0; i < numberOfFences; i++) {
		glPushMatrix();
			glTranslatef(-SQUARESIZE/2, 0.0, i*FENCE_W-SQUARESIZE/2);
			glRotatef(-90.0, 0, 1 , 0);
			f->drawFence();
		glPopMatrix();
	}
	if(corner) {
		glPushMatrix();
			glTranslatef(-SQUARESIZE/2, 0.0, numberOfFences*FENCE_W-difference/4-SQUARESIZE/2);
			glRotatef(-90.0, 0, 1 , 0);
			f->drawSmallPiece(difference);
		glPopMatrix();
	}
	
	for(i = 0; i < numberOfFences; i++) {
		glPushMatrix();
			glTranslatef(i*FENCE_W-SQUARESIZE/2, 0.0, SQUARESIZE/2);
			glRotatef(180, 0, 1 , 0);
			f->drawFence();
		glPopMatrix();
	}
	if(corner) {
		glPushMatrix();
			glTranslatef(numberOfFences*FENCE_W-difference/4-SQUARESIZE/2, 0.0, SQUARESIZE/2);
			glRotatef(180, 0, 1 , 0);
			f->drawSmallPiece(difference);
		glPopMatrix();
	}
	
	glPopMatrix();
}

int main(int argc, char **argv){
	new TicTacToeGL(argc, argv);
}
