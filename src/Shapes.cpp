#include "Shapes.h"
void cylinder(int segments){
	int step = 360/segments;
	glBegin(GL_QUADS);
	for (int i = -step; i<360; i+=step){

		double rad = radians(i);
		double rad2 = radians(i+step);
		glNormal3f((cos(rad) +cos(rad2))/2.0, 0.0,(sin(rad) +sin(rad2))/2.0);
		glVertex3f(cos(rad), 0.0, sin(rad));
		glVertex3f(cos(rad), 1.0, sin(rad));
		glVertex3f(cos(rad2), 1.0, sin(rad2));
		glVertex3f(cos(rad2), 0.0, sin(rad2));

	}
	glEnd();

}

void cone(int segments){

	int step = 360/segments;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = -step; i<360; i+=step){
		double rad = radians(i);
		double rad2 = radians(i+step);
		glNormal3f((cos(rad) +cos(rad2))/2.0, 0.5,(sin(rad) +sin(rad2))/2.0);
		glVertex3f(cos(rad), 0.0, sin(rad));
		glVertex3f(0,1,0);
	}
	glEnd();


}

void tree(){
	glScalef(.4,.4,.4);
	glPushMatrix();
	glScalef(.1,1.0,.1);
	glColor3f(.6,.4,.5);
	cylinder(36);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,1,0);
	glScalef(.1,1,.1);
		
	cone(36);
	glPopMatrix();
	int branches = rand()%8;
		
	for (int i = 0; i<branches+1; i++) treeRecurse(0);


}

void treeRecurse(int level){
	if (level > 4) return;
	int branches = rand()%2;
	if (level > 3) branches = 0;
	
	
	float rpos = (rand()%50)/100.0 + .5;
	float rrot = (rand()%1500)/20.0 - 25 ;
	float ryrot = (rand()%1800)/10.0;
	glPushMatrix();
	glTranslatef(0,rpos,0);
	
	glRotatef(ryrot, 0,1,0);
	glRotatef(rrot,0,0,1);
	glScalef(.7,.8,.7);

	for (int i = 0; i<branches+1; i++) treeRecurse(level+1);
	glPopMatrix();
	
	
	glPushMatrix();
	glScalef(.1,1.0,.1);
	glColor3f(.6,.4 + ((float)level/12),.5);
	cylinder(36);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,1,0);
	glScalef(.1,1,.1);
	cone(36);
	glPopMatrix();

}