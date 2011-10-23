#ifndef TERRAIN_TEXTURE_H
#define TERRAIN_TEXTURE_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QImage>

class TerrainTexture
{
	public:
		TerrainTexture(float** heightmap, int width, int height);
		GLuint texture() { return m_texture_id; }
		int tex_width() { return m_tex_width; }
		int tex_height() { return m_tex_height; }
				
	private:
		GLuint m_texture_id;
		int m_tex_width;
		int m_tex_height;
	
};

#endif
