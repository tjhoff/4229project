#include "GLWidget.h"

#include <QDebug>

GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	
	m_xrot = 15;
	m_yrot = 45;
	m_zrot = 0;
	
	m_cubeSize = 0.5;
	
	m_faceColors[0] = Qt::red;
	m_faceColors[1] = Qt::green;
	m_faceColors[2] = Qt::blue;
	m_faceColors[3] = Qt::yellow;
	m_faceColors[4] = Qt::darkMagenta;
	m_faceColors[5] = Qt::gray;
}

////////////////////////
//     Protected
////////////////////////

void GLWidget::initializeGL()
{
	qglClearColor(Qt::black);
	glEnable(GL_DEPTH_TEST);
}


void GLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	m_width = (height>0) ? (GLfloat)width/height : 1;
	glFrustum(-m_width, +m_width, -1.0, 1.0, 4, 15);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
}

void GLWidget::mousePressEvent(QMouseEvent* event)
{
	QGLWidget::mousePressEvent(event);
	m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
	QGLWidget::mouseMoveEvent(event);
	
	GLfloat dx = GLfloat(event->x() - m_lastPos.x()) / width();
	GLfloat dy = GLfloat(event->y() - m_lastPos.y()) / height();
	
	if(event->buttons() & Qt::LeftButton)
	{
		m_xrot += 180 * dy;
		m_yrot += 180 * dx;
		updateGL();
		m_lastPos = event->pos();
	}	
}

///////////////////////////
//       Private
///////////////////////////

void GLWidget::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(m_xrot, 1.0, 0.0, 0.0);
	glRotatef(m_yrot, 0.0, 1.0, 0.0);
	glRotatef(m_zrot, 0.0, 0.0, 1.0);
	
	glBegin(GL_QUADS);
	
	//top face
	qglColor(m_faceColors[0]);
	glVertex3f(-m_cubeSize, m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, m_cubeSize, m_cubeSize);
	glVertex3f(-m_cubeSize, m_cubeSize, m_cubeSize);
	
	// left face
	qglColor(m_faceColors[1]);
	glVertex3f(-m_cubeSize, -m_cubeSize, -m_cubeSize);
	glVertex3f(-m_cubeSize, m_cubeSize, -m_cubeSize);
	glVertex3f(-m_cubeSize, m_cubeSize, m_cubeSize);
	glVertex3f(-m_cubeSize, -m_cubeSize, m_cubeSize);
	
	// right face
	qglColor(m_faceColors[2]);
	glVertex3f(m_cubeSize, -m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, m_cubeSize, m_cubeSize);
	glVertex3f(m_cubeSize, -m_cubeSize, m_cubeSize);
	
	//front face
	qglColor(m_faceColors[3]);
	glVertex3f(-m_cubeSize, -m_cubeSize, m_cubeSize);
	glVertex3f(-m_cubeSize, m_cubeSize, m_cubeSize);
	glVertex3f(m_cubeSize, m_cubeSize, m_cubeSize);
	glVertex3f(m_cubeSize, -m_cubeSize, m_cubeSize);
	
	//back face
	qglColor(m_faceColors[4]);
	glVertex3f(-m_cubeSize, -m_cubeSize, -m_cubeSize);
	glVertex3f(-m_cubeSize, m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, -m_cubeSize, -m_cubeSize);
	
	//bottom face
	qglColor(m_faceColors[5]);
	glVertex3f(-m_cubeSize, -m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, -m_cubeSize, -m_cubeSize);
	glVertex3f(m_cubeSize, -m_cubeSize, m_cubeSize);
	glVertex3f(-m_cubeSize, -m_cubeSize, m_cubeSize);
	
	glEnd();
	
}













