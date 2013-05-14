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
#include "Player.hpp"
#include <math.h>

Player TicTacToeGL::p1;
Player TicTacToeGL::p2;
Player *TicTacToeGL::currPlayer;
int TicTacToeGL::mouseX;

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
	currPlayer = &p1;

	glClearColor(WHITE);
	glShadeModel(GL_SMOOTH);
	// initLights();
	initControls();
	// glEnable(GL_DEPTH_TEST);
}

void TicTacToeGL::initControls(){
	glutSpecialFunc( inputSpecialCb ); 
	glutKeyboardFunc( inputKeyboardCb );
	#ifdef __linux__
		glutMotionPassiveMotionFunc( inputMouseCb );
	#elif defined __APPLE__
		glutPassiveMotionFunc( inputMouseCb );
	#endif
}

void TicTacToeGL::inputMouseCb(int x, int y){

	printf("%d %d\n", x, mouseX);
	currPlayer->angY += (x-mouseX) * Player::sensitivity ;

	printf("%f\n", currPlayer->angY);
	glutPostRedisplay();
	mouseX = x;
}
void TicTacToeGL::inputSpecialCb(int key, int x, int y){
}
void TicTacToeGL::inputKeyboardCb(unsigned char key, int x, int y){
    switch (key) {
		case 27:
			exit(0);
		break;	
		case 'w':
			currPlayer->x += Player::velocity * sin(currPlayer->angY);
			currPlayer->z -= Player::velocity * cos(currPlayer->angY);
		break;
   	}	
	glutPostRedisplay();
}


void TicTacToeGL::display(){
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glViewport(0,0,XSCREEN, YSCREEN);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// printf(">%f\n", currPlayer->getRefX());

	gluLookAt( currPlayer->x,currPlayer->y,currPlayer->z,
			   currPlayer->getRefX(),0,currPlayer->getRefZ(),
				0,1,0);

	draw();

	glutSwapBuffers();
}

void TicTacToeGL::draw(){

 	// printf("%f\n", p1.x);

	glPushMatrix();
		glColor4f(RED);
		glutWireCube(2.0);
	glPopMatrix();
}


int main(int argc, char **argv){
	new TicTacToeGL(argc, argv);
}
