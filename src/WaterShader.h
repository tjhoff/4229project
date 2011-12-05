#ifndef WATER_SHADER_H
#define WATER_SHADER_H

#include <QtOpenGL>

class WaterShader 
{
	public:
		WaterShader();
		void bind();
		void release();
	
	private:
		int m_time;
		QGLShaderProgram* m_shaderProg;
};

#endif
