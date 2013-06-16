#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <math.h>
#include <vector>

#include "Fence.hpp"
#include "Surface.hpp"
#include "Player.hpp"
#include "Table.hpp"
#include "resources.hpp"

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

#define XWORLD 50
#define YWORLD 26
#define ZWORLD 50

#define SQUARESIZE 20.0

#define PLAYER_H 4.0

#define TABLE_W 1.5
#define TABLE_H 3.0
#define TABLE_D 1.5
#define TABLE_F 0.15

#define TIMER_MSEC 25

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
void initFog();

// Drawing functions
void draw();
void drawAxis();
void drawFence();
void drawFloor();
void drawWalls();
void drawSky();
void drawGame();
void drawPlayers();

// Control functions
void changePlayer();
void checkCollisions();
void update(int v);
void enableLights();

// Help functions
GLfloat toDeg(GLfloat rad) ;
double toRad(double);
double distance_(float3 p1, float3 p2);

#endif
