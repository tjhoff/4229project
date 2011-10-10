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
		Polygon(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4, Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4);
		
		void set_vertices(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 v4);
		void set_colors(Vec3 c1, Vec3 c2, Vec3 c3, Vec3 c4);
		
		QList<float*> get_vertices();
		QList<float*> get_colors();
		float* get_normal(); 
	
	private:
		QList<Vec3> m_vertices;
		QList<Vec3> m_colors;
};


#endif
		
