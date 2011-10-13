#include "Heightmap.h"

Heightmap::Heightmap(float ** heightVals,int iwidth, int iheight, float hScale, float offx = 0.0, float offz = 0.0){
	scale = hScale;
	width = iwidth;
	height = iheight;
	xOffset = offx;
	zOffset = offz;
	baseHeights = new float*[height-1];
	for(int i = 0; i<height-1;i++){
		baseHeights[i] = new float[width-1];
	}
	slopes = new Vec3*[height-1];
	float square[4];
	for(int i = 0; i<height-1;i++){
		slopes[i] = new Vec3[width-1];
	}
	for(int i = 0; i<height-1; i++){
		for (int j = 0; j<width-1; j++){
			baseHeights[i][j] = square[0];
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
	y = (y==0)?1:y;
	Vec3 TempVec(x,y,z);
	slope = TempVec;
}

float Heightmap::getYValue(float x, float z){
	
	x = (x-xOffset)/scale; //get to appropriate offset, then scale
	z = (z-zOffset)/scale;
	
	
	
	int ix = (int)x; // get integer value to grab quad
	int iz = (int)z;
	
	if ((ix>=width)||(ix<0)||(iz>=height)||(iz<0)) return .5; // if out of bounds
	
	Vec3 slope(slopes[iz][ix]); // get the slope vector
	float base = baseHeights[iz][ix]; // get the base height of v[0]
	return base;
	/*x = x - ix; // get floating-point remainders
	z = z - iz;
	
	float i = slope.x; // coefficients of slope
	float k = slope.z;
	float j = slope.y;
	*/
	//return base+((-(i*x) - (k*z))/j)*scale/2; // formula is y = (-ix - kz)/j, where
									// i is the gradient coefficient of x,
									// j of y;
									// and k of z.
	
	
	
}
