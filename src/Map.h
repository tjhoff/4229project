#ifndef MAP_H
#define MAP_H

/*#ifndef THREADED_PROCESSOR_H
#define THREADED_PROCESSOR_H

#include <QThread>
#include "Generator.h"
#include "TriangleMesh.h"

class ThreadedProcessor : public QThread
{
	public:
		void run();
}

#endif*/

#include <vector>
#include "Chunk.h"
#include "Generator.h"
#include "Global.h"

class Map{
	public:
		Map();
		~Map();
		std::vector<Chunk*> chunkList;
		Chunk* getChunkAt(int x, int z);
		void deleteChunkAt(int x, int z);
		void deleteFurthestChunk();
		Generator * gen;
		int curx;
		int curz;
		int numCurrentChunks;
};

#endif
