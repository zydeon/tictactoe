#include "Player.hpp"
#include "TicTacToeGL.hpp"
#include <math.h>

Player::Player(){
	this->x = 1.0;
	this->y = 0.0;
	this->z = 5.0;

	this->angX = 0.0;
	this->angY = 0.0;

}


GLfloat Player::getRefX(){
	return this->x + sin(angY) * 0.01f;
}
GLfloat Player::getRefZ(){
	return this->z - cos(angY) * 0.01f;
}
