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
}

void ToonShader::bind()
{
	m_shaderProg->bind();
}

void ToonShader::release()
{
	m_shaderProg->release();
}
