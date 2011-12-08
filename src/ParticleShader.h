#ifndef PARTICLE_SHADER_H
#define PARTICLE_SHADER_H

#include <QtOpenGL>

class ParticleShader
{
	public:
		ParticleShader();
		void bind();
		void release();
		GLuint textureLocation() { return m_textureLocation; }
		void setUniformValue(int location, int value) { m_shaderProg->setUniformValue(location, value); }
		
	private:
		QGLShaderProgram* m_shaderProg;
		GLuint m_textureLocation;
};

#endif
