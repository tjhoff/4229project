#include "GLWidget.h"

#include <QDebug>

#include <QPainter>
#include <unistd.h>

#include <time.h>

GLWidget::GLWidget(QWidget* parent) : QGLWidget(parent)
{
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	
	m_xrot = 15;
	m_yrot = 45;
	m_zrot = 0;	
	m_zoom = 1.0;
	
	m_speed = .001;
	
	m_ambient = 0.3; 
	m_diffuse = 0.5;  
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
	}
	
	m_generator = new Generator();
	change_current_chunk(ALL);
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
		m_lastPos = event->pos();
	}	
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
	if(m_fps_camera)
	{
		if(event->delta() > 0)
		{
			m_speed += .05;
			//m_zoom += 0.1;
		}
		else if(event->delta() < 0)
		{
			m_speed -= .05;
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
			change_current_chunk(UP);
			break;
		}
		case Qt::Key_Down:
		{
			change_current_chunk(DOWN);
			break;
		}
		case Qt::Key_Left:
		{
			change_current_chunk(LEFT);
			break;
		}
		case Qt::Key_Right:
		{
			change_current_chunk(RIGHT);
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
	glTranslatef(2.5, 5.0, 2.5);
	lighting();
	glPopMatrix();

	glPushMatrix();
	glCallList(m_nList);
	glCallList(m_nwList);
	glCallList(m_wList);
	glCallList(m_swList);
	glCallList(m_sList);
	glCallList(m_seList);
	glCallList(m_eList);
	glCallList(m_neList);
	glCallList(m_centerList);
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


void GLWidget::change_current_chunk(Direction dir)
{
	double start_time = clock()/1000;
	switch(dir)
	{
		case UP:
		{
			m_current_zchunk -= 1;
			GLuint old_sw = m_swList;
			GLuint old_s = m_sList;
			GLuint old_se = m_seList;
			
			glDeleteLists(old_sw, 1);
			glDeleteLists(old_s, 1);
			glDeleteLists(old_se, 1);
			
			m_swList = m_wList;
			m_sList = m_centerList;
			m_seList = m_eList;
			
			m_eList = m_neList;
			m_centerList = m_nList;
			m_wList = m_nwList;
			
			m_neList = glGenLists(1);
			m_nList = glGenLists(1);
			m_nwList = glGenLists(1);
			
			glNewList(m_nList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk, m_current_zchunk-1);
			tmesh_n = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_n->compile();
			glEndList();
			
			glNewList(m_neList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk-1);
			tmesh_ne = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_ne->compile();
			glEndList();
			
			glNewList(m_nwList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk-1);
			tmesh_nw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_nw->compile();
			glEndList();
		
			break;
		}
		case DOWN:
		{
			m_current_zchunk += 1;
			
			GLuint old_nw = m_nwList;
			GLuint old_n = m_nList;
			GLuint old_ne = m_neList;
			
			glDeleteLists(old_nw, 1);
			glDeleteLists(old_n, 1);
			glDeleteLists(old_ne, 1);
			
			m_nwList = m_wList;
			m_nList = m_centerList;
			m_neList = m_eList;
			
			m_wList = m_swList;
			m_centerList = m_sList;
			m_eList = m_seList;
			
			m_swList = glGenLists(1);
			m_sList = glGenLists(1);
			m_seList = glGenLists(1);
			
			glNewList(m_sList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk, m_current_zchunk+1);
			tmesh_s = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_s->compile();
			glEndList();
			
			glNewList(m_swList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk+1);
			tmesh_sw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_sw->compile();
			glEndList();
			
			glNewList(m_seList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk+1);
			tmesh_se = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_se->compile();
			glEndList();
			
			break;
		}
		case LEFT:
		{
			m_current_xchunk -= 1;
			
			GLuint old_ne = m_neList;
			GLuint old_e = m_eList;
			GLuint old_se = m_seList;
			
			glDeleteLists(old_ne, 1);
			glDeleteLists(old_e, 1);
			glDeleteLists(old_se, 1);
			
			m_neList = m_nList;
			m_eList = m_centerList;
			m_seList = m_sList;
			
			m_nList = m_nwList;
			m_centerList = m_wList;
			m_sList = m_swList;
			
			m_nwList = glGenLists(1);
			m_wList = glGenLists(1);
			m_swList = glGenLists(1);

			glNewList(m_nwList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk-1);
			tmesh_nw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_nw->compile();
			glEndList();
			
			glNewList(m_wList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk);
			tmesh_w = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_w->compile();
			glEndList();
			
			glNewList(m_swList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk+1);
			tmesh_sw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_sw->compile();
			glEndList();
			
			break;
		}
		case RIGHT:
		{
			m_current_xchunk += 1;
			
			GLuint old_nw = m_nwList;
			GLuint old_w = m_wList;
			GLuint old_sw = m_swList;
			
			glDeleteLists(old_nw, 1);
			glDeleteLists(old_w, 1);
			glDeleteLists(old_sw, 1);
			
			m_nwList = m_nList;
			m_wList = m_centerList;
			m_swList = m_sList;
			
			m_nList = m_neList;
			m_centerList = m_eList;
			m_sList = m_seList;
			
			m_neList = glGenLists(1);
			m_eList = glGenLists(1);
			m_seList = glGenLists(1);
			
			glNewList(m_neList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk-1);
			tmesh_ne = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_ne->compile();
			glEndList();
			
			glNewList(m_eList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk);
			tmesh_e = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_e->compile();
			glEndList();
			
			glNewList(m_seList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk+1);
			tmesh_se = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_se->compile();
			glEndList();
			
			break;
		}
		case ALL:
			m_current_xchunk = 0;
			m_current_zchunk = 0;
			
			glDeleteLists(m_nwList, 1);
			glDeleteLists(m_wList, 1);
			glDeleteLists(m_swList, 1);
			glDeleteLists(m_sList, 1);
			glDeleteLists(m_seList, 1);
			glDeleteLists(m_eList, 1);
			glDeleteLists(m_neList, 1);
			glDeleteLists(m_centerList, 1);
			
			m_nwList = glGenLists(1);
			m_wList = glGenLists(1);
			m_swList = glGenLists(1);
			m_sList = glGenLists(1);
			m_seList = glGenLists(1);
			m_eList = glGenLists(1);
			m_neList = glGenLists(1);
			m_nList = glGenLists(1);
			m_centerList = glGenLists(1);
			
			glNewList(m_nList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk, m_current_zchunk-1);
			tmesh_n = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_n->compile();
			glEndList();
			
			glNewList(m_nwList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk-1);
			tmesh_nw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_nw->compile();
			glEndList();
			
			glNewList(m_wList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk);
			tmesh_w = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_w->compile();
			glEndList();
			
			glNewList(m_swList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk-1, m_current_zchunk+1);
			tmesh_sw = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_sw->compile();
			glEndList();
			
			glNewList(m_sList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk, m_current_zchunk+1);
			tmesh_s = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_s->compile();
			glEndList();
			
			glNewList(m_seList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk+1);
			tmesh_se = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_se->compile();
			glEndList();
			
			glNewList(m_eList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk);
			tmesh_e = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_e->compile();
			glEndList();
			
			glNewList(m_neList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk+1, m_current_zchunk-1);
			tmesh_ne = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_ne->compile();
			glEndList();
			
			glNewList(m_centerList, GL_COMPILE);
			m_generator->polygons_at(m_current_xchunk, m_current_zchunk);
			tmesh_center = new TriangleMesh(m_generator->m_vertices,m_generator->m_colors,m_generator->m_d, m_generator->m_d);
			tmesh_center->compile();
			glEndList();
			
			break;
	}
		
	heightmap = new Heightmap(tmesh_center,tmesh_center->width,tmesh_center->height,5.0/tmesh_center->width,0.0,0.0);
	cam = new TerrainCamera(2.5,2.5, heightmap);
	
	qDebug() << "GLWidget::change_current_chunk took" << (clock()/1000) - start_time << "milliseconds";
}








