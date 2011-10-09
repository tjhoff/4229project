#include "Generator.h"

#include <math.h>
#include <QString>
#include <QDebug>

Generator::Generator()
{
}


float* Generator::default_translation(QString scene_name)
{
	if(scene_name == "Sine Wave" || scene_name == "High-poly Sine Wave")
	{
		float* t = new float[3];
		t[0] = -2.5;
		t[1] = 0.0;
		t[2] = -2.5;
		return t;
	}
	else
	{
		float* t = new float[3];
		t[0] = 0;
		t[1] = 0.0;
		t[2] = 0;
		return t;
	}
}


void Generator::sinewave()
{
	int d = 50;
	double step = 5.0/d;
	
	Vec3 points[d][d];
	
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			Vec3 point(i*step, sin(i*step*j*step)/2.0, j*step);
			points[i][j] = point;
		}
	}
	
	for(int i = 0; i < d-1; i++)
	{
		for(int j = 0; j < d-1; j++)
		{
			double colorfactor = (i+j)/2.0;
			Vec3 color(colorfactor*(1.0/d), colorfactor*(1.0/d), 1-(colorfactor*(1.0/d)));
			m_polys.append(new Polygon(points[i][j], points[i][j+1], points[i+1][j+1], points[i+1][j], color));
		}
	}

}

void Generator::high_poly_sinewave()
{
	int d = 300;
	double step = 5.0/d;
	
	Vec3 points[d][d];
	
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			Vec3 point(i*step, sin(i*step*j*step)/2.0, j*step);
			points[i][j] = point;
		}
	}
	
	for(int i = 0; i < d-1; i++)
	{
		for(int j = 0; j < d-1; j++)
		{
			double colorfactor = (i+j)/2.0;
			Vec3 color(colorfactor*(1.0/d), colorfactor*(1.0/d), 1-(colorfactor*(1.0/d)));
			m_polys.append(new Polygon(points[i][j], points[i][j+1], points[i+1][j+1], points[i+1][j], color));
		}
	}

}


void Generator::sombrero()
{
	int d = 50;
	double step = 5.0/d;
	
	Vec3 points[d][d];
	
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			double x = (i - (d/2.0)) * step;
			double y = (j - (d/2.0)) * step;
			Vec3 point(x, sombrero_height(x*5, y*5)*2, y);
			points[i][j] = point;
		}
	}
	
	for(int i = 0; i < d-1; i++)
	{
		for(int j = 0; j < d-1; j++)
		{
			double x = (i * (1.0/d)) - 0.5;
			double y = (j * (1.0/d)) - 0.5;
			double colorfactor = sqrt((x*x) + (y*y))*1.5;

			Vec3 color(1-colorfactor, 0.0, colorfactor);
			m_polys.append(new Polygon(points[i][j], points[i][j+1], points[i+1][j+1], points[i+1][j], color));
		}
	}
}


void Generator::high_poly_sombrero()
{
	int d = 300;
	double step = 5.0/d;
	
	Vec3 points[d][d];
	
	for(int i = 0; i < d; i++)
	{
		for(int j = 0; j < d; j++)
		{
			double x = (i - (d/2.0)) * step;
			double y = (j - (d/2.0)) * step;
			Vec3 point(x, sombrero_height(x*5, y*5)*2, y);
			points[i][j] = point;
		}
	}
	
	for(int i = 0; i < d-1; i++)
	{
		for(int j = 0; j < d-1; j++)
		{
			double x = (i * (1.0/d)) - 0.5;
			double y = (j * (1.0/d)) - 0.5;
			double colorfactor = sqrt((x*x) + (y*y))*1.5;

			Vec3 color(1-colorfactor, 0.0, colorfactor);
			m_polys.append(new Polygon(points[i][j], points[i][j+1], points[i+1][j+1], points[i+1][j], color));
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


void Generator::cube()
{
	Vec3 bbl(-1, -1, -1);
	Vec3 bbr( 1, -1, -1);
	Vec3 tbr( 1,  1, -1);
	Vec3 tbl(-1,  1, -1);
	Vec3 bfl(-1, -1,  1);
	Vec3 bfr( 1, -1,  1);
	Vec3 tfr( 1,  1,  1);
	Vec3 tfl(-1,  1,  1);
	
	Vec3 red(1, 0, 0);
	Vec3 green(0, 1, 0);
	Vec3 blue(0, 0, 1);
	Vec3 cyan(0, 1, 1);
	Vec3 magenta(1, 0, 1);
	Vec3 yellow(1, 1, 0);
	
	
	// top face
	m_polys.append(new Polygon(tbl, tfl, tfr, tbr, red));
	
	// left face
	m_polys.append(new Polygon(tfl, tbl, bbl, bfl, green));
	
	// back face
	m_polys.append(new Polygon(tbl, tbr, bbr, bbl, blue));
	
	// right face
	m_polys.append(new Polygon(tbr, tfr, bfr, bbr, cyan));
	
	// front face
	m_polys.append(new Polygon(tfr, tfl, bfl, bfr, magenta));
	
	// bottom face
	m_polys.append(new Polygon(bfr, bfl, bbl, bbr, yellow));
}


QList<Polygon*> Generator::polygons(QString scene_name)
{
	m_polys.clear();
	
	if(scene_name == "Cube")
	{
		cube();
	}
	else if(scene_name == "Sine Wave")
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
	
	return m_polys;
}





