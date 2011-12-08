#include "ParticleEngine.h"

#include <QDebug>
#include <QtOpenGL>
#include <stdlib.h>
#include <time.h>

ParticleEngine::ParticleEngine()
{
	m_nParticles = 5250;
	srand(time(NULL));
	for(int i = 0; i < m_nParticles; i++)
	{
		m_particles.append(new Particle());
	}
	
	QImage buf, snowflake;
	buf.load("./tex/snowflake.bmp");
	snowflake = QGLWidget::convertToGLFormat(buf);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1,&m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, snowflake.width(), snowflake.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, snowflake.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	m_particleShader = new ParticleShader();
	m_shaderTextureLocation = m_particleShader->textureLocation();
}

ParticleEngine::~ParticleEngine()
{
}

void ParticleEngine::compile()
{
	for(int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->compile();
	}
}

void ParticleEngine::draw()
{		
	m_particleShader->bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	m_particleShader->setUniformValue(m_shaderTextureLocation, 0);
	
	for(int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->draw();
	}
	
	m_particleShader->release();
}
