#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QtOpenGL>
#include <QGLWidget>

#include "Generator.h"
#include "Polygon.h"

#include <vector>

class GLWidget : public QGLWidget
{
	Q_OBJECT
	
	public:
		GLWidget(QWidget *parent = 0);
		
	public slots:
		void toggleWireframe();
		
	protected:
		void initializeGL();
		void resizeGL(int width, int height);
		void paintGL();
		void mousePressEvent(QMouseEvent* event);
		void mouseMoveEvent(QMouseEvent* event);
		void initLists();

	private:
		void draw();
		void lighting();
		
		GLfloat m_xrot;
		GLfloat m_yrot;
		GLfloat m_zrot;
		
		QColor m_faceColors[6];
		GLfloat m_width;
	
		GLfloat m_cubeSize;
		
		QPoint m_lastPos;
		
		std::vector<Polygon*> m_polygons;
		Generator* m_generator;
		
		GLuint m_displayList;
		
		GLfloat m_ambient;
		GLfloat m_diffuse;
		GLfloat m_specular;
		GLfloat m_xpos;
		GLfloat m_ypos;
		GLfloat m_zpos;
		
		bool m_wireframe;
};

#endif
