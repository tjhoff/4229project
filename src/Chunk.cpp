//Chunk.cpp
#include "Chunk.h"
#include <QDebug>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Chunk::Chunk(int ix,int iz, TerrainGenerator * terrainGen){
	m_x = ix;
	m_z = iz;
	m_terrainGen = terrainGen;
	create();
}

void Chunk::create(){
	m_terrainGen->polygons_at(m_x, m_z);
	m_width = m_terrainGen->m_d;
	m_height = m_terrainGen->m_d;
	
	m_bufferGen = new BufferGenerator(m_terrainGen->m_vertices, m_terrainGen->m_colors, m_terrainGen->m_d, m_terrainGen->m_d);
	m_heightMap = new Heightmap(m_bufferGen, m_bufferGen->width(), m_bufferGen->height(), 5.0/m_bufferGen->width(), 5.0*m_x, 5.0*m_z); 
	qDebug() << "Heightmap:" << m_heightMap;
	
	m_terrainVBO = new QGLBuffer(QGLBuffer::VertexBuffer);
	m_terrainIBO = new QGLBuffer(QGLBuffer::IndexBuffer);
	
	m_terrainVBO->create();
	m_terrainIBO->create();
	
	GLushort* IBOData = m_bufferGen->IBOData();
	GLfloat* VBOData = m_bufferGen->VBOData();
	
	int VBOSize = m_bufferGen->VBOByteSize();
	int IBOSize = m_bufferGen->IBOByteSize();
	int numIndices = m_bufferGen->numIndices();
	
	m_terrainVBO->setUsagePattern(QGLBuffer::StaticDraw);
	m_terrainVBO->bind();
	
	m_terrainVBO->allocate(VBOData, VBOSize);
	
	m_terrainIBO->setUsagePattern(QGLBuffer::StaticDraw);
	m_terrainIBO->bind();
	m_terrainIBO->allocate(IBOData, IBOSize);
	
	TerrainTexture* tex = new TerrainTexture(m_terrainGen->m_colors, m_width, m_height);
	m_texID = tex->texture();
}

void Chunk::draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texID);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glColor3f(1.0, 1.0, 1.0);
	m_terrainVBO->bind();
	m_terrainIBO->bind();
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 8*sizeof(float), (GLvoid*)(5*sizeof(float)));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 8*sizeof(float), (GLvoid*)(3*sizeof(float)));
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 8*sizeof(float), (GLvoid*)NULL);
	
	glDrawElements(GL_TRIANGLES, m_bufferGen->numIndices(), GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
}

