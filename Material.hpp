#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

class Material {
private:
	color4 ambient;
    color4 diffuse;
    color4 specular;
    color4 emission;
    GLfloat shininess;

public:
	Material(color4 a, color4 d, color4 s, color4 e, color4 sh) :
			ambient(a),
			diffuse(d),
			specular(s),
			emission(e),
			shininess(sh)
	{}

};

#endif
