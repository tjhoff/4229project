#ifndef PLAIN_SHADER_H
#define PLAIN_SHADER_H

#include <QtOpenGL>

class PlainShader
{
	public:
		PlainShader();
		void bind();
		void release();
		void setFogEnabled(bool enabled);
		
	private:
		QGLShaderProgram* m_shaderProg;
		GLuint m_shaderFogFlag;
		bool m_fogEnabled;

};

#endif
