#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QtOpenGL>
#include <QGLWidget>

class GLWidget : public QGLWidget
{
	Q_OBJECT
	
	public:
		GLWidget(QWidget *parent = 0);
		
	protected:
		void initializeGL();
		void resizeGL(int width, int height);
		void paintGL();
		void mousePressEvent(QMouseEvent* event);
		void mouseMoveEvent(QMouseEvent* event);

	private:
		void draw();
		
		GLfloat m_xrot;
		GLfloat m_yrot;
		GLfloat m_zrot;
		
		QColor m_faceColors[6];
		GLfloat m_width;
	
		GLfloat m_cubeSize;
		
		QPoint m_lastPos;
};

#endif
