#include "ParticleShader.h"

ParticleShader::ParticleShader()
{
	QGLShader* vert = new QGLShader(QGLShader::Vertex);
	QGLShader* frag = new QGLShader(QGLShader::Fragment);
	
	vert->compileSourceFile("./shaders/snowflake.vert");
	frag->compileSourceFile("./shaders/snowflake.frag");
	
	m_shaderProg = new QGLShaderProgram();
	m_shaderProg->addShader(vert);
	m_shaderProg->addShader(frag);
	m_shaderProg->link();
	
	m_textureLocation = m_shaderProg->uniformLocation("texture");
}

void ParticleShader::bind()
{
	m_shaderProg->bind();
}

void ParticleShader::release()
{
	m_shaderProg->release();
}
