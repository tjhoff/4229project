#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <new>
#include <iostream>
#define PI 3.141592653589793

float frand(){
	return (float)rand()/(float)RAND_MAX;
}

float ** makeUniform(int width, int height){
	float ** noise = new float*[height];
	for(int i = 0; i<height; i++) noise[i] = new float[width];
	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			noise[i][j] = frand();
		}
	}
	return noise;
}

int * sample_points(int x, int t, int max_x){
	int * ret = new int[3];
	ret[0] = (floor(x/t*t));
	ret[1] = (ret[0] + t) % max_x;
	ret[2] = (x - ret[0]) / t;
	return ret;
}

float ** cosine_interpolation(int k,int width, int height){
	int t = pow(2,k);
	float ** noise = makeUniform(width,height);
	float ** smoothNoise = new float*[height];
	for(int i = 0; i<height; i++) smoothNoise[i] = new float[width];
	int x0,x1,y0,y1;
	float x_alpha, y_alpha;

	float a0, a1;
	int * ret;
	for(int i = 0; i<width; i++){
		ret=sample_points(i,t,width);
		x0 = ret[0];x1 = ret[1]; x_alpha = ret[2];
		x_alpha = (1-cos(x_alpha*PI))/2;
		for(int j = 0; j<width; j++){
			ret = sample_points(j,t,height);
			y0=ret[0];y1=ret[1];y_alpha=ret[2];
			y_alpha = (1-cos(y_alpha*PI))/2;
			
			a0 = (1-x_alpha)*(noise[x0][y0]) + (x_alpha)*(noise[x1][y0]);
			a1 = (1-x_alpha)*(noise[x0][y1]) + (x_alpha)*(noise[x1][y1]);
			
			smoothNoise[i][j] = (1-y_alpha)*a0+(y_alpha)*a1;
			
		}
		
	}
	return smoothNoise;
}

float ** perlinFromSmooth(int width,int height,int layers,float falloff, bool normalize){
	
	float ** perlinNoise = new float*[height];
	for(int i = 0; i<height; i++) perlinNoise[i] = new float[width];
	for(int i = 0; i<height; i++){
		for(int j=0; j<width; j++){
			perlinNoise[i][j] = 0;
		}
	}
	float r = 1;
	float ** sNoise;
	for(int k = 0; k<layers;k++){
		r=r*falloff;
		sNoise = cosine_interpolation(layers-k-1,width,height);
		for(int i = 0; i<height; i++){
			for(int j=0; j<width; j++){
				perlinNoise[i][j] += sNoise[i][j]*r;
			}
		}
	}
	
	if (!normalize) return perlinNoise;
	
	r = 1;
	float w = 1;
	
	for(int k = 0; k<layers;k++){
		r = r* falloff;
		w+=r;
	}
	for(int i = 0; i<height; i++){
		for(int j=0; j<width; j++){
			perlinNoise[i][j] = perlinNoise[i][j]/w;
		}
	}
	
	return perlinNoise;
}

float ** perlin_noise(int width, int height, int layers, float falloff){

	float ** p;
	p = perlinFromSmooth(width, height, layers, falloff, true);
	return p;

}

int main(int argc, char* argv[]){

	srand(time(NULL));
	int height = 100;
	int width = height;
	float ** p;
	p = perlin_noise(width, height, 1,.5);
}
