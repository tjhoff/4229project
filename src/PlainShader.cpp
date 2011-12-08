#include "PlainShader.h"

PlainShader::PlainShader()
{
	QGLShader* vert = new QGLShader(QGLShader::Vertex);
	QGLShader* frag = new QGLShader(QGLShader::Fragment);
	
	vert->compileSourceFile("./shaders/plain.vert");
	frag->compileSourceFile("./shaders/plain.frag");
	
	m_shaderProg = new QGLShaderProgram();
	m_shaderProg->addShader(vert);
	m_shaderProg->addShader(frag);
	m_shaderProg->link();

	m_shaderFogFlag = m_shaderProg->uniformLocation("fog_enabled");
	m_shaderProg->setUniformValue(m_shaderFogFlag, false);
}

void PlainShader::setFogEnabled(bool enabled)
{
	m_fogEnabled = enabled;
}

void PlainShader::bind()
{
	m_shaderProg->bind();
	m_shaderProg->setUniformValue(m_shaderFogFlag, m_fogEnabled);
}

void PlainShader::release()
{
	m_shaderProg->release();
}
