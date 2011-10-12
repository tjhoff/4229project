//Camera3d.cpp
#include "Camera3d.h"

Camera::Camera(){
	x = 0;
	y = 0;
	z = 0;
	yaw = 0;
	pitch = 0;
	czoom = 0;
}

void Camera::transformCamera(){
	
	glRotatef(-pitch,1.0,0.0,0.0);
	glRotatef(-yaw,0.0,1.0,0.0);
	glTranslatef(-x,-y,-z);
	glScalef(czoom,czoom,czoom);
	
}

void Camera::setZoom(float azoom){
	czoom = azoom;
}

void Camera::zoom(float azoom){
	czoom += azoom;
}

void Camera::moveTo(float ax, float ay, float az){
	x = ax;
	y = ay;
	z = az;
}

void Camera::rotateTo(float ayaw, float apitch){
	yaw = ayaw;
	pitch = apitch;
}

void Camera::rotate(float ayaw, float apitch){
	float newPitch;

	yaw += ayaw;
	if (fabs(newPitch = pitch + apitch) > 90){
		pitch = (newPitch<0)?-90:90;
	}
	else pitch += apitch;	
}

Camera3d::Camera3d(float ax, float ay, float az){
	x = ax;
	y = ay;
	z = az;
	yaw = 0.0;
	pitch = 0.0;
	czoom = 1.0;
}

void Camera3d::move(float forward){
	x += forward * -(sin(yaw*PI/180));
	y += forward * (sin(pitch*PI/180));
	z += forward * -(cos(yaw*PI/180));
}

TerrainCamera::TerrainCamera(float ax, float az, Heightmap * heightMap){
	x = ax;
	z = az;
	yaw = 0.0;
	pitch = 0.0;
	czoom = 1.0;
	heightmap = heightMap;
	move(0.0);
}

void TerrainCamera::move(float forward){
	x += forward * (-sin(yaw*PI/180));
	z += forward * (-cos(yaw*PI/180));
	y = heightmap->getYValue(x,z)+.05;
}
