#include "TerrainTexture.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <QDebug>

TerrainTexture::TerrainTexture(Vec3** colormap, int width, int height)
{
	QImage forest, water, snow, sand, lava, lavarock, buf;
	buf.load("./tex/water.bmp");
	water = QGLWidget::convertToGLFormat(buf);
	
	buf.load("./tex/forest.bmp");
	forest = QGLWidget::convertToGLFormat(buf);
	
	buf.load("./tex/snow.bmp");
	snow = QGLWidget::convertToGLFormat(buf);
	
	buf.load("./tex/sand.bmp");
	sand = QGLWidget::convertToGLFormat(buf);
	
	buf.load("./tex/lavarock.bmp");
	lavarock = QGLWidget::convertToGLFormat(buf);
	
	buf.load("./tex/lava.bmp");
	lava = QGLWidget::convertToGLFormat(buf);
	
	m_tex_width = forest.width();
	m_tex_height = forest.height();
	
	unsigned char* texture_bits = forest.bits();
	unsigned char* water_bits = water.bits();
	unsigned char* snow_bits = snow.bits();
	unsigned char* sand_bits = sand.bits();
	unsigned char* lavarock_bits = lavarock.bits();
	unsigned char* lava_bits = lava.bits();
	
	int wratio = m_tex_width/width;
	int hratio = m_tex_height/height;
	double step = 1/m_tex_width;
	
	srand(time(NULL));
	
	
	for(int i = 0; i < (m_tex_width*m_tex_height*4); i+=4)
	{
		int x = ((i/4)/m_tex_width)/wratio;
		int y = ((i/4)%m_tex_height)/hratio;
		if(x > (width-1)) x = width-1;
		if(y > (height-1)) y = height-1;
		Vec3 color = colormap[y][x];
		
		if(color == Vec3(0.0, 0.0, 0.6))
		{
			texture_bits[i] = water_bits[i];
			texture_bits[i+1] = water_bits[i+1];
			texture_bits[i+2] = water_bits[i+2];
			texture_bits[i+3] = water_bits[i+3];
		}
		else if(color == Vec3(1.0, 1.0, 1.0))
		{
			texture_bits[i] = sand_bits[i];
			texture_bits[i+1] = sand_bits[i+1];
			texture_bits[i+2] = sand_bits[i+2];
			texture_bits[i+3] = sand_bits[i+3];
		}
		else if(color == Vec3(0.2, 0.2, 0.2))
		{
			texture_bits[i] = lavarock_bits[i];
			texture_bits[i+1] = lavarock_bits[i+1];
			texture_bits[i+2] = lavarock_bits[i+2];
			texture_bits[i+3] = lavarock_bits[i+3];
		}
		else if(color == Vec3(1.0, 0.0, 0.0))
		{
			texture_bits[i] = lava_bits[i];
			texture_bits[i+1] = lava_bits[i+1];
			texture_bits[i+2] = lava_bits[i+2];
			texture_bits[i+3] = lava_bits[i+3];
		}
			
		//else if(hvalue > 0.9)
		///{
		//	texture_bits[i] = snow_bits[i];
		//	texture_bits[i+1] = snow_bits[i+1];
		//	texture_bits[i+2] = snow_bits[i+2];
		//	texture_bits[i+3] = snow_bits[i+3];
		//}
	}
	
	glGenTextures(1,&m_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_bits);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

