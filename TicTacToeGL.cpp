#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include <stdio.h>
#include "TicTacToeGL.hpp"
#include "Player.hpp"

Player TicTacToeGL::p1;
Player TicTacToeGL::p2;
Player *TicTacToeGL::currPlayer;

TicTacToeGL::TicTacToeGL(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (XSCREEN, YSCREEN); 
	glutInitWindowPosition (0, 0); 
	glutCreateWindow ("Tic Tac Toe");

	
 	printf("%f\n", p1.x);


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
	#ifdef __linux__
		glutMotionPassiveMotionFunc( inputMouseCb );
	#elif defined __APPLE__
		glutPassiveMotionFunc( inputMouseCb );
	#endif
}

void TicTacToeGL::inputMouseCb(int x, int y){
}
void TicTacToeGL::inputSpecialCb(int key, int x, int y){
}
void TicTacToeGL::inputKeyboardCb(int key, int x, int y){
}


void TicTacToeGL::display(){
	glViewport(0,0,XSCREEN, YSCREEN);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 0.1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,20, 0,0,0, 0,1,0);

	draw();

	glutSwapBuffers();
}

void TicTacToeGL::draw(){
 	glClear(GL_COLOR_BUFFER_BIT);

 	// printf("%f\n", p1.x);

	glPushMatrix();
		glColor4f(RED);
		glutSolidCube(1.0);
	glPopMatrix();
}


int main(int argc, char **argv){
	new TicTacToeGL(argc, argv);
}
