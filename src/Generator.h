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
		void sombrero();
		void sinewave();
		void high_poly_sombrero();
		void high_poly_sinewave();
		double sombrero_height(double x, double y);
		void perlin_object();
		void smooth_perlin();
		void high_poly_smooth_perlin();
		
		QList<Polygon*> m_polys;
		
		int m_d;
		Vec3** m_vertices;
		Vec3** m_colors;
};

#endif
