#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <QtOpenGL>

class ShaderManager
{
	public:
		ShaderManager();

		void toggleShaders();
		void draw(GLuint tex, float width);
		
	private:
		QGLShaderProgram* m_blurProgram;
		QGLShader* m_blurShader;
		
		GLuint m_texHandle;
		bool m_using_shaders;
		int m_shaderTextureLocation;
		
		QGLBuffer* m_vbo;
		QGLBuffer* m_ibo;		
		
		
};

#endif
