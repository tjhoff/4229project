#include "Generator.h"

#include <QDebug>

Generator::Generator()
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
	m_polys.push_back(new Polygon(tbl, tfl, tfr, tbr, red));
	
	// left face
	m_polys.push_back(new Polygon(tfl, tbl, bbl, bfl, green));
	
	// back face
	m_polys.push_back(new Polygon(tbl, tbr, bbr, bbl, blue));
	
	// right face
	m_polys.push_back(new Polygon(tbr, tfr, bfr, bbr, cyan));
	
	// front face
	m_polys.push_back(new Polygon(tfr, tfl, bfl, bfr, magenta));
	
	// bottom face
	m_polys.push_back(new Polygon(bfr, bfl, bbl, bbr, yellow));
	
}


std::vector<Polygon*> Generator::polygons()
{
	return m_polys;
}
