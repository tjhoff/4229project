#ifndef HEIGHTMAP
	#define HEIGHTMAP

#include "Global.h"
#include "Vec3.h"
#ifndef TRIANGLEMESH
#include "TriangleMesh.h"
#endif
class Heightmap{
	public:
	
		Heightmap(TriangleMesh * mesh, int iwidth, int iheight, float vScale, float offx, float offz);
		float getYValue(float x, float z);
	private:
		void calcSlope(float * yVals, Vec3 &slope);
		void calcBases();
		Vec3 ** slopes;
		
		TriangleMesh * tMesh;
		
		float ** baseHeights;
		float scale; 
		int width;
		int height;
		float xOffset;
		float zOffset;
		
};
#endif
