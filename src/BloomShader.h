#ifndef BLOOM_SHADER_H
#define BLOOM_SHADER_H

#include <QtOpenGL>

class BloomShader
{
	public:
		BloomShader(QGLWidget* glw);

		void toggleShaders();
		void draw(GLuint tex, float width);
		void resize(int width, int height);
		
	private:
		QGLShaderProgram* m_horizBlurProgram;
		QGLShader* m_horizFragShader;
		QGLShader* m_horizVertShader;
		
		QGLShaderProgram* m_vertBlurProgram;
		QGLShader* m_vertFragShader;
		QGLShader* m_vertVertShader;
		
		GLuint m_texHandle;
		int m_shaderTextureLocation;
		
		QGLFramebufferObject* m_fbo;
		
		QGLWidget* m_glw;
};

#endif
