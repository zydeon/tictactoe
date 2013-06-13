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

GLfloat globalLightColor[4];


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


	XSCREEN = glutGet(GLUT_SCREEN_WIDTH);
	YSCREEN = glutGet(GLUT_SCREEN_HEIGHT);
	glClearColor(BLACK);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	initControls();
	initLights();
	initObjects();

	glutDisplayFunc(display);
	
	glutMainLoop();
}

void initObjects(){
	table = new Table(TABLE_W,TABLE_H,TABLE_D,TABLE_F);
	sky = new Surface(XWORLD,ZWORLD,S_TYPE);
	wall = new Surface(YWORLD, XWORLD,W_TYPE);
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

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ); 
	glEnable(GL_LIGHTING);
	
		// glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glColor4f(BLUE);
		glTranslatef (-1.2, 5.0, 10.2);		
		// glutSolidSphere(1.2, 250, 250);
		glutSolidCube(3.0);
		glPopMatrix();

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
		sky->drawSurface(0, -1, 0);
	glPopMatrix();
}

void drawWalls() {
	glPushMatrix();
		glTranslatef(0, YWORLD/2, -ZWORLD/2);
		wall->drawSurface(0,0,1);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-XWORLD/2, YWORLD/2, 0.0);
		glRotatef(90.0,0.0,1.0,0.0);
		wall->drawSurface(1,0,0);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(XWORLD/2, YWORLD/2, 0.0);
		glRotatef(-90.0,0.0,1.0,0.0);
		wall->drawSurface(-1,0,0);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, YWORLD/2, ZWORLD/2);
		glRotatef(180.0,0.0,1.0,0.0);
		wall->drawSurface(0,0,-1);
	glPopMatrix();
}

void drawFloor() {
	glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		ground->drawSurface(0, 1, 0);
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

void initLights(void){
	globalLightColor[0] = 0.6;
	globalLightColor[1] = 0.6;
	globalLightColor[2] = 0.6;
	globalLightColor[3] = 1.0;

	// Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalLightColor);

	// // Tecto (Pontual)
	// glEnable(GL_LIGHT0);
	// GLfloat localCor[4] ={0.1, 0.1, 0.1, 1.0};
	// GLfloat localPos[4] ={xC/2, 10.0, xC/2, 1.0};//{0, xC, 0, 1.0};
	// GLfloat localCorDif[4] ={ 1, 1, 1, 1.0}; 
	// GLfloat localAttCon =1.0;
	// GLfloat localAttLin =0.05;
	// GLfloat localAttQua =0.0;	
	// glLightfv(GL_LIGHT0, GL_POSITION, localPos );
	// glLightfv(GL_LIGHT0, GL_AMBIENT, localCor );
	// glLightfv(GL_LIGHT0, GL_DIFFUSE,       localCorDif );   
	// glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
	// glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin) ;
	// glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua) ;

	// // Foco
	// glEnable(GL_LIGHT1);
	// GLfloat direccao[ ] = { sin(angY) , 0, -cos(angY)};
	// GLfloat concentracao = 128;
	// GLfloat angulo = 20.0;
	// // glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direccao );
	// glLightf (GL_LIGHT1, GL_SPOT_EXPONENT , concentracao);
	// glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, angulo);
	// GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
	// GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
	// GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
	// // GLfloat positionLight[4] ={x, y, z, 1.0};
	// // glLightfv(GL_LIGHT1, GL_POSITION, positionLight );
	// glLightfv(GL_LIGHT1, GL_AMBIENT, blackAmbientLight );
	// glLightfv(GL_LIGHT1, GL_SPECULAR, whiteSpecularLight);
	// glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteDiffuseLight);
	// // glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	// // glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05) ;
	// // glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION,0.0) ;	
}
