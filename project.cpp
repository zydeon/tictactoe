#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include <iostream>
#include "Fence.hpp"

#define WS 800
#define HS 600
#define SCENE_SIZE 50

#define FENCE_W 5
#define FENCE_H 25
#define FENCE_D 0.5

using namespace std;

GLfloat projAngle = 90;
GLfloat projNear = 5;
GLfloat projFar = 170;
GLfloat viewerPos [] = { 70.0, 70.0, 70.0 };

void init() {
	glClearColor(0,0,0,1);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_DEPTH_TEST);
}

void drawAxis() {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex3i(0,0,0);
		glVertex3i(SCENE_SIZE,0,0);
		glVertex3i(0,0,0);
		glVertex3i(0,SCENE_SIZE,0);
		glVertex3i(0,0,0);
		glVertex3i(0,0,SCENE_SIZE);
	glEnd();
}

void drawFence() {
	int numberOfFences = SCENE_SIZE/FENCE_W + 1;
	
	int i;
	
	Fence *f;
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	cout << numberOfFences << " fences" << endl;
	
	for(i = 0; i < numberOfFences; i++) {
		f = new Fence(FENCE_W, FENCE_H, FENCE_D);
		glPushMatrix();
			glTranslatef(i*FENCE_W, 0.0, 0.0);
			f->drawFence();
		glPopMatrix();
	}
	
	for(i = 0; i < numberOfFences; i++) {
		f = new Fence(FENCE_W, FENCE_H, FENCE_D);
		glPushMatrix();
			glTranslatef(0.0, 0.0, i*FENCE_W);
			glRotatef(90.0, 0, 1 , 0);
			f->drawFence();
		glPopMatrix();
	}
	
	for(i = 0; i < numberOfFences; i++) {
		f = new Fence(FENCE_W, FENCE_H, FENCE_D);
		glPushMatrix();
			glTranslatef(SCENE_SIZE, 0.0, i*FENCE_W);
			glRotatef(-90.0, 0, 1 , 0);
			f->drawFence();
		glPopMatrix();
	}
	
	for(i = 0; i < numberOfFences; i++) {
		f = new Fence(FENCE_W, FENCE_H, FENCE_D);
		glPushMatrix();
			glTranslatef(i*FENCE_W, 0.0, SCENE_SIZE);
			glRotatef(180, 0, 1 , 0);
			f->drawFence();
		glPopMatrix();
	}
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Viewport
	glViewport(0,0,WS,HS);
	// Projecao
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(projAngle, WS/HS, projNear, projFar);
	// Observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewerPos[0],viewerPos[1],viewerPos[2], 0.0,0.0,0.0, 0.0,1.0,0.0);
	
	drawAxis();
	drawFence();
	
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	
}

void specialKeys(int key, int x, int y) {

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (WS, HS); 
	glutInitWindowPosition (100, 100); 
	glutCreateWindow ("Tric Trac Troi");
  
	init();
	
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display); 
	glutSpecialFunc(specialKeys);
	
	glutMainLoop();
	return 0;
}
