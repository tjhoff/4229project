#ifndef PARTICLE_ENGINE_H
#define PARTICLE_ENGINE_H

#include "Particle.h"
#include "ParticleShader.h"
#include <QList>
#include <QtOpenGL>

class ParticleEngine 
{
	public:
		ParticleEngine();
		~ParticleEngine();
		
		void compile();
		void draw();
		
	private:
		QList<Particle*> m_particles;
		ParticleShader* m_particleShader;
		int m_nParticles;
		GLuint m_texture;
		GLuint m_shaderTextureLocation;
		
};

#endif
