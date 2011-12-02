#include "ShaderManager.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

ShaderManager::ShaderManager()
{
	m_blurShader = new QGLShader(QGLShader::Fragment);
	m_blurShader->compileSourceFile("./shaders/blur.f.glsl");
		
	m_blurProgram = new QGLShaderProgram();
	m_blurProgram->addShader(m_blurShader);
	m_blurProgram->link();
	
	m_using_shaders = false;
	
	float vertices[] = {0, 1, -1, 1, 
						0, 0, -1, -1, 
						1, 0, 1, -1, 
						1, 1, 1, 1};
						
	int indices[] = {0, 1, 2, 3};
	
	m_vbo = new QGLBuffer(QGLBuffer::VertexBuffer);
	m_ibo = new QGLBuffer(QGLBuffer::IndexBuffer);
	
	m_vbo->create();
	m_ibo->create();
	
	m_vbo->setUsagePattern(QGLBuffer::StaticDraw);
	m_vbo->bind();
	m_vbo->allocate(vertices, 16*sizeof(float));
	
	m_ibo->setUsagePattern(QGLBuffer::StaticDraw);
	m_ibo->bind();
	m_ibo->allocate(indices, 4*sizeof(int));
	
}


void ShaderManager::toggleShaders()
{
	m_using_shaders = !m_using_shaders;
}


void ShaderManager::draw(GLuint tex, float width)
{
	m_texHandle = tex;
	
	if(m_using_shaders)
	{
		m_blurProgram->bind();
		glActiveTexture(GL_TEXTURE0);
   		glBindTexture(GL_TEXTURE_2D, m_texHandle);
		m_blurProgram->setUniformValue(m_shaderTextureLocation, 0);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_texHandle);
	}
	
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2.4);
	//glScalef(width, 1, 1);
	
	glColor3f(1.0, 1.0, 1.0);
	m_vbo->bind();
	m_ibo->bind();
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 2*sizeof(float), (GLvoid*)(2*sizeof(float)));
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 2*sizeof(float), (GLvoid*)(0*sizeof(float)));
	
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
	
	if(m_using_shaders)
	{
		m_blurProgram->release();
	}

}

