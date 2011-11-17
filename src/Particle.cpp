#include "Particle.h"

#include <QDebug>

#include <QtOpenGL>

#include <stdlib.h>
#include <time.h>

Particle::Particle()
{
	
	m_x = (((double)rand()/RAND_MAX)*5)-1;
	m_y = (((double)rand()/RAND_MAX)*5)-1;
	m_z = (((double)rand()/RAND_MAX)*5)-1;
	
	m_xrot = ((double)rand()/RAND_MAX)*90;
	m_yrot = ((double)rand()/RAND_MAX)*90;
	m_zrot = ((double)rand()/RAND_MAX)*90;
}

Particle::~Particle()
{
}

void Particle::compile()
{
}

void Particle::draw()
{
	m_y -= 0.015;
	if(m_y < -1)
	{
		m_y = 4.0;
	}
	
	m_xrot += 1;
	m_yrot += 1;
	m_zrot += 1;
	
	if(m_xrot > 360)
	{
		m_xrot = 0;
	}
	
	if(m_yrot > 360)
	{
		m_yrot = 0;
	}
	
	if(m_zrot > 360)
	{
		m_zrot = 0;
	}
	
	glPushMatrix();
	
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	
	glColor3f(1.0, 1.0, 1.0);
	
	glTranslatef(m_x, m_y, m_z);
	glRotatef(m_xrot, 1, 0, 0);
	glRotatef(m_yrot, 0, 1, 0);
	glRotatef(m_zrot, 0, 0, 1);
	glScalef(0.03, 0.03, 0.03);
	
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.001);
	glVertex3f(-0.5, 0.5, 0.001);
	glVertex3f(0.5, 0.5, 0.001);
	glVertex3f(0.5, -0.5, 0.001);
	glEnd();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	
	glPopMatrix();
	
}
