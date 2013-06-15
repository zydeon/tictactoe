#include "TTTGraphics.hpp"

TTTGraphics::TTTGraphics(GLfloat size_) {
	size = size_;
	board = new Surface(size, size, GLASS_BMP, Material(
														color4(1, 1, 1, 1),
														color4(1, 1, 1, 0.5)
		) ) ;
	ttt = new TicTacToe();
	loadTextures();
}

void TTTGraphics::drawGame() {
	glPushMatrix();

		glPushMatrix();
			glTranslatef(0, 0, -0.4);
			drawPiece();
		glPopMatrix();

		// Reflection
		glEnable(GL_STENCIL_TEST); 	//Activa o uso do stencil buffer
		glColorMask(0, 0, 0, 0); 	// Desenha so no stencil buffer (definir area)
		glDisable(GL_DEPTH_TEST);	// better performance
		
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 1);
		board->drawSurface();				// define area (pixels value = 1)

		glColorMask(1, 1, 1, 1);
		glEnable(GL_DEPTH_TEST);

		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_EQUAL, 1, 1);

		// replicate objects
		glPushMatrix();
			glScalef(1, 1, -1);
			glTranslatef(0, 0, -0.4);
			drawPiece();
		glPopMatrix();

		glDisable(GL_STENCIL_TEST);

		// desenhar superficie reflectora
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			board->drawSurface();
		glDisable(GL_BLEND);

		glTranslatef(-size/2,-size/2,0);
		// drawLines();
		// drawPieces();
	glPopMatrix();
}

void TTTGraphics::drawPiece(){
	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	glutWireCube(0.2);
	glEnable(GL_LIGHTING);
}

void TTTGraphics::drawLines() {
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_LINES);	
		glVertex3f(0.0, size/3, 0.0);
		glVertex3f(size, size/3, 0.0);
		
		glVertex3f(0.0, 2*size/3, 0.0);
		glVertex3f(size, 2*size/3, 0.0);
		
		glVertex3f(size/3, 0.0, 0.0);
		glVertex3f(size/3, size, 0.0);
		
		glVertex3f(2*size/3, 0.0, 0.0);
		glVertex3f(2*size/3, size, 0.0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(4.0f,0.0f); glVertex3f(size, 0.0, 0.0);
		glTexCoord2f(4.0f,1.0f); glVertex3f(size, size/10, 0.0);
		glTexCoord2f(0.0f,1.0f); glVertex3f(0.0, size/10, 0.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 9*size/10, 0.0);
		glTexCoord2f(4.0f,0.0f); glVertex3f(size, 9*size/10, 0.0);
		glTexCoord2f(4.0f,1.0f); glVertex3f(size, size, 0.0);
		glTexCoord2f(0.0f,1.0f); glVertex3f(0.0, size, 0.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 9*size/10, 0.0);
	glEnd();
}

void TTTGraphics::drawPieces() {
	int i,j, index;
	int *positions;
	GLfloat inc = size/3;
	
	positions = ttt->getPositions();
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			index = i*3+j;
			if(positions[index] != NO_MOVE) {
				glPushMatrix();
					glTranslatef(j*inc, i*inc, 0.0);
					if(positions[index] == X_MOVE) {
						drawX();
					}
					else if(positions[index] == O_MOVE) {
						drawO();
					}
				glPopMatrix();
			}
		}
	}
}

void TTTGraphics::drawX() {
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f,0.0f); glVertex3f(size/3, 0.0, 0.0);
		glTexCoord2f(1.0f,1.0f); glVertex3f(size/3, size/3, 0.0);
		glTexCoord2f(0.0f,1.0f); glVertex3f(0.0, size/3, 0.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
}

void TTTGraphics::drawO() {
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f,0.0f); glVertex3f(size/3, 0.0, 0.0);
		glTexCoord2f(1.0f,1.0f); glVertex3f(size/3, size/3, 0.0);
		glTexCoord2f(0.0f,1.0f); glVertex3f(0.0, size/3, 0.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
};

int TTTGraphics::play(bool x, int pos) {
	return ttt->play(x,pos);
}

void TTTGraphics::loadTextures() {
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(BLUE_BMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
		
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile(RED_BMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}
