#ifndef POLYGON_H
#define POLYGON_H


class Vec3;

class Polygon 
{
	public:
		Polygon();
		Polygon(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4);
		
		void set_vertices(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4);
		
		double** get_vertices();
		double* get_normal(); 
	
	private:
		Vec3* m_vertices;
};


class Vec3
{
	public:
		Vec3();
		Vec3(double x, double y, double z);
		Vec3(const Vec3& source);
		
		Vec3& operator=(const Vec3& source);
		Vec3& operator+(const Vec3& rhs);
		Vec3& operator-(const Vec3& rhs);
		double operator*(const Vec3& rhs);
		
		double x;
		double y;
		double z;
		
};


#endif
		
