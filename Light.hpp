#ifndef LIGHT_HPP
#define LIGHT_HPP

#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

#include "resources.hpp"

class Light {
private:
    GLenum id;
    color4 ambient;
    color4 diffuse;
    color4 specular;
 
    float4 position;
    float3 spotDirection;
    float  spotExponent;
    float  spotCutOff;

    float  constantAttenuation;
    float  linearAttenuation;
    float  quadraticAttenuation;

public:
	Light( GLenum id_ 					= GL_LIGHT0
         , color4 ambient_ 				= color4( 0.0, 0.0, 0.0, 1.0 )
         , color4 diffuse_ 				= color4( 1.0, 1.0, 1.0, 1.0 )
		 , color4 specular_ 			= color4( 1.0, 1.0, 1.0, 1.0 )
		 , float4 position_ 			= float4( 0.0, 0.0, 1.0, 0.0 )  // last element is 0 if its a directional light (eg, sun)
         , float3 spotDirection_ 		= float3( 0.0, 0.0, 1.0 )
         , float  spotExponent_			= 0.0
         , float  spotCutOff_ 			= 180.0f
         , float  constantAttenuation_ 	= 1.0f
         , float  linearAttenuation_ 	= 0.05f
         , float  quadraticAttenuation_ = 0.0f )
        : id ( id_ )
        , ambient( ambient_ )
        , diffuse( diffuse_ )
        , specular( specular_ )
        , position( position_ )
        , spotDirection( spotDirection_ )
        , spotExponent( spotExponent_ )
        , spotCutOff( spotCutOff_ )
        , constantAttenuation( constantAttenuation_ )
        , linearAttenuation( linearAttenuation_ )
        , quadraticAttenuation( quadraticAttenuation_ )
    {}
 
    void enable() {
        glEnable( id );
        glLightfv( id, GL_AMBIENT, 				ambient.values );
        glLightfv( id, GL_DIFFUSE, 				diffuse.values );
        glLightfv( id, GL_SPECULAR, 			specular.values );
        glLightfv( id, GL_POSITION, 			position.values );
        glLightfv( id, GL_SPOT_DIRECTION, 		spotDirection.values );
        glLightf(  id, GL_SPOT_EXPONENT, 		spotExponent );
        glLightf(  id, GL_SPOT_CUTOFF, 			spotCutOff );
        glLightf(  id, GL_CONSTANT_ATTENUATION, constantAttenuation );
        glLightf(  id, GL_LINEAR_ATTENUATION, 	linearAttenuation );
        glLightf(  id, GL_QUADRATIC_ATTENUATION,quadraticAttenuation );
    }

    void updatePosition(float4 position_, float3 spotDirection_) {
        glLightfv( id, GL_POSITION, 		position_.values );
        glLightfv( id, GL_SPOT_DIRECTION,	spotDirection_.values );
    }    
 
    void disable(){
        glDisable( id );
    }
 


};

#endif
