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
}

void PlainShader::bind()
{
	m_shaderProg->bind();
}

void PlainShader::release()
{
	m_shaderProg->release();
}
