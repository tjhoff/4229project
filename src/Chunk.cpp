//Chunk.cpp
#include "Chunk.h"
#include <QDebug>

Chunk::Chunk(int ix,int iz, Generator * m_gen){
	x = ix;
	z = iz;
	gen = m_gen;
	create();
}

void Chunk::create(){
	gen->polygons_at(x, z);
	tMesh= new TriangleMesh(gen->m_vertices,gen->m_colors,gen->m_d, gen->m_d);
	heightmap = new Heightmap(tMesh, tMesh->width, tMesh->height, 5.0/tMesh->width, 5.0*x, 5.0*z); 
}

void Chunk::draw()
{
	tMesh->draw();
}
