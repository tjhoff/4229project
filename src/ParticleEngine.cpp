#include "ParticleEngine.h"

#include <QDebug>
#include <QtOpenGL>
#include <stdlib.h>
#include <time.h>

ParticleEngine::ParticleEngine()
{
	m_nParticles = 1250;
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
	for(int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i]->draw();
	}
}
