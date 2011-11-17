#ifndef MAP_H
#define MAP_H

#include <QList>
#include <QDebug>

#include "Chunk.h"
#include "TerrainGenerator.h"

class Map
{
	public:
		Map();
		~Map();
		Chunk* getChunkAt(int x, int z);
		
		int curx;
		int curz;
	
	private:
		QList<Chunk*> m_chunkList;
		TerrainGenerator * m_terrainGen;
};

#endif
