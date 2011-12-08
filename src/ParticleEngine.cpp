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
	glDisable(GL_TEXTURE_2D);
	glColor3f(1,1,1);
	for(int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->draw();
	}
	glEnable(GL_TEXTURE_2D);
}
