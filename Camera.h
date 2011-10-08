#ifndef GL
	#define GL
	#define PI 3.14159265
	#include <GL/glut.h>
	#include <math.h>
#endif

class Camera{
	public:
		Camera();
		void hRotate(float amount);
		void vRotate(float amount);
		void move(float x, float y, float z);
		void move(float loc[3]);
		void setZoom(float amount);
		void cameraTransform();
	private:
		float camX;
		float camY;
		float camZ;
		float hRot;
		float vRot;
		float zoom;
};
