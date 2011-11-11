#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>
#include <stdio.h>

#include "Polygon.h"
#include "Camera3d.h"
#include "Heightmap.h"
#include "TriangleMesh.h"
#include "Skybox.h"
#include "Map.h"
#include "Chunk.h"
#include "CSCIx229.h"

#include <vector>

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ALL
};

class GLWidget : public QGLWidget
{
	Q_OBJECT
	
	public:
		GLWidget(QWidget *parent = 0);
		~GLWidget();
		
	public slots:
		void toggleWireframe();
		void drawScene();
		void toggleCameraMode();
		
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
		void change_current_chunk();
		void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far);
		
		GLfloat m_xrot;
		GLfloat m_yrot;
		GLfloat m_zrot;
		GLfloat m_zoom;
		
		GLfloat m_speed;
		
		GLfloat m_width;
		
		QTimer* m_update_timer;
		
		QPoint m_lastPos;
		
		QList<Polygon*> m_polygons;
				
		int m_current_xchunk;
		int m_current_zchunk;
		
		GLfloat m_ambient;
		GLfloat m_diffuse;
		GLfloat m_specular;
		GLfloat m_xpos;
		GLfloat m_ypos;
		GLfloat m_zpos;
		GLfloat m_light_rotation;
		
		Map* m_map;
		
		Chunk* m_nchunk;
		Chunk* m_nwchunk;
		Chunk* m_wchunk;
		Chunk* m_swchunk;
		Chunk* m_schunk;
		Chunk* m_sechunk;
		Chunk* m_echunk;
		Chunk* m_nechunk;
		Chunk* m_centerchunk;
		
		Camera * cam;
		Skybox * skybox;
		
		bool m_wireframe;
		bool m_fps_camera;
		bool m_initial_chunk;
		
		float* m_default_translation;
};

#endif
