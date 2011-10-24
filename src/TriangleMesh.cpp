//TriangleMesh.cpp
#include "TriangleMesh.h"

#define vertex(i,j) glVertex3f(tVertices[i][j].x,tVertices[i][j].y,tVertices[i][j].z)
#define color(i,j) glColor3f(1.0, 1.0, 1.0)
#define normal(i,j) glNormal3f(tNormals[i][j].x,tNormals[i][j].y,tNormals[i][j].z)

#define ColNormVex(i,j)   normal(i,j); color(i,j); vertex(i,j)

TriangleMesh::TriangleMesh(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight){

	width = vwidth;
	height = vheight;
	
	tVertices = new Vec3 * [height];
	tColors = new Vec3 * [height];
	tNormals = new Vec3 * [height];
	
	heightmap = new float*[height];

	for(int iz = 0; iz < height; iz++){
		tVertices[iz] = new Vec3[width];
		tColors[iz] = new Vec3[width];
		tNormals[iz] = new Vec3[width];
		heightmap[iz] = new float[width];
		
		for(int ix = 0; ix<width; ix++){
			tVertices[iz][ix] = vertices[iz][ix];
			tColors[iz][ix] = colors[iz][ix];
			heightmap[iz][ix] = vertices[iz][ix].y;
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

	for(int iz = 0; iz<height-1; iz++){ 
		glBegin(GL_TRIANGLES);
		for(int ix = 0; ix<width-2; ix+=2){ 
			switch (count){
				case 0:
					glTexCoord2f((double)(iz)/height, (double)(ix)/width);
					ColNormVex(iz,ix);
					glTexCoord2f((double)(iz+1)/height, (double)(ix)/width);
					ColNormVex(iz+1,ix);
					glTexCoord2f((double)(iz)/height, (double)(ix+1)/width);
					ColNormVex(iz,ix+1);

					glTexCoord2f((double)(iz)/height, (double)(ix+1)/width);
					ColNormVex(iz,ix+1);
					glTexCoord2f((double)(iz+1)/height, (double)(ix)/width);
					ColNormVex(iz+1,ix);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+1)/width);
					ColNormVex(iz+1,ix+1);
					
					glTexCoord2f((double)(iz)/height, (double)(ix+1)/width);
					ColNormVex(iz,ix+1);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+1)/width);
					ColNormVex(iz+1,ix+1);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+2)/width);
					ColNormVex(iz+1,ix+2);
					
					glTexCoord2f((double)(iz)/height, (double)(ix+1)/width);
					ColNormVex(iz,ix+1);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+2)/width);
					ColNormVex(iz+1,ix+2);
					glTexCoord2f((double)(iz)/height, (double)(ix+2)/width);
					ColNormVex(iz,ix+2);
					break;
				case 1:
					glTexCoord2f((double)(iz)/height, (double)(ix)/width);
					ColNormVex(iz,ix);
					glTexCoord2f((double)(iz+1)/height, (double)(ix)/width);
					ColNormVex(iz+1,ix);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+1)/width);
					ColNormVex(iz+1,ix+1);
					
					glTexCoord2f((double)(iz)/height, (double)(ix)/width);
					ColNormVex(iz,ix);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+1)/width);
					ColNormVex(iz+1,ix+1);
					glTexCoord2f((double)(iz)/height, (double)(ix+1)/width);
					ColNormVex(iz,ix+1);

					glTexCoord2f((double)(iz)/height, (double)(ix+1)/width);
					ColNormVex(iz,ix+1);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+1)/width);
					ColNormVex(iz+1,ix+1);
					glTexCoord2f((double)(iz)/height, (double)(ix+2)/width);
					ColNormVex(iz,ix+2);
					
					glTexCoord2f((double)(iz+1)/height, (double)(ix+1)/width);
					ColNormVex(iz+1,ix+1);
					glTexCoord2f((double)(iz+1)/height, (double)(ix+2)/width);
					ColNormVex(iz+1,ix+2);
					glTexCoord2f((double)(iz)/height, (double)(ix+2)/width);
					ColNormVex(iz,ix+2);
					break;
			}


		
		} // end ix
		count = !count;
		glEnd();
	} // end iz
	
}

void TriangleMesh::computeNormals(){
	
	Vec3 v1, v2, v3;
	
	Vec3 n1, n2;
	
	Vec3 u;
	Vec3 v;
	
	float x1,y1, z1;
	
	/////////////// DO FOR iz=0 ix=0	
	v1 = tVertices[0][0]; //
	v2 = tVertices[1][0]; // 
	v3 = tVertices[1][1]; //
		
	u = v2 - v1;
	v = v3 - v1;
		
	tNormals[0][0].x = (u.y*v.z) - (u.z*v.y);
	tNormals[0][0].y = (u.z*v.x) - (u.x*v.z);
	tNormals[0][0].z = (u.x*v.y) - (u.y*v.x);
	////////////////////////////////
	

	for(int ix = 1;ix<width-1;ix++){
	
		//////////// FOR iz=0
		v1 = tVertices[0][ix]; //
		v2 = tVertices[0][ix-1]; // 
		v3 = tVertices[1][ix]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[0][ix]; //
		v2 = tVertices[1][ix]; // 
		v3 = tVertices[0][ix+1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[0][ix].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[0][ix].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[0][ix].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
		////////////////////
	}

	////////////// iz = 0, ix = width-1		
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

	for(int iz = 1; iz<height-1; iz++){ 

		//////////// DO FOR ix = 0
		v1 = tVertices[iz][0]; //
		v2 = tVertices[iz+1][0]; // 
		v3 = tVertices[iz][1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[iz][0]; //
		v2 = tVertices[iz][1]; // 
		v3 = tVertices[iz-1][0]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[iz][0].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[iz][0].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[iz][0].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
				
		//////////////////////////

		for (int ix = 1; ix<width-1; ix++){

			///// BASE CASE //////
			
			v1 = tVertices[iz-1][ix]; //
			v2 = tVertices[iz][ix-1]; //
			v3 = tVertices[iz+1][ix]; //
			
			u = v2 - v1;
			v = v3 - v1;
			
			x1 = (u.y*v.z) - (u.z*v.y);
			y1 = (u.z*v.x) - (u.x*v.z);
			z1 = (u.x*v.y) - (u.y*v.x);
			
			v1 = tVertices[iz-1][ix]; //
			v2 = tVertices[iz+1][ix]; // 
			v3 = tVertices[iz][ix+1]; // 
			
			u = v2 - v1;
			v = v3 - v1;
			
			tNormals[iz][ix].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
			tNormals[iz][ix].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
			tNormals[iz][ix].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
			////////////////////
			
		}
		////////////// ix = width-1
		v1 = tVertices[iz][width-1]; //
		v2 = tVertices[iz-1][width-1]; // 
		v3 = tVertices[iz][width-2]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[iz][width-1]; //
		v2 = tVertices[iz][width-2]; // 
		v3 = tVertices[iz+1][width-1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[iz][width-1].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[iz][width-1].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[iz][width-1].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
				
	}

	///////////////// for iz = height-1, ix = 0;
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


	for(int ix =1; ix<width-1;ix++){
		////////////////// for iz = height-1
		v1 = tVertices[height-1][ix]; //
		v2 = tVertices[height-2][ix]; // 
		v3 = tVertices[height-1][ix-1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[height-1][ix]; //
		v2 = tVertices[height-1][ix+1]; // 
		v3 = tVertices[height-2][ix]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[height-1][ix].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[height-1][ix].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[height-1][ix].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
		////////////////////////
	}
	//////////////// for iz = height-1, ix = width -1
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

