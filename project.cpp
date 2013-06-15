#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "project.hpp"
#include "resources.hpp"
#include "Light.hpp"

using namespace std;

GLfloat projAngle = 100;
GLfloat projNear = 1;
GLfloat projFar = 200;

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

Light L0, L1;

char nearTable;

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
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  | GLUT_STENCIL);
	glutInitWindowSize (XWINDOW, YWINDOW); 
	glutInitWindowPosition (XWINDOW_POS, YWINDOW_POS); 
	glutCreateWindow ("Tic Tac Toe");

	XSCREEN = glutGet(GLUT_SCREEN_WIDTH);
	YSCREEN = glutGet(GLUT_SCREEN_HEIGHT);
	glClearColor(BLACK);

	initControls();
	initObjects();
	initLights();

	glutDisplayFunc(display);
	
	glutMainLoop();
}

void initObjects(){
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	table = new Table(TABLE_W,TABLE_H,TABLE_D,TABLE_F);
	sky = new Surface(XWORLD, ZWORLD, SKY_BMP, Material() );
	wall = new Surface(YWORLD, XWORLD, WALLS_BMP, Material() );
	ground = new Surface(XWORLD,ZWORLD, FLOOR_BMP, Material() );
	f = new Fence(FENCE_W, FENCE_H, FENCE_D);	

	players[0].loadTextures(true);
	players[0].setZ(5.0);
	players[1].loadTextures(false);
	players[1].setZ(-5.0);
	currPlayerIndex = 0;
	currPlayer = &players[currPlayerIndex];	
}

void initLights(){
	glEnable(GL_LIGHTING);
	// Global ambient model
	color4 globalAmbientColor = color4(0.7f, 0.7f, 0.7f, 1.0f);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor.values );

	// Personal focus
	L0 = Light( 		GL_LIGHT0,
						color4( 0.2, 0.2, 0.2, 1.0 ), 	// ambient
						color4( 0.8, 0.8, 0.8, 1.0 ),	// diffuse
						color4( 1.0, 1.0, 0.0, 1.0 ),	// specular
						float4( 0.0, 20.0, 0.0, 1.0 ),	// position 		(will be updated)
						float3( 0.0, -1.0, 0.0 ),		// spot direction	(will be updated)
						128,							// spot exponent
						80.0f							// spot cutoff
					);	

	// lamp
	L1 = Light( 		GL_LIGHT1,
						color4( 0.2, 0, 0, 1.0 ), 	// ambient
						color4( 0.8, 0, 0, 1.0 ),	// diffuse
						color4( 1.0, 1.0, 0.0, 1.0 ),	// specular
						float4( 0.0, 10.0, 0.0, 1.0 ),	// position 		(will be updated)
						float3( 0.0, -1.0, 0.0 ),		// spot direction	(will be updated)
						128,							// spot exponent
						60.0f							// spot cutoff
					);

}

void initControls(){
	//glutSpecialFunc( inputSpecialCb ); 
	glutKeyboardFunc(inputKeyboardCb);

	// centrar rato
	mouseX = XWINDOW/2;
	mouseY = YWINDOW/2;
	glutWarpPointer(mouseX, mouseY);
	glutPassiveMotionFunc(inputMouseCb);
	glutSetCursor(GLUT_CURSOR_NONE);
}

void inputKeyboardCb(unsigned char key, int x, int y){
	switch (key) {
		case 27:
				exit(0);
		break;
		
		case 'w':
				currPlayer->x -= Player::velocity * sin(currPlayer->angY);
				currPlayer->z -= Player::velocity * cos(currPlayer->angY);
		break;
		case 's':
				currPlayer->x += Player::velocity * sin(currPlayer->angY);
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
		
		case 't': if(nearTable) table->makeMove(playerX, 0); break;
		case 'y': if(nearTable) table->makeMove(playerX, 1); break;
		case 'u': if(nearTable) table->makeMove(playerX, 2); break;
		case 'g': if(nearTable) table->makeMove(playerX, 3); break;
		case 'h': if(nearTable) table->makeMove(playerX, 4); break;
		case 'j': if(nearTable) table->makeMove(playerX, 5); break;
		case 'b': if(nearTable) table->makeMove(playerX, 6); break;
		case 'n': if(nearTable) table->makeMove(playerX, 7); break;
		case 'm': if(nearTable) table->makeMove(playerX, 8); break;
	}       

	checkCollisions();
	glutPostRedisplay();
}

double distance_(float3 p1, float3 p2){
	return sqrt( (p1.values[0]-p2.values[0])*(p1.values[0]-p2.values[0]) +
				 (p1.values[1]-p2.values[1])*(p1.values[1]-p2.values[1]) +
				 (p1.values[2]-p2.values[2])*(p1.values[2]-p2.values[2]) );
}

void checkCollisions(){
	float3 currPosition = float3(currPlayer->x, currPlayer->y, currPlayer->z);

	// se estiver perto da mesa
	nearTable = distance_(currPosition, float3(0,0,0)) < 5;

	// TODO RESTO DAS COLISOES
}

void changePlayer() {
	playerX = !playerX;
	currPlayerIndex = (currPlayerIndex + 1) % 2;
	currPlayer = &players[currPlayerIndex];
}

void inputMouseCb(int x, int y){
	currPlayer->angX += (mouseY-y) * Player::sensitivity ;
	currPlayer->angY += (mouseX-x) * Player::sensitivity ;
	if(currPlayer->angX > PI/2) currPlayer->angX = PI/2;
	if(currPlayer->angX < -PI/2) currPlayer->angX = -PI/2;

	// fake continuous movement
	if( x == -XWINDOW_POS )  // limite esquerdo
			mouseX++;
	else if( x == XSCREEN-XWINDOW_POS )  // limite direito
			mouseX--;
	else mouseX = x;
	if( y == -YWINDOW_POS )  // limite cima
			mouseY++;
	else if( y == YSCREEN-YWINDOW_POS )  // limite direito
			mouseY--;
	else mouseY = y;

	glutPostRedisplay();    
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//--- 3D
	// Viewport
	glViewport(0,0,XWINDOW,YWINDOW);
	// Projecao
	glViewport(0,0,XWINDOW, YWINDOW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(projAngle, XWINDOW/YWINDOW, projNear, projFar);
	// Observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	currPlayer->x, currPlayer->y, currPlayer->z,
				currPlayer->getRefX(), currPlayer->getRefY(), currPlayer->getRefZ(),
				0, 1, 0);
	draw();

	if(nearTable){
		//--- 2D
		// Viewport
		glViewport(0,0,200, 200);
		// Projecao
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho( -1,1, -1,1, -0.2,10 );
		// Observador
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0,table->height/2,0, 0,0,0, 0,0,-1);
		draw();	
	}

	glutSwapBuffers();
}

void draw(){
	L0.update( 	float4(currPlayer->x, currPlayer->y, currPlayer->z, 1),
				float3(-sin(currPlayer->angY), sin(currPlayer->angX), -cos(currPlayer->angY)) );
	L1.enable();
	L0.enable();
		drawFence();
		drawWalls();
		drawSky();
		drawFloor();
		drawPlayers();
		drawTable();

		drawAxis();
	L0.disable();
}

void drawSky() {
	glPushMatrix();
		glTranslatef(0.0,YWORLD, 0.0);
		glRotatef(90 ,1 ,0 ,0 );
		sky->drawSurface();
	glPopMatrix();
}

void drawWalls() {
	glPushMatrix();
		glTranslatef(0, YWORLD/2, -ZWORLD/2);
		wall->drawSurface();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-XWORLD/2, YWORLD/2, 0 );
		glRotatef(90 ,0 ,1 ,0 );
		wall->drawSurface();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(XWORLD/2, YWORLD/2, 0 );
		glRotatef(-90 ,0 ,1 ,0 );
		wall->drawSurface();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0 , YWORLD/2, ZWORLD/2);
		glRotatef(180 ,0 ,1 ,0 );
		wall->drawSurface();
	glPopMatrix();
}

void drawTable() {
	glPushMatrix();
		table->drawTable();
	glPopMatrix();
}

void drawFloor() {
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		ground->drawSurface();
	glPopMatrix();
}
void drawAxis() {
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3i(-XWORLD/2,0.4,0);
		glVertex3i(XWORLD/2,0.4,0);
		glVertex3i(0,-YWORLD/2,0);
		glVertex3i(0,YWORLD/2,0);
		glVertex3i(0,0.4,-ZWORLD/2);
		glVertex3i(0,0.4,ZWORLD/2);
	glEnd();
	glEnable(GL_LIGHTING);
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
		glTranslatef(players[0].x, players[0].y, players[0].z);
		glRotatef(toDeg(players[0].angY)+180 ,0,1,0);
		players[0].drawPlayer();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(players[1].x, players[1].y, players[1].z);
		glRotatef(toDeg(players[1].angY)+180 ,0,1,0);
		players[1].drawPlayer();
	glPopMatrix();
}

double toRad(double deg) {
	return (PI*deg)/180;
}

GLfloat toDeg(GLfloat rad) {
	return 180*rad/PI;
}
