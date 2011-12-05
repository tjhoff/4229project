#include "Skybox.h"
#define val 1.0
#define a glVertex3f(val/2, val/4, val/2)
#define b glVertex3f(-val/2, val/4, val/2)
#define c glVertex3f(-val/2, -val/8, val/2)
#define d glVertex3f(val/2, -val/8, val/2)

#define e glVertex3f(val/2, val/4, -val/2)
#define f glVertex3f(val/2, -val/8, -val/2)
#define g glVertex3f(-val/2, -val/8, -val/2)
#define h glVertex3f(-val/2, val/4, -val/2)


Skybox::Skybox(){
	
	int m_tex_width = 600;
	int m_tex_height = 600;
	
	glEnable(GL_TEXTURE_2D);
	QImage Iright, Ileft, Ifront, Iback, Itop, buffer;
	buffer.load("./tex/right62.jpg");
	Iright = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&right);
	glBindTexture(GL_TEXTURE_2D, right);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Iright.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	
	
	buffer.load("./tex/left62.jpg");
	Ileft = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&left);
	glBindTexture(GL_TEXTURE_2D, left);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Ileft.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	buffer.load("./tex/front62.jpg");
	Ifront = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&front);
	glBindTexture(GL_TEXTURE_2D,front );
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Ifront.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	buffer.load("./tex/back62.jpg");
	Iback = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&back);
	glBindTexture(GL_TEXTURE_2D, back);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Iback.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	buffer.load("./tex/top62.jpg");
	Itop = QGLWidget::convertToGLFormat(buffer);
	glGenTextures(1,&top);
	glBindTexture(GL_TEXTURE_2D, top);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, m_tex_width, m_tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Itop.bits());
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void Skybox::draw(){
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	
	glBindTexture(GL_TEXTURE_2D, right);
	glBegin(GL_QUADS);
		
		glTexCoord2f(1.0,1.0);b;
		glTexCoord2f(0.0,1.0);a;
		glTexCoord2f(0.0,0.0);d;
		glTexCoord2f(1.0,0.0);c;
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, front);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0,1.0);a;
		glTexCoord2f(0.0,1.0);e;
		glTexCoord2f(0.0,0.0);f;
		glTexCoord2f(1.0,0.0);d;
	glEnd();
	glBindTexture(GL_TEXTURE_2D, left);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0,1.0);e;
		glTexCoord2f(0.0,1.0);h;
		glTexCoord2f(0.0,0.0);g;
		glTexCoord2f(1.0,0.0);f;
	glEnd();
	glBindTexture(GL_TEXTURE_2D, back);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0,1.0);h;
		glTexCoord2f(0.0,1.0);b;
		glTexCoord2f(0.0,0.0);c;
		glTexCoord2f(1.0,0.0);g;
	glEnd();
	glBindTexture(GL_TEXTURE_2D, top);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,0.0);e;
		glTexCoord2f(1.0,0.0);a;
		glTexCoord2f(1.0,1.0);b;
		glTexCoord2f(0.0,1.0);h;
	glEnd();
	
	glEnable(GL_LIGHTING);
}

