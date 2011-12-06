#include "BloomShader.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

BloomShader::BloomShader()
{
	m_horizFragShader = new QGLShader(QGLShader::Fragment);
	m_horizFragShader->compileSourceFile("./shaders/horizontal_blur.frag");
	
	m_horizVertShader = new QGLShader(QGLShader::Vertex);
	m_horizVertShader->compileSourceFile("./shaders/horizontal_blur.vert");
		
	m_horizBlurProgram = new QGLShaderProgram();
	m_horizBlurProgram->addShader(m_horizFragShader);
	m_horizBlurProgram->addShader(m_horizVertShader);
	m_horizBlurProgram->link();
	
	m_vertFragShader = new QGLShader(QGLShader::Fragment);
	m_vertFragShader->compileSourceFile("./shaders/vertical_blur.frag");
	
	m_vertVertShader = new QGLShader(QGLShader::Vertex);
	m_vertVertShader->compileSourceFile("./shaders/vertical_blur.vert");
		
	m_vertBlurProgram = new QGLShaderProgram();
	m_vertBlurProgram->addShader(m_vertFragShader);
	m_vertBlurProgram->addShader(m_vertVertShader);
	m_vertBlurProgram->link();
	
	m_using_shaders = false;
		
	m_fbo = new QGLFramebufferObject(1366, 768, QGLFramebufferObject::NoAttachment);
}


void BloomShader::toggleShaders()
{
	m_using_shaders = !m_using_shaders;
}


void BloomShader::draw(GLuint tex, float width)
{
	m_fbo->bind();
	
	m_texHandle = tex;
	
	if(m_using_shaders)
	{
		m_horizBlurProgram->bind();
		glActiveTexture(GL_TEXTURE0);
   		glBindTexture(GL_TEXTURE_2D, m_texHandle);
		m_horizBlurProgram->setUniformValue(m_shaderTextureLocation, 0);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_texHandle);
	}
	
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.4);
	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-width, -1, 0);
	glTexCoord2f(1, 0); glVertex3f(width, -1, 0);
	glTexCoord2f(1, 1); glVertex3f(width, 1, 0);
	glTexCoord2f(0, 1); glVertex3f(-width, 1, 0);
	glEnd();
	
	if(m_using_shaders)
	{
		m_horizBlurProgram->release();
	}
	
	m_fbo->release();
	
	m_texHandle = m_fbo->texture();

	if(m_using_shaders)
	{
		m_vertBlurProgram->bind();
		glActiveTexture(GL_TEXTURE0);
   		glBindTexture(GL_TEXTURE_2D, m_texHandle);
		m_vertBlurProgram->setUniformValue(m_shaderTextureLocation, 0);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_texHandle);
	}
	
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.4);
	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-width, -1, 0);
	glTexCoord2f(1, 0); glVertex3f(width, -1, 0);
	glTexCoord2f(1, 1); glVertex3f(width, 1, 0);
	glTexCoord2f(0, 1); glVertex3f(-width, 1, 0);
	glEnd();
	
	if(m_using_shaders)
	{
		m_vertBlurProgram->release();
	}

}
