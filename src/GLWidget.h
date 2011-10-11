#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>

#include "Generator.h"
#include "Polygon.h"
#include "Camera3d.h"

#include <vector>

class GLWidget : public QGLWidget
{
	Q_OBJECT
	
	public:
		GLWidget(QWidget *parent = 0);
		~GLWidget();
		
	public slots:
		void toggleWireframe();
		void drawScene(QString scene_name);
		
	protected slots:
		void initializeGL();
		void resizeGL(int width, int height);
		void paintGL();
		void updateGL();
		void mousePressEvent(QMouseEvent* event);
		void mouseMoveEvent(QMouseEvent* event);
		void wheelEvent(QWheelEvent* event);
		void keyPressEvent(QKeyEvent* event);
		
	private:
		void draw();
		void lighting();
		void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far);
		
		GLfloat m_xrot;
		GLfloat m_yrot;
		GLfloat m_zrot;
		GLfloat m_zoom;
		
		GLfloat m_width;
		
		QTimer* m_update_timer;
		
		QPoint m_lastPos;
		
		QList<Polygon*> m_polygons;
		Generator* m_generator;
		
		GLuint m_displayList;
		
		GLfloat m_ambient;
		GLfloat m_diffuse;
		GLfloat m_specular;
		GLfloat m_xpos;
		GLfloat m_ypos;
		GLfloat m_zpos;
		GLfloat m_light_rotation;
		
		Camera3d * cam;
		
		bool m_wireframe;
		
		float* m_default_translation;
};

#endif
