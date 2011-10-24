#ifndef VEC3_H
#define VEC3_H

//----------------------------------------
//       A Simple 3 component vector
//
//       All the basic vector math works
//----------------------------------------
class Vec3
{
	public:
		Vec3();
		Vec3(float x, float y, float z);
		Vec3(const Vec3& source);
		
		Vec3 operator=(const Vec3& source);
		Vec3 operator+(const Vec3& rhs);
		Vec3 operator-(const Vec3& rhs);
		float operator*(const Vec3& rhs);
		bool operator==(const Vec3& rhs);
	
		float x;
		float y;
		float z;
		
};

#endif
