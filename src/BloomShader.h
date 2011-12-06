#ifndef BLOOM_SHADER_H
#define BLOOM_SHADER_H

#include <QtOpenGL>

class BloomShader
{
	public:
		BloomShader();

		void toggleShaders();
		void draw(GLuint tex, float width);
		
	private:
		QGLShaderProgram* m_horizBlurProgram;
		QGLShader* m_horizFragShader;
		QGLShader* m_horizVertShader;
		
		QGLShaderProgram* m_vertBlurProgram;
		QGLShader* m_vertFragShader;
		QGLShader* m_vertVertShader;
		
		GLuint m_texHandle;
		bool m_using_shaders;
		int m_shaderTextureLocation;
		
		QGLFramebufferObject* m_fbo;
};

#endif
