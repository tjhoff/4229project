#include "Map.h"

Map::Map(){
	m_terrainGen = new TerrainGenerator();
	curx = 0;
	curz = 0;
}

Map::~Map(){
	delete m_terrainGen;
}

Chunk* Map::getChunkAt(int x, int z){
	qDebug() << "Map::getChunkAt";
	Chunk* c;
	
	for(int i = 0; i < m_chunkList.size(); i++)
	{
		c = m_chunkList[i];
		if((c->x() == x) && (c->z() == z))
		{
			qDebug() << "Chunk found at"<< x <<  z;
			return c;
		}
	
	}
	qDebug() << "No chunk at" << x << z;	
	// if no chunk matching the coordinates was found

	c = new Chunk(x, z, m_terrainGen);
	qDebug() << "new chunk was" << c;
	m_chunkList.append(c);
	return c;
}
