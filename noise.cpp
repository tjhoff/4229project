#include <time.h>

#include <math.h>
#ifndef PI
	#define PI 3.1415927
#endif

float noise(int x, int y){
	int n = x + y * 57;
    n = (n<<13) ^ n;
    return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

float linInterp(float a, float b, float x){
	return a*(1-x) + b*x;
}

float cosInterp(float a, float b, float x){
	float ft = x*PI;
	float f = (1-cos(ft))*.5;
	return a*(1-f)+(b*f);
}

float smoothNoise(float x, float y){
	float corners = (noise(x-1,y-1)+noise(x+1,y-1)+noise(x-1,y+1) + noise(x+1,y+1))/16;
	float sides = (noise(x-1,y) + noise(x+1,y) + noise(x,y-1) + noise(x,y+1))/8;
	float center = noise(x,y)/4;
	
	return corners+sides+center;
}

float interpNoise(float x, float y){

	int ix = (int)x;
	x = x-ix;
	int iy=(int)y;
	y = y-iy;
	
	float v1 = smoothNoise(ix, iy);
	float v2 = smoothNoise(ix+1,iy);
	float v3 = smoothNoise(ix,iy+1);
	float v4 = smoothNoise(ix+1,iy+1);
	
	float i1 = cosInterp(v1, v2, x);
	float i2 = cosInterp(v3, v4, x);
	
	return cosInterp(i1, i2, iy);

}

float perlin(float x, float y){

	float total = 0;
	float persistence = 10.0;
	int octaves = 4;
	float frequency;
	float amplitude;
	for (int i = 0; i<octaves; i++){
		frequency = pow(2,i);
		amplitude = pow(persistence,i);
		total+= interpNoise(x*frequency, y*frequency) * amplitude;
	}
	return total;
}

int main(){

}


