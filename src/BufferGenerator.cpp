//BufferGenerator.cpp
#include "BufferGenerator.h"

BufferGenerator::BufferGenerator(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight){

	m_width = vwidth;
	m_height = vheight;
	
	tVertices = new Vec3 * [m_height];
	tColors = new Vec3 * [m_height];
	tNormals = new Vec3 * [m_height];
	
	for(int iz = 0; iz < m_height; iz++){
		tVertices[iz] = new Vec3[m_width];
		tColors[iz] = new Vec3[m_width];
		tNormals[iz] = new Vec3[m_width];
		
		for(int ix = 0; ix<m_width; ix++){
			tVertices[iz][ix] = vertices[iz][ix];
			tColors[iz][ix] = colors[iz][ix];
		}
	}
	computeNormals();
	compile();
	
}

void BufferGenerator::compile()
{
	size_t float_buffer_size = m_width*m_height*3 + m_width*m_height*2 + m_width*m_height*3; //normals + colors + texcoords + vertices
	
	m_VBOdata = new float[float_buffer_size];
	
	m_numIndices = (m_width-1)*(m_width-1)*6;
	m_IBOdata = new GLushort[m_numIndices];
	
	int counter = 0;
	//initialize the m_IBOdata
	for(int i = 0; i < m_numIndices; i+=6)
	{
		if((counter%m_width) == (m_width-1))
		{
			counter += 1;
		}
		m_IBOdata[i+2] = counter;
		m_IBOdata[i+1] = counter+1;
		m_IBOdata[i+0] = counter+m_width;
		m_IBOdata[i+3] = counter+1;
		m_IBOdata[i+4] = counter+m_width;
		m_IBOdata[i+5] = counter+m_width+1;

		counter += 1;
	}
	
	
	// m_VBOdata looks like this
	// norm.x norm.y norm.z tex.x tex.y vertex.x vertex.y vertex.z ...
	for(int i = 0; i < m_width; i++)
	{
		for(int j = 0; j < m_height; j++)
		{
			int index = ((i*m_width)+j)*8;
			m_VBOdata[index] = tNormals[i][j].x;
			m_VBOdata[index+1] = tNormals[i][j].y;
			m_VBOdata[index+2] = tNormals[i][j].z;
			m_VBOdata[index+3] = (double)(i)/m_height;
			m_VBOdata[index+4] = (double)(j)/m_width;
			m_VBOdata[index+5] = tVertices[i][j].x;
			m_VBOdata[index+6] = tVertices[i][j].y;
			m_VBOdata[index+7] = tVertices[i][j].z;
		}
	}
}



void BufferGenerator::computeNormals()
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
	

	for(int ix = 1;ix<m_width-1;ix++){
	
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

	////////////// iz = 0, ix = m_width-1		
	v1 = tVertices[0][m_width-1]; //
	v2 = tVertices[0][m_width-2]; // 
	v3 = tVertices[1][m_width-1]; //
			
	u = v2 - v1;
	v = v3 - v1;
			
	x1 = (u.y*v.z) - (u.z*v.y);
	y1 = (u.z*v.x) - (u.x*v.z);
	z1 = (u.x*v.y) - (u.y*v.x);
				
	tNormals[0][m_width-1].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
	tNormals[0][m_width-1].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
	tNormals[0][m_width-1].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
	//////////////////////////

	for(int iz = 1; iz<m_height-1; iz++){ 

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

		for (int ix = 1; ix<m_width-1; ix++){

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
		////////////// ix = m_width-1
		v1 = tVertices[iz][m_width-1]; //
		v2 = tVertices[iz-1][m_width-1]; // 
		v3 = tVertices[iz][m_width-2]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[iz][m_width-1]; //
		v2 = tVertices[iz][m_width-2]; // 
		v3 = tVertices[iz+1][m_width-1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[iz][m_width-1].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[iz][m_width-1].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[iz][m_width-1].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
				
	}

	///////////////// for iz = m_height-1, ix = 0;
	v1 = tVertices[m_height-1][0]; //
	v2 = tVertices[m_height-1][1]; // 
	v3 = tVertices[m_height-2][0]; //
			
	u = v2 - v1;
	v = v3 - v1;
			
	x1 = (u.y*v.z) - (u.z*v.y);
	y1 = (u.z*v.x) - (u.x*v.z);
	z1 = (u.x*v.y) - (u.y*v.x);
			
	tNormals[m_height-1][0].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
	tNormals[m_height-1][0].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
	tNormals[m_height-1][0].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
	//////////////////////////


	for(int ix =1; ix<m_width-1;ix++){
		////////////////// for iz = m_height-1
		v1 = tVertices[m_height-1][ix]; //
		v2 = tVertices[m_height-2][ix]; // 
		v3 = tVertices[m_height-1][ix-1]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		x1 = (u.y*v.z) - (u.z*v.y);
		y1 = (u.z*v.x) - (u.x*v.z);
		z1 = (u.x*v.y) - (u.y*v.x);
				
		v1 = tVertices[m_height-1][ix]; //
		v2 = tVertices[m_height-1][ix+1]; // 
		v3 = tVertices[m_height-2][ix]; //
			
		u = v2 - v1;
		v = v3 - v1;
			
		tNormals[m_height-1][ix].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
		tNormals[m_height-1][ix].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
		tNormals[m_height-1][ix].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
		////////////////////////
	}
	//////////////// for iz = m_height-1, ix = m_width -1
	v1 = tVertices[m_height-1][m_width-1]; //
	v2 = tVertices[m_height-2][m_width-1]; // 
	v3 = tVertices[m_height-1][m_width-2]; //
			
	u = v2 - v1;
	v = v3 - v1;
			
	tNormals[m_height-1][m_width-1].x = (x1+(u.y*v.z) - (u.z*v.y))/2;
	tNormals[m_height-1][m_width-1].y = (y1+(u.z*v.x) - (u.x*v.z))/2;
	tNormals[m_height-1][m_width-1].z = (z1+(u.x*v.y) - (u.y*v.x))/2;
				
	/////////////////////////////////////
}

