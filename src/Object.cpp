// Object.cpp

#include "Object.h"

Object::Object(int disp, float nx, float ny, float nz){
	displayname = disp;
	x = nx;
	y = ny;
	z = nz;
	scale = 1;
	xRot = 0;
	yRot = 0;
	zRot = 0;

}

void Object::setLocation(double nx, double ny, double nz){
	x = nx;
	y = ny;
	z = nz;
}

void Object::setScale(double nscale){
	scale = nscale;
}



void Object::draw(){
	glPushMatrix();
	glTranslated(x, y, z);
	glRotated(zRot, 0, 0, 1);
	glRotated(yRot, 0, 1, 0);
	glRotated(xRot, 1, 0, 0);
	glScaled(scale, scale, scale);
	glCallList(displayname);
	glPopMatrix();
}
