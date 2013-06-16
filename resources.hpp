#ifndef RESOURCES_HPP
#define RESOURCES_HPP

// facilitar passagem por parametro
class color4{
public:
	GLfloat values[4];
	color4(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
		values[0] = r;
		values[1] = g;
		values[2] = b;
		values[3] = a;
	}
};

class float4{
public:
	GLfloat values[4];
	float4(GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4){
		values[0] = f1;
		values[1] = f2;
		values[2] = f3;
		values[3] = f4;
	}
};

class float3{
public:
	GLfloat values[3];
	float3(GLfloat f1, GLfloat f2, GLfloat f3){
		values[0] = f1;
		values[1] = f2;
		values[2] = f3;
	}
};

#endif
