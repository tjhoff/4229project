#ifndef GENERATOR_H
#define GENERATOR_H

#include <QList>
#include "Polygon.h"
#include "Heightmap.h"
#include "Perlin.h"

//-------------------------------
//     Base Generator Class
//
//     Subclass this for different 
//     terrain generators
//-------------------------------
class Generator
{
	public:
		Generator();
		~Generator();
		QList<Polygon*> polygons_at(int x, int z);
		float* default_translation();
		Heightmap * heightmap;
		Vec3** m_vertices;
		Vec3** m_colors;
		int m_d;
		float m_chunk_size;
	private:
		void chunk_at(int x, int z);	
		float base_height(float x, float z);	
		QList<Polygon*> m_polys;
		float* m_default_translation;
		int m_seed;
		
		Perlin* m_base_height_perlin;
		Perlin* m_detail_perlin;
};

#endif
