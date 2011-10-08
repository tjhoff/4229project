#include "Camera.h"

Camera::Camera(){
		camX = 0.0;
		camY = 0.0;
		camZ = 0.0;
		hRot = 0.0;
		vRot = 0.0;
		zoom = 1.0;
}

void Camera::hRotate(float amount){
	hRot += amount;
}

void Camera::vRotate(float amount){
	vRot += amount;
}

void Camera::move(float x, float y, float z){
	camX=x;
	camY=y;
	camZ=z;
}

void Camera::move(float loc[3]){
	camX=loc[0];
	camY=loc[1];
	camZ=loc[2];
}


void Camera::setZoom(float amount){
	zoom = amount;
}

void Camera::cameraTransform(){
	gluLookAt(camX+2*sin(hRot*PI/180), camY+1.5, camZ+2*cos(hRot*PI/180), camX, camY, camZ, 0.0,1.0,0.0); 
	glScalef(zoom, zoom, zoom);
}
