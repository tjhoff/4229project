#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>

#include "GLWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
		
	private slots:
		void toggleFullscreen();
		
		
	private:
		int m_width;
		int m_height;
		
		QMenuBar* m_menuBar;
		QMenu* m_fileMenu;
		QAction* m_quitAction;
		
		QToolBar* m_toolBar;
		QAction* m_generateAction;
		QAction* m_fullScreenAction;
		QAction* m_toggleWireframeAction;
		
		GLWidget* m_glWidget;
		
		bool m_fullscreen;
};


#endif
