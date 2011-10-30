//Chunk.cpp
#include "Chunk.h"
Chunk::Chunk(int ix,int iz, Generator * m_gen){
	x = ix;
	z = iz;
	displayName = glGenLists(1);
	gen = m_gen;
	create();
	compile();
}

void Chunk::create(){
	gen->polygons_at(x, z);
	tMesh= new TriangleMesh(gen->m_vertices,gen->m_colors,gen->m_d, gen->m_d);
	heightmap = new Heightmap(tMesh, tMesh->width, tMesh->height, 5.0/tMesh->width, 5.0*x, 5.0*z); 
}

void Chunk::compile(){
	glDeleteLists(displayName, 1);
	displayName = glGenLists(1);
	glNewList(displayName, GL_COMPILE);
	tMesh->compile();
	glEndList();
}

void Chunk::draw(){
	glCallList(displayName);
}
