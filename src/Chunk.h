#ifndef CHUNK_H
#define CHUNK_H

// Chunk.h
#include "TriangleMesh.h"
#include "Generator.h"
#include "Global.h"
#include "ObjectManager.h"

#include <QtOpenGL>

class Chunk{
	public: 
		Chunk(int ix,int iz, Generator * m_gen);
		~Chunk();
		GLuint texture() { return tMesh->tex_id; }
		int x;
		int z;
		int displayName;
		Heightmap* heightmap;
		TriangleMesh* tMesh;
		Generator * gen;
		void create();
		void compile();
		void draw();
		ObjectManager manager;
};

#endif
