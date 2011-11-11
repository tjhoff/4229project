//BufferGenerator.h
#ifndef BUFFER_GENERATOR
#define BUFFER_GENERATOR

#include <QDebug>
#include <math.h>
#include <stdint.h>

#include "Vec3.h"
#include "TerrainTexture.h"

class BufferGenerator{

	public:
		BufferGenerator(Vec3 ** vertices, Vec3 ** colors, int vwidth, int vheight);
		
		float* VBOData() { return m_VBOdata; }
		uint16_t* IBOData() { return m_IBOdata; }
		int width() { return m_width; }
		int height() { return m_height; }
		
		int VBOByteSize() { return m_VBOByteSize; }
		int IBOByteSize() { return m_numIndices*sizeof(uint16_t); }
		int numIndices() { return m_numIndices; }
		
	private:
		void compile();
		void computeNormals();
		
		int m_width;
		int m_height;
		
		float* m_VBOdata;
		uint16_t* m_IBOdata;
		
		int m_VBOByteSize;
		int m_numIndices;
		
		Vec3 ** tVertices;
		Vec3 ** tColors;
		Vec3 ** tNormals;
		
		GLuint tex_id;
		
};

#endif
