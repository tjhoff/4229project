#include "Map.h"

Map::Map(){
	gen = new Generator();
	curx = 0;
	curz = 0;
	Chunk * C = new Chunk(curx, curz, gen);
	chunkList.push_back(C);
	numCurrentChunks = 1;
}

Map::~Map(){
	delete gen;
	Chunk* retC;
	for(std::vector<Chunk*>::iterator it = chunkList.begin(); it!=chunkList.end(); it++){
		retC = *it;
		
		delete retC;
	
	}
}

void Map::deleteChunkAt(int x, int z){
	Chunk* retC;
	for(std::vector<Chunk*>::iterator it = chunkList.begin(); it!=chunkList.end(); it++){
		retC = *it;
		if ((retC->x == x) && (retC->z == z)){
			delete retC;
			numCurrentChunks -=1;
			return;
		}
	
	}

}

void Map::deleteFurthestChunk(){
	Chunk* retC;
	Chunk* furthest;
	float distance = 0;
	for(std::vector<Chunk*>::iterator it = chunkList.begin(); it!=chunkList.end(); it++){
		retC = *it;
		
		
		float newdistance = sqrt(pow(abs(curx - retC->x), 2) + pow(abs(curz - retC->z), 2));
		
		if (newdistance > distance){
			furthest = retC;
		}
		
	
	}
	delete retC;

}

Chunk* Map::getChunkAt(int x, int z){
	Chunk * retC;
	
	for(std::vector<Chunk*>::iterator it = chunkList.begin(); it!=chunkList.end(); it++){
		retC = *it;
		if ((retC->x == x) && (retC->z == z)){
			std::cout<<"Chunk found at "<< x<<" "<<z<<"\n";	
			return retC;
		}
	
	}
	std::cout<<"No chunk at "<< x<<" "<<z<<"\n";	
	// if no chunk matching the coordinates was found
	numCurrentChunks +=1;
	
	//if (numCurrentChunks >= CURRENT_CHUNK_LIMIT){
	//	deleteFurthestChunk();
	//}
	
	retC = new Chunk(x, z, gen);
	chunkList.push_back(retC);
	return retC;
}
