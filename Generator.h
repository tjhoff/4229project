#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>

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
		std::vector<Polygon*> polygons();
		
	private:
		std::vector<Polygon*> m_polys;
};

#endif
