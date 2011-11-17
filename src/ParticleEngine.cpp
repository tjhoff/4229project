#include "ParticleEngine.h"

#include <QDebug>

ParticleEngine::ParticleEngine()
{
	qDebug() << "ParticleEngine constructor";
}

ParticleEngine::~ParticleEngine()
{
	qDebug() << "ParticleEngine destructor";
}


void ParticleEngine::draw()
{
	qDebug() << "ParticleEngine::draw()";
	for(int i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].draw();
	}
}
