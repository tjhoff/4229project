#include "Vec3.h"

class Heightmap{
	public:
	
		Heightmap(float ** heightVals, int width, int height, float vScale);
		float getYValue(float x, float z);
	private:
		void calcSlope(float * yVals, Vec3 &slope);
		Vec3 ** slopes;
		float scale; 
		
};
