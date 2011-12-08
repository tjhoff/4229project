#include "Skybox.h"
#define a(val) glVertex3f(val, val, val)
#define b(val) glVertex3f(-val, val, val)
#define c(val) glVertex3f(-val, -val, val)
#define d(val) glVertex3f(val, -val, val)

#define e(val) glVertex3f(val, val, -val)
#define f(val) glVertex3f(val, -val, -val)
#define g(val) glVertex3f(-val, -val, -val)
#define h(val) glVertex3f(-val, val, -val)


Skybox::Skybox(){
	
	int m_tex_width = 1024;
	int m_tex_height = 1024;
	
	glEnable(GL_TEXTURE_2D);
	QImage Iright, Ileft, Ifront, Iback, Itop, Ibottom, buffer;
	
	
	buffer.load("./tex/day/right.bmp");
	Iright = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&right);
	glBindTexture(GL_TEXTURE_2D, right);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Iright.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	
	buffer.load("./tex/day/left.bmp");
	Ileft = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&left);
	glBindTexture(GL_TEXTURE_2D, left);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Ileft.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	buffer.load("./tex/day/front.bmp");
	Ifront = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&front);
	glBindTexture(GL_TEXTURE_2D,front );
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Ifront.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	buffer.load("./tex/day/back.bmp");
	Iback = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&back);
	glBindTexture(GL_TEXTURE_2D, back);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Iback.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	buffer.load("./tex/day/top.bmp");
	Itop = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&top);
	glBindTexture(GL_TEXTURE_2D, top);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Itop.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	buffer.load("./tex/day/bdown.bmp");
	Iright = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&bottom);
	glBindTexture(GL_TEXTURE_2D, bottom);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Ibottom.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

}

void Skybox::draw(){
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	
	glBindTexture(GL_TEXTURE_2D, right);
	glBegin(GL_QUADS);
		
		glTexCoord2f(0.999,0.999);b(5.0);
		glTexCoord2f(0.001,0.999);a(5.0);
		glTexCoord2f(0.001,0.001);d(5.0);
		glTexCoord2f(0.999,0.001);c(5.0);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, front);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.999,0.999);a(5.0);
		glTexCoord2f(0.001,0.999);e(5.0);
		glTexCoord2f(0.001,0.001);f(5.0);
		glTexCoord2f(0.999,0.001);d(5.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, left);
	glBegin(GL_QUADS);
		glTexCoord2f(0.999,0.999);e(5.0);
		glTexCoord2f(0.001,0.999);h(5.0);
		glTexCoord2f(0.001,0.001);g(5.0);
		glTexCoord2f(0.999,0.001);f(5.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, back);
	glBegin(GL_QUADS);
		glTexCoord2f(0.999,0.999);h(5.0);
		glTexCoord2f(0.001,0.999);b(5.0);
		glTexCoord2f(0.001,0.001);c(5.0);
		glTexCoord2f(0.999,0.001);g(5.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, top);
	glBegin(GL_QUADS);
		glTexCoord2f(0.001,0.001);e(5.0);
		glTexCoord2f(0.999,0.001);a(5.0);
		glTexCoord2f(0.999,0.999);b(5.0);
		glTexCoord2f(0.001,0.999);h(5.0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, bottom);
	glBegin(GL_QUADS);
		glTexCoord2f(0.001,0.001);c(5.0);
		glTexCoord2f(0.999,0.001);d(5.0);
		glTexCoord2f(0.999,0.999);f(5.0);
		glTexCoord2f(0.001,0.999);g(5.0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

