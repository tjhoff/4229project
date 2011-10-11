#include "Heightmap.h"

Heightmap::Heightmap(float ** heightVals,int width, int height, float hScale){
	scale = hScale;

	slopes = new Vec3*[height-1];
	float square[4];
	for(int i = 0; i<height-1;i++){
		slopes[i] = new Vec3[width-1];
	}
	for(int i = 0; i<height-1; i++){
		for (int j = 0; j<width-1; j++){
			square[0] = heightVals[i+1][j];
			square[1] = heightVals[i+1][j+1];
			square[2] = heightVals[i][j+1];
			square[3] = heightVals[i][j];
			calcSlope(square, slopes[i][j]);
		}
	}
}

void Heightmap::calcSlope(float * yVals, Vec3& slope){
	float x = yVals[1]-yVals[0];
	float z = yVals[3]-yVals[0];
	
	float min = yVals[0];
	float max = 0;
	
	for(int i =  0; i<4;i++){
		if (min>yVals[i]) min = yVals[i];
		if (max<yVals[i]) max = yVals[i];
	}
	
	float y = max-min;
	
	Vec3 TempVec(x,y,z);
	slope = TempVec;
}

float Heightmap::getYValue(float x, float z){
	x = x*scale; //get to appropriate scale
	z = z*scale;
	int ix = (int)x; // get integer value to grab quad
	int iz = (int)z;
	
	Vec3 slope(slopes[iz][ix]);
	
	x = x - ix;
	z = z - iz;
	
	float i = slope.x;
	float k = slope.z;
	float j = slope.y;
	
	return (-(i*x) - (k*z))/j; // formula is y = (-ix - kz)/j, where
									// i is the gradient coefficient of x,
									// j of y;
									// and k of z.
	
	
	
}
