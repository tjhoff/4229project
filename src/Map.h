#ifndef MAP_H
#define MAP_H

#include <vector>
#include <iostream>

#include "Chunk.h"
#include "TerrainGenerator.h"

class Map
{
	public:
		Map();
		~Map();
		std::vector<Chunk*> chunkList;
		Chunk* getChunkAt(int x, int z);
		TerrainGenerator * gen;
		int curx;
		int curz;
};

#endif
