#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include <QList>
#include <stdio.h>
#include "Polygon.h"
#include "Heightmap.h"
#include "Perlin.h"

//-------------------------------
//     Base TerrainGenerator Class
//
//     Subclass this for different 
//     terrain generators
//-------------------------------
class TerrainGenerator
{
	public:
		TerrainGenerator();
		~TerrainGenerator();
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
		float fuzzy_height(float middle, float plus_or_minus, float x, float z);
		void islands(int i, int j, float step, int chunk_x, int chunk_z);
		
			
		QList<Polygon*> m_polys;
		float* m_default_translation;
		int m_seed;
		
		Perlin* m_base_height_perlin;
		Perlin* m_detail_perlin;
		Perlin* m_height_cutoff_perlin;
};

#endif
