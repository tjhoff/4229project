#include "MainWindow.h"

#include <QDesktopWidget>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
	m_width = 800;
	m_height = 600;
	
	int x = (QApplication::desktop()->width()-m_width)/2;
	int y = (QApplication::desktop()->height()-m_height)/2;
	setGeometry(x, y, m_width, m_height);
	
	m_glWidget = new GLWidget();
	setCentralWidget(m_glWidget);
	
	m_menuBar = new QMenuBar();
	m_fileMenu = m_menuBar->addMenu("File");
	m_quitAction = m_fileMenu->addAction("Quit");
	m_quitAction->setShortcut(QKeySequence::Quit);
	connect(m_quitAction, SIGNAL(triggered()), this, SLOT(close()));
	setMenuBar(m_menuBar);
		
	m_toolBar = new QToolBar();
	addToolBar(Qt::TopToolBarArea, m_toolBar);
	
	m_fullScreenAction = m_toolBar->addAction("Toggle Fullscreen");
	m_toggleWireframeAction = m_toolBar->addAction("Toggle Wireframe Mode");
	
	connect(m_fullScreenAction, SIGNAL(triggered()), this, SLOT(toggleFullscreen()));
	connect(m_toggleWireframeAction, SIGNAL(triggered()), m_glWidget, SLOT(toggleWireframe()));
	
	m_displayNameDropdown = new QComboBox();
	m_displayNameDropdown->addItem("Sombrero");
	m_displayNameDropdown->addItem("Sine Wave");
	m_displayNameDropdown->addItem("High-poly Sine Wave");
	m_displayNameDropdown->addItem("High-poly Sombrero");
	m_displayNameDropdown->addItem("Perlin Object");
	m_displayNameDropdown->addItem("Smooth Perlin");
	m_displayNameDropdown->addItem("High-poly Smooth Perlin"); 
	
	m_toolBar->addWidget(m_displayNameDropdown);	
	m_regenAction = m_toolBar->addAction("Generate Scene");
	
	connect(m_regenAction, SIGNAL(triggered()), this, SLOT(generateScene()));

	m_fullscreen = false;
}

////////////////////////////////////////
//           Slots
////////////////////////////////////////

void MainWindow::toggleFullscreen()
{
	if(m_fullscreen)
	{
		showNormal();
		m_fullscreen = false;
	}
	else
	{
		showFullScreen();
		m_fullscreen = true;
	}
}


void MainWindow::generateScene()
{
	m_glWidget->drawScene(m_displayNameDropdown->currentText());
}

