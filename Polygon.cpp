#include "Polygon.h"


Polygon::Polygon()
{
	m_vertices = new Vec3[4];
	m_vertices[0] = Vec3(-0.5, -0.5, 0.0);
	m_vertices[1] = Vec3(0.5, -0.5, 0.0);
	m_vertices[2] = Vec3(0.5, 0.5, 0.0);
	m_vertices[3] = Vec3(-0.5, 0.5, 0.0);
}

Polygon::Polygon(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
{
	m_vertices = new Vec3[4];
	m_vertices[0] = v1;
	m_vertices[1] = v2;
	m_vertices[2] = v3;
	m_vertices[3] = v4;
}

void Polygon::set_vertices(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4)
{
	m_vertices[0] = v1;
	m_vertices[1] = v2;
	m_vertices[2] = v3;
	m_vertices[3] = v4;
}


double** Polygon::get_vertices()
{
	double** ret = new double*[4];
 	
	for(int i = 0; i < 4; i++)
	{
		ret[i] = new double[3];
		ret[i][0] = m_vertices[i].x; 
		ret[i][1] = m_vertices[i].y; 
		ret[i][2] = m_vertices[i].z;
	}
	return ret;
}

double* Polygon::get_normal()
{
	double* norm = new double[3];
	
	Vec3 U = m_vertices[1] - m_vertices[0];
	Vec3 V = m_vertices[2] - m_vertices[0];
	
	norm[0] = (U.y * V.z) - (U.z * V.y);
	norm[1] = (U.z * V.x) - (U.x * V.z);
	norm[2] = (U.x * V.y) - (U.y * V.x); 
	
	return norm;
}


////////////////////////////
//    Vector Classes
////////////////////////////

Vec3::Vec3()
{
	x = 1.0;
	y = 1.0;
	x = 1.0;
}

Vec3::Vec3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->x = z;
}	

Vec3::Vec3(const Vec3& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
}

Vec3& Vec3::operator= (const Vec3& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
	return *this;
}

Vec3& Vec3::operator+(const Vec3& rhs)
{
	x = x + rhs.x;
	y = y + rhs.y;
	z = z + rhs.z;
	return *this;
}

Vec3& Vec3::operator-(const Vec3& rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
	z = z - rhs.z;
	return *this;
}

double Vec3::operator*(const Vec3& rhs)
{
	return (x*rhs.x) + (y*rhs.y) + (z*rhs.z);
}






