//TriangleMesh.h
#include <QtOpenGL>
#include <math.h>
#include "Vec3.h"

#include <iostream>

class TriangleMesh{

	public:
		TriangleMesh(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight);
		void compile();
		void computeNormals();
		
		int width;
		int height;
		
		Vec3 ** tVertices;
		Vec3 ** tColors;
		Vec3 ** tNormals;

};
