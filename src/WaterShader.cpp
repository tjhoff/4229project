#include "WaterShader.h"

WaterShader::WaterShader()
{
	QGLShader* vert = new QGLShader(QGLShader::Vertex);
	//QGLShader* frag = new QGLShader(QGLShader::Fragment);
	
	vert->compileSourceFile("./shaders/water.vert");
	//vert->compileSourceFile("./shaders/water.frag");
	
	m_shaderProg = new QGLShaderProgram();
	m_shaderProg->addShader(vert);
	//m_shaderProg->addShader(frag);
	m_shaderProg->link();
}

void WaterShader::bind()
{
	m_shaderProg->bind();
}

void WaterShader::release()
{
	m_shaderProg->release();
}
