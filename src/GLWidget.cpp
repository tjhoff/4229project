#include "GLWidget.h"

#include <QDebug>

#include <QPainter>

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
	m_specular = .3;  
	m_xpos = 0;
	m_ypos = 0;
	m_zpos = 1;
	m_light_rotation = 0.0;
	
	m_wireframe = false;
	m_displayList = 0;
	m_default_translation = new float[3];
	
	cam = new Camera3d(0.0,0.0,-7.0);
	setFocusPolicy(Qt::StrongFocus);
	m_update_timer = new QTimer();
	connect(m_update_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	m_update_timer->start(1000/60.0);
}		


GLWidget::~GLWidget()
{
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


void GLWidget::drawScene(QString scene_name)
{
	if(m_polygons.size() != 0)
	{
		m_polygons.clear();
		glDeleteLists(m_displayList, 1);
		delete m_generator;
	}
	
	m_generator = new Generator();
	m_displayList = glGenLists(1);
	m_polygons = m_generator->polygons(scene_name);
	m_default_translation = m_generator->default_translation(scene_name);
	qDebug()<<scene_name;
	if(scene_name == "High-poly Smooth Perlin") {
		delete cam;
		cam = new TerrainCamera(2.5,2.5, m_generator->heightmap);
		//cam = new Camera3d(2.5,1.0,2.5);
		qDebug() << "new camera added";
		}
	else {
		delete cam;
		cam = new Camera3d(2.5,1.0,2.5);
	}glNewList(m_displayList, GL_COMPILE);
	
	for(int i = 0; i < m_polygons.size(); i++)
	{		
		glBegin(GL_POLYGON);
		glNormal3fv(m_polygons[i]->get_normal());
		
		for(int j = 0; j < 4; j++)
		{
			glColor3fv(m_polygons[i]->get_colors()[j]);
			glVertex3fv(m_polygons[i]->get_vertices()[j]);
		}

		glEnd();
	}
	glEndList();
	
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
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glEnable(GL_CULL_FACE);
	
	float ambient[] = {0.3, 0.3, 0.3, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	float specular[] = {0.1,0.1,0.1,1.0};
	glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
	glEnable(GL_LIGHT0);
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
		cam->rotate(180*-dx,180*-dy);
		/*m_xrot += 180 * dy;
		m_yrot += 180 * dx;*/
		updateGL();
		m_lastPos = event->pos();
	}	
}

void GLWidget::wheelEvent(QWheelEvent* event)
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
	
	updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent* event){

	if (event->key() == Qt::Key_Up) cam->move(m_speed);
	if (event->key() == Qt::Key_Down) cam->move(-m_speed);
}


///////////////////////////
//       Private
///////////////////////////

void GLWidget::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	cam->transformCamera();

	//qDebug()<<cam->x<<","<<cam->y<<","<<cam->z<<","<<cam->yaw<<","<<cam->pitch;
	/*glTranslatef(0.0, 0.0, -7.0);
	
	glRotatef(m_xrot, 1.0, 0.0, 0.0);
	glRotatef(m_yrot, 0.0, 1.0, 0.0);
	
	glScalef(0.5, 0.5, 0.5);
	glScalef(m_zoom, m_zoom, m_zoom);*/
	
	glPushMatrix();
	glTranslatef(5, 5, 5);
	lighting();
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(m_default_translation[0], m_default_translation[1], m_default_translation[2]);
	glCallList(m_displayList);
	glPopMatrix();
	
	char cameraLocation[100];
	sprintf(cameraLocation, "x:%2.3f y:%2.3f z:%2.3f yaw:%2.3f pitch:%2.3f", cam->x, cam->y, cam->z, cam->yaw, cam->pitch);
	glColor3f(1.0,1.0,1.0);
	renderText(0,50, cameraLocation);
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









