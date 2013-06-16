#include "TTTGraphics.hpp"
#include "resources.hpp"

TTTGraphics::TTTGraphics(GLfloat size_) {
	size = size_;
	board = new Surface(size, size, GLASS_BMP, Material(
														color4(1, 1, 1, 1),
														color4(1, 1, 1, 0.5)
		), 0.1f ) ;
	ttt = new TicTacToe();
}

void TTTGraphics::drawGame() {
	glPushMatrix();

		glPushMatrix();
			glTranslatef(0, 0, -0.4);
			drawPieces(1);
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
			drawPieces(0);
		glPopMatrix();

		glDisable(GL_STENCIL_TEST);

		// desenhar superficie reflectora
		glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			board->drawSurface();
		glDisable(GL_BLEND);

		glTranslatef(-size/2,-size/2,0);
		drawLines();
	glPopMatrix();
}

void TTTGraphics::drawLines() {
	glDisable(GL_LIGHTING);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);	
		glVertex3f(0.0, size/3, -0.01);
		glVertex3f(size, size/3, -0.01);
		
		glVertex3f(0.0, 2*size/3, -0.01);
		glVertex3f(size, 2*size/3, -0.01);
		
		glVertex3f(size/3, 0.0, -0.01);
		glVertex3f(size/3, size, -0.01);
		
		glVertex3f(2*size/3, 0.0, -0.01);
		glVertex3f(2*size/3, size, -0.01);
	glEnd();
	glEnable(GL_LIGHTING);
}

void TTTGraphics::drawPieces(char lightsOn) {
	int i,j, index;
	int *positions;
	GLfloat inc = size/3;
	
	positions = ttt->getPositions();
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++) {
			index = i*3+j;
			if(positions[index] != NO_MOVE) {
				glPushMatrix();
					glTranslatef((j-1)*inc, (i-1)*inc, 0.0);
					color4 color = positions[index] == X_MOVE ? color4(1,0,0,1) : color4(0,0,1,1);
					pieces[index].draw(color, lightsOn);
				glPopMatrix();
			}
		}
	}
}

void TTTGraphics::updatePieces() {
	int i;
	for( i = 0; i < 9; ++i ){
		pieces[i].update();
	}
}

int TTTGraphics::play(bool x, int pos) {
	return ttt->play(x,pos);
}
