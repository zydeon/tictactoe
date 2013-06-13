#include <stdio.h>
#include "lights.hpp"

void initLights(){
	// globalLightColor[0] = 1.0;
	// globalLightColor[1] = 1.0;
	// globalLightColor[2] = 1.0;
	// globalLightColor[3] = 1.0;

	printf("KASJNbdkasjdnbksajndbksajnd\n");
	// Ambiente
	// glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalLightColor);

	// // Tecto (Pontual)
	// glEnable(GL_LIGHT0);
	// GLfloat localCor[4] ={0.1, 0.1, 0.1, 1.0};
	// GLfloat localPos[4] ={xC/2, 10.0, xC/2, 1.0};//{0, xC, 0, 1.0};
	// GLfloat localCorDif[4] ={ 1, 1, 1, 1.0}; 
	// GLfloat localAttCon =1.0;
	// GLfloat localAttLin =0.05;
	// GLfloat localAttQua =0.0;	
	// glLightfv(GL_LIGHT0, GL_POSITION, localPos );
	// glLightfv(GL_LIGHT0, GL_AMBIENT, localCor );
	// glLightfv(GL_LIGHT0, GL_DIFFUSE,       localCorDif );   
	// glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
	// glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin) ;
	// glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua) ;

	// // Foco
	// glEnable(GL_LIGHT1);
	// GLfloat direccao[ ] = { sin(angY) , 0, -cos(angY)};
	// GLfloat concentracao = 128;
	// GLfloat angulo = 20.0;
	// // glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direccao );
	// glLightf (GL_LIGHT1, GL_SPOT_EXPONENT , concentracao);
	// glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, angulo);
	// GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0};
	// GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
	// GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0};
	// // GLfloat positionLight[4] ={x, y, z, 1.0};
	// // glLightfv(GL_LIGHT1, GL_POSITION, positionLight );
	// glLightfv(GL_LIGHT1, GL_AMBIENT, blackAmbientLight );
	// glLightfv(GL_LIGHT1, GL_SPECULAR, whiteSpecularLight);
	// glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteDiffuseLight);
	// // glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	// // glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05) ;
	// // glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION,0.0) ;	
}
