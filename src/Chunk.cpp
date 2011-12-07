//Chunk.cpp
#include "Chunk.h"
#include <QDebug>

Chunk::Chunk(int ix,int iz, Generator * m_gen){
	x = ix;
	z = iz;
	gen = m_gen;
	create();
}

Chunk::~Chunk(){

	delete tMesh;
	delete heightmap;

}

void Chunk::create(){
	gen->polygons_at(x, z);
	tMesh= new TriangleMesh(gen->m_vertices,gen->m_colors,gen->m_d, gen->m_d);
	heightmap = new Heightmap(tMesh, tMesh->width, tMesh->height, CHUNK_SIZE/tMesh->width, CHUNK_SIZE*x, CHUNK_SIZE*z); 
	Vec3** colors = gen->m_colors;
	for (int i = 0; i<1; i++){
	
		float rx = ((rand()%1000)/(1000.0/CHUNK_SIZE)+x*CHUNK_SIZE);
		float rz = ((rand()%1000)/(1000.0/CHUNK_SIZE)+z*CHUNK_SIZE);
		float ry = heightmap->getYValue(rx, rz)-.2;
		if (colors[(int)(rx-x*CHUNK_SIZE)][(int)(rz-z*CHUNK_SIZE)]== Vec3(0,0,0)) continue;
		Object* obj = new Object(1, rx, ry, rz);
		obj->setScale(1.0);
		manager.addObject(obj);
	
	}
}

void Chunk::draw()
{
	tMesh->draw();
	manager.drawObjects();
}
