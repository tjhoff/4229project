#include "Heightmap.h"

Heightmap::Heightmap(TriangleMesh * mesh,int iwidth, int iheight, float hScale, float offx = 0.0, float offz = 0.0){
	
	tMesh = mesh;
	
	qDebug() << offx << offz;
	
	scale = hScale;
	width = iwidth;
	height = iheight;
	xOffset = offx;
	zOffset = offz;
	baseHeights = new float*[height];
	for(int i = 0; i<height;i++){
		baseHeights[i] = new float[width];
	}
	calcBases();
}

void Heightmap::calcBases()
{
	for(int i = 0; i<height; i++){
		for(int j = 0; j<width; j++){
			baseHeights[i][j] = tMesh->tVertices[i][j].y;
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
	x = fabs(x);
	z = fabs(z);
	int ix = (int)x; // get integer value to grab quad
	int iz = (int)z;
	
	if ((ix>=width)||(ix<0)||(iz>=height)||(iz<0)) return .5; // if out of bounds
	
	//Vec3 slope(slopes[iz][ix]); // get the slope vector
	return baseHeights[iz][ix]; // get the base height of v[0]
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
