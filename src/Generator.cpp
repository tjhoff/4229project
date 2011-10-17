#include "Generator.h"

#include <math.h>
#include <QString>
#include <QDebug>

#include <time.h>


Generator::Generator()
{
	m_d = 0;
	m_seed = 5;
	m_base_height_perlin = new Perlin(6, 2, 1, m_seed);
	m_chunk_size = 5;
}


Generator::~Generator()
{
	qDebug() << "Generator destructor";
	if(m_d != 0)
	{
		for(int i = 0; i < m_d; i++)
		{
			delete[] m_colors[i];
			delete[] m_vertices[i];
		}
		delete[] m_colors;
		delete[] m_vertices;
		delete[] m_default_translation;
		
		m_polys.clear();
	}
}
		


float* Generator::default_translation()
{
	m_default_translation = new float[3];
	m_default_translation[0] = -2.5;
	m_default_translation[1] = 0.0;
	m_default_translation[2] = -2.5;
	return m_default_translation;
}


void Generator::chunk_at(int chunk_x, int chunk_z)
{
	double start_time = clock()/1000;
	
	m_d = 200;
	float step = m_chunk_size/m_d;
	float x,y,z;
	
	float ** yVals = new float *[m_d];
	for(int i = 0; i<m_d; i++) yVals[i] = new float[m_d]; //heightmap yVals
	
	Vec3 color;
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i<m_d;i++){
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		z = (i*step) + (chunk_z*m_chunk_size);
		for(int j = 0; j<m_d; j++){
			x = (j*step) + (chunk_x*m_chunk_size);
			y = base_height(x, z);
			
			if(y > 0.3)
			{
				y = (y*0.1)+0.27;
				color = Vec3(0.4, 0.2, 0.1);			
			}
			else if (y > .02)
			{	
				color = Vec3(.6*y + .4, 0.40*y +.2, 0.1);			
			}
			else{
				color = Vec3(.8,.8,.7);
			}
			
			m_vertices[i][j] = Vec3(x,y,z);
			m_colors[i][j] = color;

		}
	}
	
	qDebug() << "Generator::chunk_at() took" << (clock()/1000) - start_time << "milliseconds";
}


float Generator::base_height(float x, float z)
{
	float y = m_base_height_perlin->Get(x/2, z/2);	
	return y*y*2;
}


QList<Polygon*> Generator::polygons_at(int x, int z)
{
	m_polys.clear();
	
	if(m_d != 0)
	{
		for(int i = 0; i < m_d; i++)
		{
			delete[] m_colors[i];
			delete[] m_vertices[i];
		}
		delete[] m_colors;
		delete[] m_vertices;
		
		for(int i = 0; i < m_polys.size(); i++)
		{
			delete m_polys[i];
		}
		
		m_d = 0;
	}

	chunk_at(x, z);
	
	return m_polys;
}





