#include "Polygon.h"

#include <QDebug>

Polygon::Polygon()
{
	m_vertices.append(Vec3(-0.5, -0.5, 0.0));
	m_vertices.append(Vec3(0.5, -0.5, 0.0));
	m_vertices.append(Vec3(0.5, 0.5, 0.0));
	m_vertices.append(Vec3(-0.5, 0.5, 0.0));
}

Polygon::Polygon(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Vec3 color)
{
	m_vertices.append(v1);
	m_vertices.append(v2);
	m_vertices.append(v3);
	m_vertices.append(v4);
	m_color = color;
}

void Polygon::set_vertices(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
{
	m_vertices.append(v1);
	m_vertices.append(v2);
	m_vertices.append(v3);
	m_vertices.append(v4);
}


void Polygon::set_color(Vec3 color)
{
	m_color = color;
}


QList<float*> Polygon::get_vertices()
{
	QList<float*> ret;

	for(int i = 0; i < 4; i++)
	{
		float *vec = new float[3];
		vec[0] = m_vertices[i].x;
		vec[1] = m_vertices[i].y;
		vec[2] = m_vertices[i].z;
		ret.append(vec);
	}
	return ret;
}


float* Polygon::get_color()
{
	float* ret = new float[3];
	
	ret[0] = m_color.x;
	ret[1] = m_color.y;
	ret[2] = m_color.z;
	
	return ret;
}


float* Polygon::get_normal()
{
	float* norm = new float[3];
	
	Vec3 U = m_vertices[1] - m_vertices[0];
	Vec3 V = m_vertices[2] - m_vertices[0];
	
	norm[0] = (U.y * V.z) - (U.z * V.y);
	norm[1] = (U.z * V.x) - (U.x * V.z);
	norm[2] = (U.x * V.y) - (U.y * V.x); 
	
	return norm;
}



