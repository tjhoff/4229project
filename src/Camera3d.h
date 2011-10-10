// Camera3d.h

#include <GL/glut.h>
#include <math.h>
#ifndef PI
#define PI 3.141592653589793
#endif

class Camera3d{

	public:
		Camera3d(float ax, float ay, float az);
		void transformCamera();
		void setZoom(float azoom);
		void zoom(float azoom);
		void moveTo(float ax, float ay, float az);
		void move(float forward);
		void rotateTo(float ayaw, float apitch);
		void rotate(float ayaw, float apitch);
	private:
	
		
		float x;
		float y;
		float z;
		float yaw;
		float pitch;
		float czoom;
};

