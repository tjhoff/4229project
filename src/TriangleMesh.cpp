//TriangleMesh.cpp
#include "TriangleMesh.h"

#define vertex(i,j) glVertex3f(tVertices[i][j].x,tVertices[i][j].y,tVertices[i][j].z)
#define color(i,j) glColor3f(1.0, 1.0, 1.0)
#define normal(i,j) glNormal3f(tNormals[i][j].x,tNormals[i][j].y,tNormals[i][j].z)
#define tex(i,j) glTexCoord3f((double)i/width, heightmap[i][j], (double)j/height); qDebug() << i << width << (double)i/width << "...";

#define ColNormVex(i,j)   normal(i,j); color(i,j); tex(i,j); vertex(i,j)

TriangleMesh::TriangleMesh(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight){

	width = vwidth;
	height = vheight;
	
	tVertices = new Vec3 * [height];
	tColors = new Vec3 * [height];
	tNormals = new Vec3 * [height];
	
	heightmap = new float*[height];

	for(int i = 0; i < height; i++){
		tVertices[i] = new Vec3[width];
		tColors[i] = new Vec3[width];
		tNormals[i] = new Vec3[width];
		heightmap[i] = new float[width];
		
		for(int j = 0; j<width; j++){
			tVertices[i][j] = vertices[i][j];
			tColors[i][j] = colors[i][j];
			heightmap[i][j] = vertices[i][j].y;
		}
	}
	double start_time = clock()/1000;
	computeNormals();
	qDebug()<<"Calculating normals took "<< clock()/1000 - start_time << "mirriseconds";
	
}

void TriangleMesh::compile(){
	double start_time = clock()/1000;
	int count = 0;
	
	TerrainTexture* tex = new TerrainTexture(heightmap, width, height);
	GLuint tex_id = tex->texture();
	int tex_width = tex->tex_width();
	int tex_height = tex->tex_height();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_QUADS);
	for(int i = 0; i<height-1; i++)
	{ 
		for(int j = 0; j<width-1; j++)
		{ 
			glNormal3f(tNormals[i][j].x,tNormals[i][j].y,tNormals[i][j].z);
			glTexCoord3f((double)i/height, (double)j/width, heightmap[i][j]);
			glVertex3f(tVertices[i][j].x,tVertices[i][j].y,tVertices[i][j].z);
			
			glNormal3f(tNormals[i+1][j].x,tNormals[i+1][j].y,tNormals[i+1][j].z);
			glTexCoord3f((double)(i+1)/height, (double)j/width, heightmap[i+1][j+1]);
			glVertex3f(tVertices[i+1][j].x,tVertices[i+1][j].y,tVertices[i+1][j].z);
			
			glNormal3f(tNormals[i+1][j+1].x,tNormals[i+1][j+1].y,tNormals[i+1][j+1].z);
			glTexCoord3f((double)(i+1)/height, (double)(j+1)/width, heightmap[i+1][j+1]);
			glVertex3f(tVertices[i+1][j+1].x,tVertices[i+1][j+1].y,tVertices[i+1][j+1].z);
			
			glNormal3f(tNormals[i][j+1].x,tNormals[i][j+1].y,tNormals[i][j+1].z);
			glTexCoord3f((double)i/height, (double)(j+1)/width, heightmap[i][j+1]);
			glVertex3f(tVertices[i][j+1].x,tVertices[i][j+1].y,tVertices[i][j+1].z);
			
		} 
	}
	
	
	glEnd();
	
	qDebug()<<"Compiling displays took "<< clock()/1000 - start_time<< "parsecs";

}

void TriangleMesh::computeNormals(){
	
	Vec3 v1, v2, v3;
	
	Vec3 n1, n2;
	
	Vec3 u;
	Vec3 v;
	
	float x1,y1, z1;
	
	/////////////// DO FOR i=0 j=0	
	v1 = tVertices[0][0]; //
	v2 = tVertices[1][0]; // 
	v3 = tVertices[1][1]; //
		
	u = v2 - v1;
	v = v3 - v1;
		
	tNormals[0][0].x = (u.y*v.z) - (u.z*v.y);
	tNormals[0][0].y = (u.z*v.x) - (u.x*v.z);
	tNormals[0][0].z = (u.x*v.y) - (u.y*v.x);
	////////////////////////////////
	

	for(int j = 1;j<width-1;j++){
	
		//////////// FOR i=0
		v1 = tVertices[0][j]; //
		v2 = tVertices[0][j-1]; // 
		v3 = tVertices[1][j]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[0][j]; //
		v2 = tVertices[1][j]; // 
		v3 = tVertices[0][j+1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[0][j].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[0][j].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[0][j].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
		////////////////////
	}

	////////////// i = 0, j = width-1		
	v1 = tVertices[0][width-1]; //
	v2 = tVertices[0][width-2]; // 
	v3 = tVertices[1][width-1]; //
			
	u = v2 - v1;
	v = v3 - v1;
			
	x1 = (u.y*v.z) - (u.z*v.y);
	y1 = (u.z*v.x) - (u.x*v.z);
	z1 = (u.x*v.y) - (u.y*v.x);
				
	tNormals[0][width-1].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
	tNormals[0][width-1].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
	tNormals[0][width-1].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
	//////////////////////////

	for(int i = 1; i<height-1; i++){ 

		//////////// DO FOR j = 0
		v1 = tVertices[i][0]; //
		v2 = tVertices[i+1][0]; // 
		v3 = tVertices[i][1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[i][0]; //
		v2 = tVertices[i][1]; // 
		v3 = tVertices[i-1][0]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[i][0].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[i][0].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[i][0].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
				
		//////////////////////////

		for (int j = 1; j<width-1; j++){

			///// BASE CASE //////
			
			v1 = tVertices[i-1][j]; //
			v2 = tVertices[i][j-1]; //
			v3 = tVertices[i+1][j]; //
			
			u = v2 - v1;
			v = v3 - v1;
			
			x1 = (u.y*v.z) - (u.z*v.y);
			y1 = (u.z*v.x) - (u.x*v.z);
			z1 = (u.x*v.y) - (u.y*v.x);
			
			v1 = tVertices[i-1][j]; //
			v2 = tVertices[i+1][j]; // 
			v3 = tVertices[i][j+1]; // 
			
			u = v2 - v1;
			v = v3 - v1;
			
			tNormals[i][j].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
			tNormals[i][j].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
			tNormals[i][j].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
			////////////////////
			
		}
		////////////// j = width-1
		v1 = tVertices[i][width-1]; //
		v2 = tVertices[i-1][width-1]; // 
		v3 = tVertices[i][width-2]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[i][width-1]; //
		v2 = tVertices[i][width-2]; // 
		v3 = tVertices[i+1][width-1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[i][width-1].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[i][width-1].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[i][width-1].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
				
	}

	///////////////// for i = height-1, j = 0;
	v1 = tVertices[height-1][0]; //
	v2 = tVertices[height-1][1]; // 
	v3 = tVertices[height-2][0]; //
			
	u = v2 - v1;
	v = v3 - v1;
			
	x1 = (u.y*v.z) - (u.z*v.y);
	y1 = (u.z*v.x) - (u.x*v.z);
	z1 = (u.x*v.y) - (u.y*v.x);
			
	tNormals[height-1][0].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
	tNormals[height-1][0].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
	tNormals[height-1][0].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
	//////////////////////////


	for(int j =1; j<width-1;j++){
		////////////////// for i = height-1
		v1 = tVertices[height-1][j]; //
		v2 = tVertices[height-2][j]; // 
		v3 = tVertices[height-1][j-1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[height-1][j]; //
		v2 = tVertices[height-1][j+1]; // 
		v3 = tVertices[height-2][j]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[height-1][j].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[height-1][j].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[height-1][j].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
		////////////////////////
	}
	//////////////// for i = height-1, j = width -1
	v1 = tVertices[height-1][width-1]; //
	v2 = tVertices[height-2][width-1]; // 
	v3 = tVertices[height-1][width-2]; //
			
	u = v2 - v1;
	v = v3 - v1;
			
	tNormals[height-1][width-1].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
	tNormals[height-1][width-1].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
	tNormals[height-1][width-1].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
				
	/////////////////////////////////////
}

