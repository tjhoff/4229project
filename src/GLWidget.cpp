#include "GLWidget.h"

#include <QDebug>

#include <QPainter>
#include <unistd.h>

GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	
	m_xrot = 15;
	m_yrot = 45;
	m_zrot = 0;	
	m_zoom = 1.0;
	
	m_speed = .001;
	
	m_ambient = 0.0; 
	m_diffuse = .5;  
	m_specular = 1.0;  
	m_xpos = 0;
	m_ypos = 0;
	m_zpos = 0;
	m_light_rotation = 0.0;
	
	m_fps_camera = true;
	
	m_wireframe = false;
	
	cam = new Camera3d(0.0,0.0,-7.0);
	setFocusPolicy(Qt::StrongFocus);
	m_update_timer = new QTimer();
	connect(m_update_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	m_update_timer->start(1000/60.0);
}		


GLWidget::~GLWidget()
{
	qDebug() << "GLWidget destructor";
	if(m_generator != NULL) 
		delete m_generator;
		
	delete[] m_default_translation;
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


void GLWidget::drawScene()
{
	if(m_polygons.size() != 0)
	{
		m_polygons.clear();
		delete m_generator;
		
		glDeleteLists(m_displayLists, 9);
	}
	
	m_generator = new Generator();

	m_current_xchunk = 0;
	m_current_zchunk = 0;
	
	change_current_chunk();

	updateGL();
}

void GLWidget::toggleCameraMode()
{
	m_fps_camera = !m_fps_camera;
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
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_CULL_FACE);
	
	float ambient[] = {0.1, 0.1, 0.1, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	glEnable(GL_LIGHT0);
	glLighti(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
}


void GLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	m_width = (height>0) ? (GLfloat)width/height : 1;
	gluPerspective(45, m_width, 0.005, 15);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	draw();
}

void GLWidget::updateGL()
{
	QGLWidget::updateGL();
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
		if(m_fps_camera)
		{
			cam->rotate(180*-dx,180*-dy);
		}
		else
		{
			m_xrot += 180 * dy;
			m_yrot += 180 * dx;
		}
		updateGL();
		m_lastPos = event->pos();
	}	
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
	if(m_fps_camera)
	{
		if(event->delta() > 0)
		{
			m_speed += .001;
			//m_zoom += 0.1;
		}
		else if(event->delta() < 0)
		{
			m_speed -= .001;
			//m_zoom -= 0.1;
		}
	}
	else
	{	
		if(event->delta() > 0)
		{
			m_zoom += 0.1;
		}
		else if(event->delta() < 0)
		{
			m_zoom -= 0.1;
		}
	}
	
	updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent* event){

	switch(event->key())
	{
		case Qt::Key_W:
		{
			cam->move(m_speed);
			break;
		}
		case Qt::Key_S:
		{
			cam->move(-m_speed);
			break;
		}
		case Qt::Key_Up:
		{
			m_current_zchunk -= 1;
			change_current_chunk();
			break;
		}
		case Qt::Key_Down:
		{
			m_current_zchunk += 1;
			change_current_chunk();
			break;
		}
		case Qt::Key_Left:
		{
			m_current_xchunk -= 1;
			change_current_chunk();
			break;
		}
		case Qt::Key_Right:
		{
			m_current_xchunk += 1;
			change_current_chunk();
			break;
		}
		default:
			break;
	}
}


///////////////////////////
//       Private
///////////////////////////

void GLWidget::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_light_rotation += .003;

	if(m_fps_camera)
	{
		cam->transformCamera();
	}
	else
	{
		glTranslatef(0.0, 0.0, -7.0);
	
		glRotatef(m_xrot, 1.0, 0.0, 0.0);
		glRotatef(m_yrot, 0.0, 1.0, 0.0);
	
		glScalef(0.5, 0.5, 0.5);
		glScalef(m_zoom, m_zoom, m_zoom);
	}
	
	glPushMatrix();
	glTranslatef(2.5, 5.0*sin(m_light_rotation), 2.5*cos(m_light_rotation)+2.5);
	lighting();
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+1);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+2);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+3);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+4);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+5);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+6);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+7);
	glPopMatrix();

	glPushMatrix();
	glCallList(m_displayLists+8);
	glPopMatrix();
	
	char cameraLocation[100];
	sprintf(cameraLocation, "x:%2.3f y:%2.3f z:%2.3f yaw:%2.3f pitch:%2.3f", cam->x, cam->y, cam->z, cam->yaw, cam->pitch);
	glColor3f(1.0,1.0,1.0);
	renderText(0,30, cameraLocation);
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

void GLWidget::gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
   GLdouble xmin, xmax, ymin, ymax;

   ymax = zNear * tan(fovy * M_PI / 360.0);
   ymin = -ymax;
   xmin = ymin * aspect;
   xmax = ymax * aspect;


   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}


void GLWidget::change_current_chunk()
{
	glDeleteLists(m_displayLists, 9);
	m_displayLists = glGenLists(9);
	
	glNewList(m_displayLists, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk, m_current_zchunk);
	tmesh_center = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	heightmap = new Heightmap(tmesh_center,tmesh_center->width,tmesh_center->height,5.0/tmesh_center->width,0.0,0.0);
	cam = new TerrainCamera(2.5,2.5, heightmap);
	tmesh_center->compile();
	glEndList();
	
	glNewList(m_displayLists+1, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk, m_current_zchunk-1);
	tmesh_n = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_n->compile();
	glEndList();
	
	glNewList(m_displayLists+2, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk-1);
	tmesh_nw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_nw->compile();
	glEndList();
	
	glNewList(m_displayLists+3, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk);
	tmesh_w = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_w->compile();
	glEndList();

	glNewList(m_displayLists+4, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk+1);
	tmesh_sw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_sw->compile();
	glEndList();
	
	glNewList(m_displayLists+5, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk, m_current_zchunk+1);
	tmesh_s = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_s->compile();
	glEndList();
	
	glNewList(m_displayLists+6, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk+1);
	tmesh_se = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_se->compile();
	glEndList();
	
	glNewList(m_displayLists+7, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk);
	tmesh_e = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_e->compile();
	glEndList();
	
	glNewList(m_displayLists+8, GL_COMPILE);
	m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk-1);
	tmesh_ne = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
	tmesh_ne->compile();
	glEndList();
	
	updateGL();

}








