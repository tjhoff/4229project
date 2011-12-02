//TriangleMesh.cpp
#include "TriangleMesh.h"

#define vertex(i,j) glVertex3f(tVertices[i][j].x,tVertices[i][j].y,tVertices[i][j].z)
#define color(i,j) glColor3f(1.0, 1.0, 1.0)
#define normal(i,j) glNormal3f(tNormals[i][j].x,tNormals[i][j].y,tNormals[i][j].z)

#define ColNormVex(i,j)   normal(i,j); color(i,j); vertex(i,j)

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>

TriangleMesh::TriangleMesh(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight){

	width = vwidth;
	height = vheight;
	
	tVertices = new Vec3 * [height];
	tColors = new Vec3 * [height];
	tNormals = new Vec3 * [height];
	
	for(int iz = 0; iz < height; iz++){
		tVertices[iz] = new Vec3[width];
		tColors[iz] = new Vec3[width];
		tNormals[iz] = new Vec3[width];
		
		for(int ix = 0; ix<width; ix++){
			tVertices[iz][ix] = vertices[iz][ix];
			tColors[iz][ix] = colors[iz][ix];
		}
	}
	double start_time = clock()/1000;
	computeNormals();
	compile();
	qDebug()<<"Calculating normals took "<< clock()/1000 - start_time << "mirriseconds";
	
}

TriangleMesh::~TriangleMesh(){

	/*for (int i = 0; i<height; i++){
		for(int j = 0; j< height; j++){
			delete tVertices[i][j];
			delete tColors[i][j];
			delete tNormals[i][j];
		}
		
	}*/
	for (int i = 0; i<height; i++){
		delete tVertices[i];
		delete tColors[i];
		delete tNormals[i];
	}
	delete tVertices;
	delete tColors;
	delete tNormals;
	qDebug()<< "Take THAT, memory leaks!";

}

void TriangleMesh::compile()
{
	terrainVBO = new QGLBuffer(QGLBuffer::VertexBuffer);
	terrainIBO = new QGLBuffer(QGLBuffer::IndexBuffer);
	
	terrainVBO->create();
	terrainIBO->create();
	
	GLsizeiptr float_buffer_size = width*height*3 + width*height*2 + width*height*3; //normals + colors + texcoords + vertices
	GLsizeiptr byte_buffer_size = float_buffer_size*sizeof(float);
	
	float* bufferdata = new float[float_buffer_size];
	
	numIndices = (width-1)*(width-1)*6;
	GLushort* indexdata = new GLushort[numIndices];
	
	int counter = 0;
	//initialize the indexdata
	for(int i = 0; i < numIndices; i+=6)
	{
		if((counter%width) == (width-1))
		{
			counter += 1;
		}
		indexdata[i+2] = counter;
		indexdata[i+1] = counter+1;
		indexdata[i+0] = counter+width;
		indexdata[i+3] = counter+1;
		indexdata[i+4] = counter+width;
		indexdata[i+5] = counter+width+1;

		counter += 1;
	}
	
	
	// bufferdata looks like this
	// norm.x norm.y norm.z tex.x tex.y vertex.x vertex.y vertex.z ...
	
	/*for(int index = 0; index < width*height; index+=8)
	{
		int i = index/width;
		int j = index%width;
		
		bufferdata[index] = tNormals[i][j].x;
		bufferdata[index+1] = tNormals[i][j].y;
		bufferdata[index+2] = tNormals[i][j].z;
		bufferdata[index+3] = (double)(i)/height;
		bufferdata[index+4] = (double)(j)/width;
		bufferdata[index+5] = tVertices[i][j].x;
		bufferdata[index+6] = tVertices[i][j].y;
		bufferdata[index+7] = tVertices[i][j].z;
	}*/

	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			int index = ((i*width)+j)*8;
			bufferdata[index] = tNormals[i][j].x;
			bufferdata[index+1] = tNormals[i][j].y;
			bufferdata[index+2] = tNormals[i][j].z;
			bufferdata[index+3] = (double)(i)/height;
			bufferdata[index+4] = (double)(j)/width;
			bufferdata[index+5] = tVertices[i][j].x;
			bufferdata[index+6] = tVertices[i][j].y;
			bufferdata[index+7] = tVertices[i][j].z;
		}
	}
	
	terrainVBO->setUsagePattern(QGLBuffer::StaticDraw);
	terrainVBO->bind();
	terrainVBO->allocate(bufferdata, byte_buffer_size);
	
	terrainIBO->setUsagePattern(QGLBuffer::StaticDraw);
	terrainIBO->bind();
	terrainIBO->allocate(indexdata, sizeof(GLushort)*numIndices);
	
	TerrainTexture* tex = new TerrainTexture(tColors, width, height);
	tex_id = tex->texture();
}


void TriangleMesh::draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glColor3f(1.0, 1.0, 1.0);
	terrainVBO->bind();
	terrainIBO->bind();
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 8*sizeof(float), (GLvoid*)(5*sizeof(float)));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 8*sizeof(float), (GLvoid*)(3*sizeof(float)));
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 8*sizeof(float), (GLvoid*)NULL);
	
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
}


void TriangleMesh::computeNormals()
{
	
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

