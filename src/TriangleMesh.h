//TriangleMesh.h
#ifndef TRIANGLEMESH
#define TRIANGLEMESH

#include <QtOpenGL>
#include <QDebug>
#include <math.h>
#include "Vec3.h"
#ifndef TIME
#define TIME
#include "time.h"
#endif

#include <iostream>

#include "TerrainTexture.h"

class TriangleMesh{

	public:
		TriangleMesh(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight);
		void compile();
		void computeNormals();
		
		int width;
		int height;
		
		float** heightmap;
		
		Vec3 ** tVertices;
		Vec3 ** tColors;
		Vec3 ** tNormals;
		
};

#endif
