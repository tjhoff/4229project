#include "Polygon.h"

#include <QDebug>

Polygon::Polygon()
{
	m_vertices.append(Vec3(-0.5, -0.5, 0.0));
	m_vertices.append(Vec3(0.5, -0.5, 0.0));
	m_vertices.append(Vec3(0.5, 0.5, 0.0));
	m_vertices.append(Vec3(-0.5, 0.5, 0.0));
	
	m_fnormal = new float[3];
}

Polygon::Polygon(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4)
{
	m_vertices.append(v1);
	m_vertices.append(v2);
	m_vertices.append(v3);
	m_vertices.append(v4);
	m_colors.append(c1);
	m_colors.append(c2);
	m_colors.append(c3);
	m_colors.append(c4);
	m_fnormal = new float[3];
}


Polygon::~Polygon()
{
	if(m_fcolors.size() != 0)
	{
		for(int i = 0; i < 4; i++)
		{
			delete[] m_fcolors[i];
		}
	}
	
	if(m_fvertices.size() != 0)
	{
		for(int i = 0; i < 4; i++)
		{
			delete[] m_fvertices[i];
		}
	}
	
	delete[] m_fnormal;
}


void Polygon::set_vertices(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
{
	m_vertices.clear();
	m_vertices.append(v1);
	m_vertices.append(v2);
	m_vertices.append(v3);
	m_vertices.append(v4);
}


void Polygon::set_colors(Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4)
{
	m_colors.clear();
	m_colors.append(c1);
	m_colors.append(c2);
	m_colors.append(c3);
	m_colors.append(c4);
}


QList<float*> Polygon::get_vertices()
{
	for(int i = 0; i < 4; i++)
	{
		float *vec = new float[3];
		vec[0] = m_vertices[i].x;
		vec[1] = m_vertices[i].y;
		vec[2] = m_vertices[i].z;
		m_fvertices.append(vec);
	}
	return m_fvertices;
}


QList<float*> Polygon::get_colors()
{
	for(int i = 0; i < 4; i++)
	{
		float* col = new float[3];
	
		col[0] = m_colors[i].x;
		col[1] = m_colors[i].y;
		col[2] = m_colors[i].z;
		
		m_fcolors.append(col);
	}
	return m_fcolors;
}


float* Polygon::get_normal()
{
	m_fnormal = new float[3];
	
	Vec3 U = m_vertices[1] - m_vertices[0];
	Vec3 V = m_vertices[2] - m_vertices[0];
	
	m_fnormal[0] = (U.y * V.z) - (U.z * V.y);
	m_fnormal[1] = (U.z * V.x) - (U.x * V.z);
	m_fnormal[2] = (U.x * V.y) - (U.y * V.x); 
	
	return m_fnormal;
}



