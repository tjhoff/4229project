// Camera3d.h

#include <QtOpenGL>
#include <math.h>
#include <iostream>

#ifndef PI
#define PI 3.141592653589793
#endif

#include "Map.h"
#include "Heightmap.h"

class Camera{
	public:
		Camera();
		void transformCamera();
		void setZoom(float azoom);
		void zoom(float azoom);
		void moveTo(float ax, float ay, float az);
		virtual void move(float forward){forward = forward;};
		void rotateTo(float ayaw, float apitch);
		void rotate(float ayaw, float apitch);	
		float x;
		float y;
		float z;
		float yaw;
		float pitch;
		float czoom;
};

class Camera3d: public Camera{

	public:
		Camera3d(float ax, float ay, float az, Map *nmap);
		void move(float forward);
		Map * map;
		int chunkx;
		int chunkz;
};

class TerrainCamera: public Camera{

	public:
		TerrainCamera(float ax, float az, Heightmap * heightMap, Map * m_map);
		void move(float forward);
		Heightmap * heightmap;
		Map * map;
	public:
		int chunkx;
		int chunkz;
		
};

