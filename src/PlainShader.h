#ifndef PLAIN_SHADER_H
#define PLAIN_SHADER_H

#include <QtOpenGL>

class PlainShader
{
	public:
		PlainShader();
		void bind();
		void release();
		
	private:
		QGLShaderProgram* m_shaderProg;

};

#endif
