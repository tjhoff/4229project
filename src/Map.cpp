#include "Map.h"

Map::Map(){
	gen = new TerrainGenerator();
	curx = 0;
	curz = 0;
	Chunk * C = new Chunk(curx, curz, gen);
	chunkList.push_back(C);
}

Map::~Map(){
	delete gen;
	
}

Chunk* Map::getChunkAt(int x, int z){
	Chunk * retC;
	
	for(std::vector<Chunk*>::iterator it = chunkList.begin(); it!=chunkList.end(); it++){
		retC = *it;
		if ((retC->x() == x) && (retC->z() == z)){
			std::cout<<"Chunk found at "<< x<<" "<<z<<"\n";	
			return retC;
		}
	
	}
	std::cout<<"No chunk at "<< x<<" "<<z<<"\n";	
	// if no chunk matching the coordinates was found

	retC = new Chunk(x, z, gen);
	chunkList.push_back(retC);
	return retC;
}
