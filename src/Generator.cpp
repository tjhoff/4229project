#include "Generator.h"
#include "Perlin.cpp"
#include "Perlin2.h"

#include <math.h>
#include <QString>
#include <QDebug>


Generator::Generator()
{
	m_d = 0;
}


Generator::~Generator()
{
	qDebug() << "Generator destructor";
	if(m_d != 0)
	{
		for(int i = 0; i < m_d; i++)
		{
			delete[] m_colors[i];
			delete[] m_vertices[i];
		}
		delete[] m_colors;
		delete[] m_vertices;
		delete[] m_default_translation;
		
		m_polys.clear();
	}
}
		


float* Generator::default_translation(QString scene_name)
{
	if(scene_name == "Sine Wave" || scene_name == "High-poly Sine Wave" || scene_name == "Perlin Object" || scene_name == "Smooth Perlin" || scene_name == "High-poly Smooth Perlin" || scene_name == "High-poly Mesas")
	{
		m_default_translation = new float[3];
		m_default_translation[0] = -2.5;
		m_default_translation[1] = 0.0;
		m_default_translation[2] = -2.5;
		return m_default_translation;
	}
	else
	{
		m_default_translation = new float[3];
		m_default_translation[0] = 0;
		m_default_translation[1] = 0.0;
		m_default_translation[2] = 0;
		return m_default_translation;
	}
}


void Generator::sinewave()
{
	m_d = 50;
	double step = 5.0/m_d;
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i < m_d; i++)
	{
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		for(int j = 0; j < m_d; j++)
		{
			Vec3 point(i*step, sin(i*step*j*step)/2.0, j*step);
			m_vertices[i][j] = point;
			double colorfactor = (i+j)/2.0;
			m_colors[i][j] = Vec3(colorfactor*(1.0/m_d), colorfactor*(1.0/m_d), 1-(colorfactor*(1.0/m_d)));
		}
	}
}

void Generator::high_poly_sinewave()
{
	m_d = 300;
	double step = 5.0/m_d;
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i < m_d; i++)
	{
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		for(int j = 0; j < m_d; j++)
		{
			Vec3 point(i*step, sin(i*step*j*step)/2.0, j*step);
			m_vertices[i][j] = point;
			double colorfactor = (i+j)/2.0;
			m_colors[i][j] = Vec3(colorfactor*(1.0/m_d), colorfactor*(1.0/m_d), 1-(colorfactor*(1.0/m_d)));
		}
	}
}

void Generator::sombrero()
{
	m_d = 50;
	double step = 5.0/m_d;
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i < m_d; i++)
	{
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		for(int j = 0; j < m_d; j++)
		{
			double x = (i - (m_d/2.0)) * step;
			double y = (j - (m_d/2.0)) * step;
			Vec3 point(x, sombrero_height(x*5, y*5)*2, y);
			m_vertices[i][j] = point;
			
			x = (i * (1.0/m_d)) - 0.5;
			y = (j * (1.0/m_d)) - 0.5;
			double colorfactor = sqrt((x*x) + (y*y))*1.5;

			m_colors[i][j] = Vec3(1-colorfactor+0.05, 1-colorfactor+0.05, 1-colorfactor+0.1);
		}
	}
}


void Generator::high_poly_sombrero()
{
	m_d = 300;
	double step = 5.0/m_d;
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i < m_d; i++)
	{
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		for(int j = 0; j < m_d; j++)
		{
			double x = (i - (m_d/2.0)) * step;
			double y = (j - (m_d/2.0)) * step;
			Vec3 point(x, sombrero_height(x*5, y*5)*2, y);
			m_vertices[i][j] = point;
			
			x = (i * (1.0/m_d)) - 0.5;
			y = (j * (1.0/m_d)) - 0.5;
			double colorfactor = sqrt((x*x) + (y*y))*1.5;

			m_colors[i][j] = Vec3(1-colorfactor, 0.0, colorfactor);
		}
	}
}


double Generator::sombrero_height(double x, double y)
{
	double r = sqrt(x*x + y*y);
	
	if(r == 0)
	{
		return 1;
	}
	else
	{
		return  sin (r) / r;
	}
}


// teej add

void Generator::perlin_object(){
	m_d = 50;
	float step = 5.0/m_d;
	float ** p;
	float x,y,z;
	float colorVal;
	p = perlin_noise(m_d,m_d,3,.3);
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i<m_d;i++){
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		z = i*step;
		for(int j = 0; j<m_d; j++){
			x = j*step;
			y = p[i][j]*(3.0/2.0)*step;
			Vec3 point(x,y*2,z);
			m_vertices[i][j] = point;
			
			colorVal = p[i][j]*(3.0/2.0)+.5;
			m_colors[i][j] = Vec3(1-colorVal,colorVal,colorVal);
		}
	}
}


void Generator::smooth_perlin()
{
	m_d = 80;
	float step = 5.0/m_d;
	float x,y,z;
	Vec3 color;
	Perlin* perlin = new Perlin(6, 2, 1, time(NULL));
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i<m_d;i++){
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		z = i*step;
		for(int j = 0; j<m_d; j++){
			x = j*step;
			y = perlin->Get(x/3, z/3);
			y /= (1/y);
			m_vertices[i][j] = Vec3(x,y*2,z);
			
			if(y > 0.2)
			{
				color = Vec3(0.9, 0.9, 0.9);
			}
			else if(y <= 0.2 && y > 0.1)
			{
				color = Vec3(0.3, 0.3, 0.3);
			}
			else
			{
				color = Vec3(0.0, 0.5, 0.0);
			}
			
			m_colors[i][j] = color;
		}
	}
}

void Generator::high_poly_smooth_perlin()
{
	m_d = 400;
	float step = 5.0/m_d;
	float x,y,z;
	Vec3 color;
	Perlin* perlin = new Perlin(6, 2, 1, time(NULL));
	
	//qDebug() << "Perlin is" << sizeof(Perlin) << "bytes";
	
	//qDebug() << "Allocating" << m_d*m_d*sizeof(Vec3)*2 << "bytes for vertices and colors";
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i<m_d;i++){
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		z = i*step;
		for(int j = 0; j<m_d; j++){
			x = j*step;
			y = perlin->Get(x/3, z/3);
			y *= y;
			m_vertices[i][j] = Vec3(x,y*2,z);
			
			if(y > 0.2)
			{
				color = Vec3(0.9, 0.9, 0.9);
			}
			else if(y <= 0.2 && y > 0.1)
			{
				color = Vec3(0.3, 0.3, 0.3);
			}
			else
			{
				color = Vec3(0.1, 0.4, 0.1);
			}
			
			m_colors[i][j] = color;
		}
	}
}


void Generator::high_poly_mesas()
{
	m_d = 400;
	float step = 5.0/m_d;
	float x,y,z;
	
	Vec3 color;
	Perlin* perlin = new Perlin(6, 2, 1.0, time(NULL));
	
	m_vertices = new Vec3*[m_d];
	m_colors = new Vec3*[m_d];
	
	for(int i = 0; i<m_d;i++){
		m_vertices[i] = new Vec3[m_d];
		m_colors[i] = new Vec3[m_d];
		z = i*step;
		for(int j = 0; j<m_d; j++){
			x = j*step;
			y = perlin->Get(x/2, z/2);
			y *= y*2;
			
			if(y > 0.3)
			{
				y = (y*0.1)+0.27;
				color = Vec3(0.4, 0.2, 0.1);			
			}
			else if (y > .02)
			{	
				color = Vec3(.6*y + .4, 0.40*y +.2, 0.1);			
			}
			else{
				color = Vec3(.8,.8,.7);
			}
			
			m_vertices[i][j] = Vec3(x,y,z);
			m_colors[i][j] = color;

		}
	}

}


QList<Polygon*> Generator::polygons(QString scene_name)
{
	m_polys.clear();
	
	if(m_d != 0)
	{
		for(int i = 0; i < m_d; i++)
		{
			delete[] m_colors[i];
			delete[] m_vertices[i];
		}
		delete[] m_colors;
		delete[] m_vertices;
		
		for(int i = 0; i < m_polys.size(); i++)
		{
			delete m_polys[i];
		}
		
		m_d = 0;
	}
	
	
	if(scene_name == "Sine Wave")
	{
		sinewave();
	}
	else if(scene_name == "Sombrero")
	{
		sombrero();
	}
	else if(scene_name == "High-poly Sine Wave")
	{	
		high_poly_sinewave();
	}
	else if(scene_name == "High-poly Sombrero")
	{
		high_poly_sombrero();
	}
	else if(scene_name == "Perlin Object")
	{
		perlin_object();
	}
	else if(scene_name == "Smooth Perlin")
	{
		smooth_perlin();
	}
	else if(scene_name == "High-poly Smooth Perlin")
	{
		high_poly_smooth_perlin();
	}
	else if(scene_name == "High-poly Mesas")
	{
		high_poly_mesas();
	}
	
	/*for(int i = 0; i < m_d-1; i++)
	{
		for(int j = 0; j < m_d-1; j++)
		{
			Polygon* poly = new Polygon();
			poly->set_vertices(m_vertices[i][j], m_vertices[i][j+1], m_vertices[i+1][j+1], m_vertices[i+1][j]);
			poly->set_colors(m_colors[i][j], m_colors[i][j+1], m_colors[i+1][j+1], m_colors[i+1][j]);
			m_polys.append(poly);
		}
	}*/
	
	qDebug() << "Allocated" << m_d*m_d*sizeof(Polygon) << "bytes for polygons.";
	
	return m_polys;
}





