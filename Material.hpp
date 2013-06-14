#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "resources.hpp"

class Material {
private:
	color4 ambient;
    color4 diffuse;
    color4 specular;
    color4 emission;
    GLfloat shininess;

public:
	Material(	color4 a = color4(1.0, 1.0, 1.0, 1.0), 
				color4 d = color4(1.0, 1.0, 1.0, 1.0),
				color4 s = color4(0.0, 0.0, 0.0, 1.0),
				color4 e = color4(0.0, 0.0, 0.0, 1.0),
				GLfloat sh = 0 ) :
			ambient(a),
			diffuse(d),
			specular(s),
			emission(e),
			shininess(sh)
	{}

	void apply() {
        glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, ambient.values );
        glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.values );
        glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, specular.values );
        glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, emission.values );
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, shininess );
    }	

};

#endif
