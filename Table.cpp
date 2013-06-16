#include "Table.hpp"

Table::Table(GLfloat width_, GLfloat height_, GLfloat depth_) {
	width = width_;
	height = height_;
	depth = depth_;
	feetSurface = new Surface(feetWidth, height, TABLE_BMP, Material(), 0.1f);
	game = new TTTGraphics(width_);
}

void Table::drawTable() {
	int i;
	// draw foots
	for( i = 0; i < 4; ++i ){
		glTranslatef(width/2, 0, -depth/2);
		drawFoot();
		glTranslatef(-width/2, 0, depth/2);
		glRotatef(-90, 0, 1, 0);
	}

	glPushMatrix();
		glTranslatef(0,height/2,0);
		glRotatef(90, 1, 0, 0);
			game->drawGame();
	glPopMatrix();
}

void Table::drawFoot() {
	int i;
	glPushMatrix();
	for( i = 0; i < 4; ++i ){
		glTranslatef(0, 0, -1*feetWidth/2);
		feetSurface->drawSurface();
		glTranslatef(0, 0, feetWidth/2);
		glRotatef(-90, 0, 1, 0);
	}
	glPopMatrix();
}

int Table::makeMove(bool playerX, int pos) {
	return game->play(playerX,pos);
}
