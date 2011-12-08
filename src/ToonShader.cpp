#include "ToonShader.h"

ToonShader::ToonShader()
{
	QGLShader* vert = new QGLShader(QGLShader::Vertex);
	QGLShader* frag = new QGLShader(QGLShader::Fragment);
	
	vert->compileSourceFile("./shaders/toon.vert");
	frag->compileSourceFile("./shaders/toon.frag");
	
	m_shaderProg = new QGLShaderProgram();
	m_shaderProg->addShader(vert);
	m_shaderProg->addShader(frag);
	m_shaderProg->link();
	
	m_shaderFogFlag = m_shaderProg->uniformLocation("fog_enabled");
	m_shaderProg->setUniformValue(m_shaderFogFlag, false);
}

void ToonShader::setFogEnabled(bool enabled)
{
	m_fogEnabled = enabled;
}

void ToonShader::bind()
{
	m_shaderProg->bind();
	m_shaderProg->setUniformValue(m_shaderFogFlag, m_fogEnabled);
}

void ToonShader::release()
{
	m_shaderProg->release();
}
