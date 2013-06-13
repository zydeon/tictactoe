#ifndef LIGHTS_HPP
#define LIGHTS_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

GLfloat globalLightColor[4];

void initLights(void);

#endif