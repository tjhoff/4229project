//TriangleMesh.cpp
#include "TriangleMesh.h"

#define vertex(i,j) glVertex3f(tVertices[i][j].x,tVertices[i][j].y,tVertices[i][j].z)
#define color(i,j) glColor3f(tColors[i][j].x,tColors[i][j].y,tColors[i][j].z)
#define normal(i,j) glNormal3f(tNormals[i][j].x,tNormals[i][j].y,tNormals[i][j].z)


TriangleMesh::TriangleMesh(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight){

	width = vwidth;
	height = vheight;
	
	tVertices = new Vec3 * [height];
	tColors = new Vec3 * [height];
	tNormals = new Vec3 * [height];

	for(int i = 0; i < height; i++){
		tVertices[i] = new Vec3[width];
		tColors[i] = new Vec3[width];
		tNormals[i] = new Vec3[width];
		
		for(int j = 0; j<width; j++){
			tVertices[i][j] = vertices[i][j];
			tColors[i][j] = colors[i][j];
		}
	}
	
	
	computeNormals();
}

//void TriangleMesh::~TriangleMesh()

void TriangleMesh::compile(){

	
	for(int i = 0; i<height-2; i+=2){ // even rows
		glBegin(GL_TRIANGLES);
		for(int j = 0; j<width-2; j++){ //even cols

			normal(i,j);
			color(i,j);
			vertex(i,j);
			normal(i+1,j);
			color(i+1,j);
			vertex(i+1,j);
			normal(i,j+1);
			color(i,j+1);
			vertex(i,j+1);
		
		}
		for(int j = 1; j<width-2; j++){ //odd cols
		
			normal(i,j+1);
			color(i,j+1);
			vertex(i,j+1);
			normal(i+1,j);
			color(i+1,j);
			vertex(i+1,j);
			normal(i+1,j+1);
			color(i+1,j+1);
			vertex(i+1,j+1);
		
		}
		glEnd();
	}
	
	for(int i = 1; i<height-2; i+=2){ //odd rows
		glBegin(GL_TRIANGLES);
		for(int j = 0; j<width-2; j++){

			normal(i,j);
			color(i,j);
			vertex(i,j);
			normal(i+1,j);
			color(i+1,j);
			vertex(i+1,j);
			normal(i+1,j+1);
			color(i+1,j+1);
			vertex(i+1,j+1);

		}
		for(int j = 1; j<width-2; j++){
		
			normal(i,j);
			color(i,j);
			vertex(i,j);
			normal(i+1,j+1);
			color(i+1,j+1);
			vertex(i+1,j+1);
			normal(i,j+1);
			color(i,j+1);
			vertex(i,j+1);
		
		}
		glEnd();
	}

}

void TriangleMesh::computeNormals(){
	
	Vec3 v1, v2, v3;
	Vec3 u;
	Vec3 v;
	
	for(int i = 0; i<height-2; i+=2){ // even rows
		for(int j = 0; j<width-2; j+=2){ //even cols
		
			v1 = tVertices[i][j]; //top left
			v2 = tVertices[i+1][j]; //bottom left
			v3 = tVertices[i][j+1]; //top right
			
			u = v2 - v1;
			v = v3 - v1;
			
			
			tNormals[i][j].x = (u.y*v.z) - (u.z*v.y);
			tNormals[i][j].y = (u.z*v.x) - (u.x*v.z);
			tNormals[i][j].z = (u.x*v.y) - (u.y*v.x);
		}
		for(int j = 1; j<width-3; j+=2){ //odd cols
		
			v1 = tVertices[i+1][j+1]; //bottom right
			v2 = tVertices[i][j+1]; // top right
			v3 = tVertices[i+1][j]; // bottom left
			
			u = v2 - v1;
			v = v3 - v1;
			
			tNormals[i][j].x = (u.y*v.z) - (u.z*v.y);
			tNormals[i][j].y = (u.z*v.x) - (u.x*v.z);
			tNormals[i][j].z = (u.x*v.y) - (u.y*v.x);
		
		}
	}
	for(int i = 1; i<height-3; i+=2){ //odd rows
		for(int j = 0; j<width-2; j+=2){
		
			v1 = tVertices[i+1][j+1]; //bottom right
			v2 = tVertices[i][j]; // top left
			v3 = tVertices[i+1][j]; // bottom left
			
			u = v2 - v1;
			v = v3 - v1;
			
			tNormals[i][j].x = (u.y*v.z) - (u.z*v.y);
			tNormals[i][j].y = (u.z*v.x) - (u.x*v.z);
			tNormals[i][j].z = (u.x*v.y) - (u.y*v.x);
		
		}
		for(int j = 1; j<width-3; j+=2){
		
			v1 = tVertices[i][j]; // top left
			v2 = tVertices[i+1][j+1]; // bottom right
			v3 = tVertices[i][j+1]; // top right
			
			u = v2 - v1;
			v = v3 - v1;
			
			tNormals[i][j].x = (u.y*v.z) - (u.z*v.y);
			tNormals[i][j].y = (u.z*v.x) - (u.x*v.z);
			tNormals[i][j].z = (u.x*v.y) - (u.y*v.x);
		
		}
	}
	
}

/*void TriangleMesh::normal(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 * normal){

	u = v2 - v1;
	v = v3 - v1;
			
	tNormals[i][j].x = (u.y*v.z) - (u.z*v.y);
	tNormals[i][j].y = (u.z*v.x) - (u.x*v.z);
	tNormals[i][j].z = (u.x*v.y) - (u.y*v.x);

}*/
