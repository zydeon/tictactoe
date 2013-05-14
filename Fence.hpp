#ifdef __linux__
	#include <GL/glut.h>
#elif defined __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL\glut.h>
#endif

class Fence {
	public:
		Fence(GLfloat w_, GLfloat h_, GLfloat d_);
		void drawFence();
		void drawCorner();
	private:
		GLfloat w,h,d;
};
