#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "project.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

GLfloat projAngle = 100;
GLfloat projNear = 1;
GLfloat projFar = 70;

double hAng = 45.0;

bool playerX = true;

vector<Player> players(2, Player(FOOT_H+LEG_H+TORSO_H/2)); 
int currPlayerIndex;
Player *currPlayer;

int mouseX;
int mouseY;

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
 
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (XWINDOW, YWINDOW); 
	glutInitWindowPosition (XWINDOW_POS, YWINDOW_POS); 
	glutCreateWindow ("Tic Tac Toe");

	init();
	XSCREEN = glutGet(GLUT_SCREEN_WIDTH);
	YSCREEN = glutGet(GLUT_SCREEN_HEIGHT);

	glutDisplayFunc(display);
	
	glutMainLoop();
}

void init(){
	glClearColor(BLACK);
	
	glShadeModel(GL_SMOOTH);
	// initLights();
	initControls();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	table = new Table(TABLE_W,TABLE_H,TABLE_D,TABLE_F);
	sky = new Surface(XWORLD,ZWORLD,S_TYPE);
	wall = new Surface(XWORLD,YWORLD,W_TYPE);
	ground = new Surface(XWORLD,ZWORLD,F_TYPE);
	f = new Fence(FENCE_W, FENCE_H, FENCE_D);
	
	players[0].loadTextures(true);
	players[0].setZ(5.0);
	players[1].loadTextures(false);
	players[1].setZ(-5.0);
	currPlayerIndex = 0;
	currPlayer = &players[currPlayerIndex];
}

void initControls(){
	//glutSpecialFunc( inputSpecialCb ); 
	glutKeyboardFunc(inputKeyboardCb);
	glutPassiveMotionFunc(inputMouseCb); // A glutPassiveMotionFunc funciona também em linux
}

void inputKeyboardCb(unsigned char key, int x, int y){

    switch (key) {
		case 27:
			exit(0);
		break;
		
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
		
		case 'x': changePlayer(); break;
		
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

void changePlayer() {
	playerX = !playerX;
	currPlayerIndex = (currPlayerIndex + 1) % 2;
	currPlayer = &players[currPlayerIndex];
}

void inputMouseCb(int x, int y){
	currPlayer->angY += (x-mouseX) * Player::sensitivity ;
	currPlayer->angX += (mouseY-y) * Player::sensitivity ;

	// fake continuous movement
	if( x == -XWINDOW_POS )  // limite esquerdo
		mouseX++;
	else if( x == XSCREEN-XWINDOW_POS )  // limite direito
		mouseX--;
	else mouseX = x;

	mouseY = y;
	glutPostRedisplay();	
}

void display(){

	// Viewport
	glViewport(0,0,XWINDOW,YWINDOW);
	
	// Projecao
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport(0,0,XWINDOW, YWINDOW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(projAngle, XWINDOW/YWINDOW, projNear, projFar);
	
	// Observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(currPlayer->x, currPlayer->y, currPlayer->z,
			   currPlayer->getRefX(), currPlayer->getRefY(), currPlayer->getRefZ(),
				0,1,0);

	draw();

	glutSwapBuffers();
}

void draw(){

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawAxis();
	drawFence();
	drawFloor();
	drawWalls();
	drawSky();
	drawTable();
	drawPlayers();
}

void drawSky() {
	glPushMatrix();
		glTranslatef(0.0,YWORLD, 0.0);
		glRotatef(-90.0,1.0,0.0,0.0);
		sky->drawSurface();
	glPopMatrix();
}

void drawWalls() {
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

void drawFloor() {
	glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		ground->drawSurface();
	glPopMatrix();
}

void drawTable() {
	glPushMatrix();
		table->drawTable();
	glPopMatrix();
}

void drawAxis() {
	
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

void drawFence() {
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

void drawPlayers() {
	glPushMatrix();
		glPushMatrix();
			glTranslatef(players[0].getRefX(), players[0].getRefY(), players[0].getRefZ());
			players[0].drawPlayer();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(players[1].getRefX(), players[1].getRefY(), players[1].getRefZ());
			players[1].drawPlayer();
		glPopMatrix();
	glPopMatrix();
}

double toRad(double deg) {
	return (PI*deg)/180;
}
