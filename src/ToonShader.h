#ifndef TOON_SHADER_H
#define TOON_SHADER_H

#include <QtOpenGL>

class ToonShader
{
	public:
		ToonShader();
		void bind();
		void release();
		
	private:
		QGLShaderProgram* m_shaderProg;

};

#endif
