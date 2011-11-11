#ifndef CHUNK_H
#define CHUNK_H

// Chunk.h
#include "BufferGenerator.h"
#include "TerrainGenerator.h"

#include <QtOpenGL>

class Chunk{
	public: 
		Chunk(int ix,int iz, TerrainGenerator * terrainGen);
		void create();
		void compile();
		void draw();	
		int x() { return m_x; }
		int z() { return m_z; }
		
		Heightmap* heightMap() { return m_heightMap; }
		
	private:
		int m_x;
		int m_z;
		
		int m_width;
		int m_height;
	
		Heightmap* m_heightMap;
		BufferGenerator* m_bufferGen;
		TerrainGenerator * m_terrainGen;
		
		QGLBuffer* m_terrainVBO;
		QGLBuffer* m_terrainIBO;
		
		GLuint m_texID;
};

#endif
