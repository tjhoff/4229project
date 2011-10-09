#ifndef GENERATOR_H
#define GENERATOR_H

#include <QList>
#include "Polygon.h"

//-------------------------------
//     Base Generator Class
//
//     Subclass this for different 
//     terrain generators
//-------------------------------
class Generator
{
	public:
		Generator();
		QList<Polygon*> polygons(QString scene_name);
		float* default_translation(QString scene_name);
		
	private:
		void cube();
		void sombrero();
		void sinewave();
		void high_poly_sombrero();
		void high_poly_sinewave();
		double sombrero_height(double x, double y);
		void perlin_object();
		QList<Polygon*> m_polys;
};

#endif
