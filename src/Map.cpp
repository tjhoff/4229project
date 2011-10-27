#include "Map.h"

Map::Map(){
	gen = new Generator();

}

Map::~Map(){
	delete gen;
	
}

Chunk* Map::getChunkAt(int x, int z){
	Chunk * retC;
	for(std::vector<Chunk*>::iterator it = chunkList.begin(); it!=chunkList.end(); it++){
		retC = *it;
		if ((retC->x == x) && (retC->z == z)){
			return retC;
		}
	
	}
	
	// if no chunk matching the coordinates was found

	retC = new Chunk(x, z, gen);
	chunkList.push_back(retC);
	return retC;
}
