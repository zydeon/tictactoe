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
#include "project.hpp"
#include "resources.hpp"
#include "Light.hpp"

using namespace std;

GLfloat projAngle = 100;
GLfloat projNear = 1;
GLfloat projFar = 70;

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

Light L1;

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

	initObjects();
	initLights();

	glutDisplayFunc(display);
	
	glutMainLoop();
}

void initObjects(){
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void initLights(){
	// Global ambient model
	// color4 globalAmbientColor = color4(0.3f, 0.3f, 0.3f, 1.0f);
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor.values );

	// Personal focus
	// L1 = Light( 		GL_LIGHT0,
	// 					color4( 0.0, 0.0, 0.0, 1.0 ), 	// ambient
	// 					color4( 1.0, 1.0, 1.0, 1.0 ),	// diffuse
	// 					color4( 1.0, 1.0, 1.0, 1.0 ),	// specular
	// 					float4( 0.0, 5.0, 0.0, 1.0 ),	// position 		(will be updated)
	// 					float3( 0.0, -1.0, 0.0 ),		// spot direction	(will be updated)
	// 					128.0f,							// spot exponent
	// 					20.0f							// spot cutoff
	// 				);
	// L1.enable();

// GLfloat incH =0.0, incV=0.0;
// GLfloat incMaxH =0.5, incMaxV=0.35;
// GLfloat focoPini[]= { 0.0, 5.0, 0.0, 1.0 };
// GLfloat focoDir[] = { 0.0, -1.0, 0.0};
// GLfloat focoExp   = 10.0;
// GLfloat focoCut   = 15.0;	
// GLfloat focoCorEsp[4] ={ 1.0 ,  1.0, 1.0, 1.0}; 
// GLfloat focoCorDif[4] ={ 0.85, 0.85,0.85, 1.0}; 	

// 	glLightfv(GL_LIGHT1, GL_POSITION,      focoPini );
// 	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,focoDir );
// 	glLightf (GL_LIGHT1, GL_SPOT_EXPONENT ,focoExp);
// 	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF,   focoCut);
// 	glLightfv(GL_LIGHT1, GL_DIFFUSE,       focoCorDif );   
// 	glLightfv(GL_LIGHT1, GL_SPECULAR,      focoCorEsp  );		

GLfloat localCor[4] ={0.2,0.2,0.2,1.0}; 
GLfloat localCorDif[4] ={ 1, 1, 1, 1.0}; 
GLfloat localPos[4] ={0, 2, 0, 1.0};
GLfloat localAttCon =1.0;
GLfloat localAttLin =0.05;
GLfloat localAttQua =0.0;
GLfloat DIR[3] ={ 0, 1, 0}; 
GLfloat focoExp   = 128.0;
GLfloat focoCut   = 45.0f;

	glLightfv(GL_LIGHT0, GL_AMBIENT,       localCor );   
	glLightfv(GL_LIGHT0, GL_DIFFUSE,       localCorDif ); 
	glLightfv(GL_LIGHT0, GL_POSITION,      localPos );   
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,DIR );
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,   focoCut);	

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

	gluLookAt(6, 6, 6, 0, 0, 0, 0, 1, 0);


GLfloat localCor[4] ={0.2,0.2,0.2,1.0}; 
GLfloat localCorDif[4] ={ 1, 1, 1, 1.0}; 
GLfloat localPos[4] ={0, 2, 0, 1.0};
GLfloat localAttCon =1.0;
GLfloat localAttLin =0.05;
GLfloat localAttQua =0.0;
GLfloat DIR[3] ={ 0, -1, 0}; 
GLfloat focoExp   = 128.0;
GLfloat focoCut   = 10.0f;

	glLightfv(GL_LIGHT0, GL_AMBIENT,       localCor );   
	glLightfv(GL_LIGHT0, GL_DIFFUSE,       localCorDif ); 
	glLightfv(GL_LIGHT0, GL_POSITION,      localPos );   
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION,DIR );
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,   focoCut);

	draw();

	glutSwapBuffers();
}

void draw(){
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_LIGHTING);

	glColor4f(1, 0, 0, 1);
	glutSolidSphere(1.2, 250, 250);

	// glPushMatrix();
	// 	glColor4f(1, 1, 1, 1);
	// 	glTranslatef(0, 2, 0);
	// 	glutSolidSphere(0.2, 250, 250);
	// glPopMatrix();	

	glPushMatrix();
		glColor4f(0, 1, 0, 1);
		glTranslatef(0, 4, 0);
		glutSolidSphere(1.2, 250, 250);
	glPopMatrix();


	glPushMatrix();
		glColor4f(0, 0, 1, 1);
		glTranslatef(0, -4, 0);
		glutSolidSphere(1.2, 250, 250);
	glPopMatrix();

	glPushMatrix();
		glColor4f(1, 1, 0, 1);
		glTranslatef(4, 0, 0);
		glutSolidSphere(1.2, 250, 250);
	glPopMatrix();		

	glPushMatrix();
		glColor4f(0, 1, 1, 1);
		glTranslatef(-4, 0, 0);
		glutSolidSphere(1.2, 250, 250);
	glPopMatrix();

	drawAxis();

}

void drawFloor() {
	glPushMatrix();
		glRotatef(90.0, 1.0, 0.0, 0.0);
		ground->drawSurface(0, 1, 0);
	glPopMatrix();
}
void drawAxis() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex3i(-XWORLD/2,0,0);
		glVertex3i(XWORLD/2,0,0);
		glVertex3i(0,-YWORLD/2,0);
		glVertex3i(0,YWORLD/2,0);
		glVertex3i(0,0,-ZWORLD/2);
		glVertex3i(0,0,ZWORLD/2);
	glEnd();
}
