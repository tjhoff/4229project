#ifndef TOON_SHADER_H
#define TOON_SHADER_H

#include <QtOpenGL>

class ToonShader
{
	public:
		ToonShader();
		void bind();
		void release();
		void setFogEnabled(bool enabled);
		
	private:
		QGLShaderProgram* m_shaderProg;
		GLuint m_shaderFogFlag;
		bool m_fogEnabled;

};

#endif
