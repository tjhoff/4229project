#ifndef HEIGHTMAP
#define HEIGHTMAP

#include "Vec3.h"
#include "BufferGenerator.h"

class Heightmap{
	public:
	
		Heightmap(BufferGenerator* buf, int iwidth, int iheight, float vScale, float offx, float offz);
		float getYValue(float x, float z);
	private:
		void calcSlope(float * yVals, Vec3 &slope);
		void calcBases();
		Vec3 ** slopes;
		
		BufferGenerator* bufGen;
		
		float ** baseHeights;
		float scale; 
		int width;
		int height;
		float xOffset;
		float zOffset;
		
};
#endif
