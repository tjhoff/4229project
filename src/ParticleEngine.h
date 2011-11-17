#ifndef PARTICLE_ENGINE_H
#define PARTICLE_ENGINE_H

#include "Particle.h"
#include <QList>

class ParticleEngine 
{
	public:
		ParticleEngine();
		~ParticleEngine();
		
		void draw();
		
	private:
		QList<Particle*> m_particles;
		
};

#endif
