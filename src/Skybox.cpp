#include "Skybox.h"
#define val 15
#define a glVertex3f(val, val, val)
#define b glVertex3f(-val, val, val)
#define c glVertex3f(-val, -val, val)
#define d glVertex3f(val, -val, val)

#define e glVertex3f(val, val, -val)
#define f glVertex3f(val, -val, -val)
#define g glVertex3f(-val, -val, -val)
#define h glVertex3f(-val, val, -val)


Skybox::Skybox(){
	
	//definitively a skybox

}

void Skybox::draw(){
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
		glColor3f(.5,.5,1.0);
		b;a;
		glColor3f(.4,.4,.6);
		d;c;
		
		glColor3f(.5,.5,1.0);
		a;e;
		glColor3f(.4,.4,.6);
		f;d;

		glColor3f(.5,.5,1.0);
		e;h;
		glColor3f(.4,.4,.6);
		g;f;

		glColor3f(.5,.5,1.0);
		a;e;
		glColor3f(.4,.4,.6);
		f;d;

		glColor3f(.5,.5,1.0);
		h;b;
		glColor3f(.4,.4,.6);
		c;g;

		glColor3f(.5,.5,1.0);
		e;a;b;h;
	glEnd();
	glEnable(GL_LIGHTING);
}

