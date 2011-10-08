#include "GLWidget.h"

#include <QDebug>

GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	
	m_xrot = 15;
	m_yrot = 45;
	m_zrot = 0;	
	
	m_ambient = 0.0; 
	m_diffuse = 1.0;  
	m_specular = 1.0;  
	m_xpos = 0;
	m_ypos = 0;
	m_zpos = 1;
	
	m_wireframe = false;
}		


void GLWidget::toggleWireframe()
{
	if(m_wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_wireframe = false;
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_wireframe = true;
	}
	
	updateGL();
}


////////////////////////
//     Protected
////////////////////////

void GLWidget::initializeGL()
{
	qglClearColor(Qt::black);
	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	float ambient[] = {0.3, 0.1, 0.3, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	glEnable(GL_LIGHT0);
	
	initLists();
}

void GLWidget::initLists()
{
	m_displayList = glGenLists(1);
	m_generator = new Generator();
	m_polygons = m_generator->polygons();
	
	glNewList(m_displayList, GL_COMPILE);
	
	for(GLuint i = 0; i < m_polygons.size(); i++)
	{		
		glBegin(GL_POLYGON);
		glColor3fv(m_polygons[i]->get_color());
		glNormal3fv(m_polygons[i]->get_normal());

		for(int j = 0; j < 4; j++)
		{
			glVertex3fv(m_polygons[i]->get_vertices()[j]);
		}

		glEnd();
	}
	glEndList();
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
	
	lighting();
	
	glTranslatef(0.0, 0.0, -7.0);
	
	glRotatef(m_xrot, 1.0, 0.0, 0.0);
	glRotatef(m_yrot, 0.0, 1.0, 0.0);
	
	glScalef(0.5, 0.5, 0.5);

	glCallList(m_displayList);
}

void GLWidget::lighting()
{
	float Ambient[] = {m_ambient, m_ambient, m_ambient, 1.0};
	float Diffuse[] = {m_diffuse, m_diffuse, m_diffuse, 1.0};
	float Specular[] = {m_specular, m_specular, m_specular, 1.0};
	float Position[] = {m_xpos, m_ypos, m_zpos, 1.0};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT , Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE , Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, Position);
}











