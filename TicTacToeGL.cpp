#include "TicTacToeGL.hpp"
#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

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
	glClearColor(WHITE);
	gluOrtho2D(-50, 50, -50, 50);		//....	Definicao sistema coordenadas area de desenho
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
 	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor4f(YELLOW);
	glBegin(GL_QUADS);
		glVertex2f(-25.0f, -25.0f);
        glVertex2f(-25.0f,  25.0f);
        glVertex2f( 25.0f,  25.0f);
		glVertex2f( 25.0f, -25.0f);               
    glEnd();

	/*glPushMatrix();
		glColor4f(YELLOW);
		glutSolidSphere(10, 250, 250);
	glPopMatrix();*/

    glutPostRedisplay();
	glutSwapBuffers();
}


int main(int argc, char **argv){
	TicTacToeGL *t = new TicTacToeGL(argc, argv);
}
