#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <math.h>
#include <vector>

#include "Fence.hpp"
#include "Surface.hpp"
#include "Player.hpp"
#include "Table.hpp"

#define RED   	 1.0, 0.0, 0.0, 1.0
#define GREEN 	 0.0, 1.0, 0.0, 1.0
#define BLUE   	 0.0, 0.0, 1.0, 1.0
#define YELLOW   1.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK	 0.0, 0.0, 0.0, 1.0

// pixels resolution of window
#define XWINDOW 800
#define YWINDOW 600

#define XWINDOW_POS 50
#define YWINDOW_POS 50

#define XWORLD 75
#define YWORLD 40
#define ZWORLD 75

#define SQUARESIZE 20.0

#define PLAYER_H 4.0

#define FENCE_W 0.75
#define FENCE_H 2.5
#define FENCE_D 0.5

#define TABLE_W 1.5
#define TABLE_H 3.0
#define TABLE_D 1.5
#define TABLE_F 0.15

#define PI    3.14159265359

// pixels resolution of screen (dynamic)
int XSCREEN;
int YSCREEN;

// Callback functions
void inputMouseCb(int x, int y);
void inputKeyboardCb(unsigned char key, int x, int y);
void display();

// Init functions
void initControls();
void initObjects();
void initLights();

// Drawing functions
void draw();
void drawAxis();
void drawFence();
void drawFloor();
void drawWalls();
void drawSky();
void drawTable();
void drawPlayers();

// Control functions
void changePlayer();
GLfloat toDeg(GLfloat rad) ;
double toRad(double);

#endif
