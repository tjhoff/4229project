#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QComboBox>

#include "GLWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
		virtual ~MainWindow();
		
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
		QAction* m_regenAction;
		QAction* m_toggleCameraAction;
		QAction* m_toggleParticlesAction;
		QAction* m_toggleBloomAction;
		QAction* m_toggleToonLighting;
		QAction* m_toggleBloomFix;		
		
		GLWidget* m_glWidget;
		
		bool m_fullscreen;
};


#endif
