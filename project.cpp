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
#include <time.h>
#include "project.hpp"
#include "resources.hpp"
#include "Surface.hpp"
#include "Light.hpp"
#include "glm.h"
#include "Player.hpp"

using namespace std;

// pixels resolution of screen (dynamic)
int XSCREEN;
int YSCREEN;

GLfloat projAngle = 100;
GLfloat projNear = 1;
GLfloat projFar = 200;

bool playerX = true;

Player *players[2];
int currPlayerIndex;
Player *currPlayer;

int mouseX;
int mouseY;

Table *table;
Surface *sky;
Surface *walls[4];
Surface *ground;
Fence *fence;

Light L0, L1;

char nearTable;

// GLMmodel *bunny;

// collisions
GLfloat collisionDist = 0.7f;
GLfloat newPositionX;
GLfloat newPositionZ;

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

	srand (time(NULL));

	XSCREEN = glutGet(GLUT_SCREEN_WIDTH);
	YSCREEN = glutGet(GLUT_SCREEN_HEIGHT);
	glClearColor(BLACK);

	initControls();
	initObjects();
	initLights();
	initFog();

	glutDisplayFunc(display);
	glutTimerFunc(TIMER_MSEC, update, 0);
	
	glutMainLoop();
}

void update(int v){
	table->game->updatePieces();
	glutPostRedisplay();
	glutTimerFunc(TIMER_MSEC, update, 0);
}

void initObjects(){
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	table = new Table(0, 0, 0, TABLE_W,TABLE_H,TABLE_D);
	ground = new Surface(FLOOR_BMP, Material() );
	fence = new Fence(20, 15, 15);

	// no light
	sky = new Surface(WALLS_TOP_BMP, Material() );
	walls[0] = new Surface(WALLS_FRONT_BMP, Material() );
	walls[1] = new Surface(WALLS_RIGHT_BMP, Material() );
	walls[2] = new Surface(WALLS_BACK_BMP, Material() );
	walls[3] = new Surface(WALLS_LEFT_BMP, Material() );

	/*bunny = glmReadOBJ("models/fence.obj");
	if (!bunny)  exit(0);
	glmUnitize(bunny);
	glmFacetNormals(bunny);
	glmVertexNormals(bunny, 90.0);
	glmLinearTexture(bunny);
	glmReadMTL(bunny, "fence.mtl");*/

	players[0] = new Player(FOOT_H+LEG_H+TORSO_H+NECK_W+HEAD_H/2, 0);
	players[1] = new Player(FOOT_H+LEG_H+TORSO_H+NECK_W+HEAD_H/2, 1);

	players[0]->setZ(5.0);
	players[1]->setZ(-5.0);
	players[1]->angY = PI;
	currPlayerIndex = 0;
	currPlayer = players[currPlayerIndex];	
}

void initLights(){
	glEnable(GL_LIGHTING);
	// Global ambient model
	color4 globalAmbientColor = color4(0.3, 0.3, 0.3, 1.0f);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor.values );

	// Personal focus
	L0 = Light( 		GL_LIGHT0,
						color4( 0.2, 0.2, 0.2, 1.0 ), 	// ambient
						color4( 0.8	, 0.8, 0.8, 1.0 ),	// diffuse
						color4( 1.0, 1.0, 0.0, 1.0 ),	// specular
						float4( 0.0, 20.0, 0.0, 1.0 ),	// position 		(will be updated)
						float3( 0.0, -1.0, 0.0 ),		// spot direction	(will be updated)
						0,								// spot exponent
						10.0f							// spot cutoff
					);	

	// Lamp
	L1 = Light( 		GL_LIGHT1,
						color4( 0.2, 0.2, 0, 1.0 ), 	// ambient
						color4( 0.8, 0.2, 0, 1.0 ),		// diffuse
						color4( 1.0, 1.0, 0.0, 1.0 ),	// specular
						float4( 0.0, 10.0, 0.0, 1.0 ),	// position 		(will be updated)
						float3( 0.0, -1.0, 0.0 ),		// spot direction	(will be updated)
						0,								// spot exponent
						10.0f							// spot cutoff
					);

}

void initFog(){
	glEnable(GL_FOG);
	color4 fogColor = color4(0.60, 0.60, 0.60, 1);

	glFogfv(GL_FOG_COLOR, fogColor.values);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 40.0);
	// glFogf(GL_FOG_DENSITY, 0.35);
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
			newPositionX = currPlayer->x - Player::velocity * sin(currPlayer->angY);
			newPositionZ = currPlayer->z - Player::velocity * cos(currPlayer->angY);
		break;
		case 's':
			newPositionX = currPlayer->x + Player::velocity * sin(currPlayer->angY);
			newPositionZ = currPlayer->z + Player::velocity * cos(currPlayer->angY);
		break;
		case 'a':
			newPositionX = currPlayer->x + Player::velocity * sin(currPlayer->angY-PI/2);
			newPositionZ = currPlayer->z + Player::velocity * cos(currPlayer->angY-PI/2);
		break;
		case 'd':
			newPositionX = currPlayer->x + Player::velocity * sin(currPlayer->angY+PI/2);
			newPositionZ = currPlayer->z + Player::velocity * cos(currPlayer->angY+PI/2);
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
	float3 currPosition2 = float3(players[!currPlayerIndex]->x, players[!currPlayerIndex]->y, players[!currPlayerIndex]->z);

	// se estiver perto da mesa
	if(distance_(currPosition, float3(table->x,table->y,table->z) ) < 6 ){
		nearTable = 1;

		// reset position
		checkCollisionObject(table->x, table->z, TABLE_W, TABLE_D);
	}
	else{
		nearTable = 0;
	}

	// other player
	checkCollisionObject(players[!currPlayerIndex]->x, players[!currPlayerIndex]->z, TORSO_W +1+ collisionDist, HEAD_D + collisionDist);

	// fence
	if( newPositionX > 0 + fence->width/2 - collisionDist ) newPositionX = 0 + fence->width/2 - collisionDist;
	if( newPositionX < 0 - fence->width/2 + collisionDist ) newPositionX = 0 - fence->width/2 + collisionDist ;
	if( newPositionZ > 0 + fence->height/2 - collisionDist ) newPositionZ = 0 + fence->height/2 - collisionDist;
	if( newPositionZ < 0 - fence->height/2 + collisionDist ) newPositionZ = 0 - fence->height/2 + collisionDist;

	currPlayer->x = newPositionX;
	currPlayer->z = newPositionZ;
}

void checkCollisionObject(GLfloat x, GLfloat z, GLfloat w, GLfloat d){
	if( newPositionZ > z -d/2 && newPositionZ < z + d/2 ){
		if( newPositionX > x - w/2 - collisionDist && currPlayer->x <= x - w/2 )
			newPositionX = x - w/2 - collisionDist;
		if( newPositionX < x + w/2 + collisionDist && currPlayer->x >= x + w/2){
			newPositionX = x + w/2 + collisionDist;
		}
	}
	if( newPositionX > x -w/2 && newPositionX < x + w/2 ){
		if( newPositionZ > z - d/2 - collisionDist && currPlayer->z <= z - d/2 )
			newPositionZ = z - d/2 - collisionDist;
		if( newPositionZ < z + d/2 + collisionDist && currPlayer->z >= z + d/2){
			newPositionZ = z + d/2 + collisionDist;
		}
	}
}

void changePlayer() {
	playerX = !playerX;
	currPlayerIndex = (currPlayerIndex + 1) % 2;
	currPlayer = players[currPlayerIndex];
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

	enableLights();
	draw();

	if(nearTable){
		//--- 2D
		// Viewport
		glViewport(0,0,200, 200);
		// Projecao
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho( -table->width/2,table->width/2, -table->width/2,table->width/2, -0.2,10 );
		// Observador
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0,table->height,0, 0,0,0, 0,0,-1);

		enableLights();
		drawGame();	
	}

	glutSwapBuffers();
}

void enableLights(){
	L0.update( 	float4(currPlayer->x, currPlayer->y, currPlayer->z, 1),
				float3(-sin(currPlayer->angY), sin(currPlayer->angX), -cos(currPlayer->angY)) );
	L1.enable();
	L0.enable();
}

void draw(){
	/*glEnable(GL_COLOR_MATERIAL);
	glTranslatef(0,4,0);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glColor3f(0.2,0.2,0.2);
	glmDraw(bunny, GLM_SMOOTH  );
	glTranslatef(0,-4,0);
	glDisable(GL_COLOR_MATERIAL);*/

	drawFence();
	drawWalls();
	drawSky();
	drawFloor();
	drawPlayers();
	drawGame();
	// drawAxis();
}


void drawSky() {
	glPushMatrix();
		glTranslatef(0.0,YWORLD, 0.0);
		glRotatef(90 ,1 ,0 ,0 );
		sky->draw(XWORLD, ZWORLD, GL_DECAL);
	glPopMatrix();
}

void drawWalls() {
	int i;
	glPushMatrix();
	glTranslatef(0, YWORLD/2, 0);
	for( i = 0; i < 4; ++i ){
		glTranslatef(0, 0, -ZWORLD/2);
		walls[i]->draw(XWORLD, YWORLD, GL_DECAL);
		glTranslatef(0, 0, ZWORLD/2);
		glRotatef(-90, 0, 1, 0);
	}
	glPopMatrix();
}

void drawGame() {
	glPushMatrix();
		glTranslatef(0, TABLE_H/2, 0);
		table->drawTable();
	glPopMatrix();
}

void drawFloor() {
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		ground->draw(XWORLD, ZWORLD);
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
	fence->draw();
}

void drawPlayers() {
	glPushMatrix();
		glTranslatef(players[0]->x, players[0]->y, players[0]->z);
		glRotatef(toDeg(players[0]->angY)+180 ,0,1,0);
		players[0]->drawPlayer();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(players[1]->x, players[1]->y, players[1]->z);
		glRotatef(toDeg(players[1]->angY)+180 ,0,1,0);
		players[1]->drawPlayer();
	glPopMatrix();
}

double toRad(double deg) {
	return (PI*deg)/180;
}

GLfloat toDeg(GLfloat rad) {
	return 180*rad/PI;
}
