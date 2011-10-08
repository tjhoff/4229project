#include "Vec3.h"

#include <QDebug>

Vec3::Vec3()
{
	x = 1.0;
	y = 1.0;
	z = 1.0;
}

Vec3::Vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}	

Vec3::Vec3(const Vec3& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
}

Vec3 Vec3::operator= (const Vec3& source)
{
	x = source.x;
	y = source.y;
	z = source.z;
	return *this;
}

Vec3 Vec3::operator+(const Vec3& rhs)
{
	Vec3 v;
	v.x = x + rhs.x;
	v.y = y + rhs.y;
	v.z = z + rhs.z;
	return v;
}

Vec3 Vec3::operator-(const Vec3& rhs)
{
	Vec3 v;
	v.x = x - rhs.x;
	v.y = y - rhs.y;
	v.z = z - rhs.z;
	return v;
}

float Vec3::operator*(const Vec3& rhs)
{
	return (x*rhs.x) + (y*rhs.y) + (z*rhs.z);
}






