//Camera3d.cpp
#include "Camera3d.h"

Camera3d::Camera3d(float ax, float ay, float az){
	x = ax;
	y = ay;
	z = az;
	yaw = 0.0;
	pitch = 0.0;
	czoom = 1.0;
}

void Camera3d::transformCamera(){
	glTranslatef(x, y, z);
	glRotatef(pitch,1.0,0.0,0.0);
	glRotatef(yaw,0.0,1.0,0.0);
	glScalef(czoom,czoom,czoom);
	
	
}

void Camera3d::setZoom(float azoom){
	czoom = azoom;
}

void Camera3d::zoom(float azoom){
	czoom += azoom;
}

void Camera3d::moveTo(float ax, float ay, float az){
	x = ax;
	y = ay;
	z = az;
}

void Camera3d::move(float forward){
	x += forward * (cos(yaw*PI/180));
	y += forward * (cos(pitch*PI/180));
	z += forward * (sin(yaw*PI/180));
}

void Camera3d::rotateTo(float ayaw, float apitch){
	yaw = ayaw;
	pitch = apitch;
}

void Camera3d::rotate(float ayaw, float apitch){
	float newPitch;

	yaw += ayaw;
	if (fabs(newPitch = pitch + apitch) > 90){
		pitch = (newPitch<0)?-90:90;
	}
	else pitch += apitch;	
}
