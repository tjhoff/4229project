#ifndef HEIGHTMAP
	#define HEIGHTMAP

#include "Vec3.h"
#include <iostream>

class Heightmap{
	public:
	
		Heightmap(float ** heightVals, int iwidth, int iheight, float vScale, float offx, float offz);
		float getYValue(float x, float z);
	private:
		void calcSlope(float * yVals, Vec3 &slope);
		Vec3 ** slopes;
		float ** baseHeights;
		float scale; 
		int width;
		int height;
		float xOffset;
		float zOffset;
		
};
#endif
