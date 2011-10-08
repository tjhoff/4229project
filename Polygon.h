#ifndef POLYGON_H
#define POLYGON_H

#include <QList>

#include "Vec3.h"


//--------------------------------------
//        The Polygon Class
// 
//        Polygons must be drawn in ccw 
//        order, or the normal vector 
//        calculation will bork!
//--------------------------------------
class Polygon 
{
	public:
		Polygon();
		Polygon(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Vec3 color);
		
		void set_vertices(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4);
		void set_color(Vec3 color);
		
		QList<float*> get_vertices();
		float* get_color();
		float* get_normal(); 
	
	private:
		QList<Vec3> m_vertices;
		Vec3 m_color;
};


#endif
		
